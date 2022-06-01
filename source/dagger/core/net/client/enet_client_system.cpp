#include "core/net/client/enet_client_system.h"
#include "core/engine.h"
#include <enet/enet.h>
#include "core/net/client/client.h"
#include <variant>

using namespace dagger;

ENetHost* ClientENetSystem::InitENetHost() 
{
    if (enet_initialize () != 0) 
    {
        Logger::critical("Failed to initialize ENet");
        return nullptr;
    }

    auto* host = enet_host_create(nullptr, // client host
                                  2,       // allow up to 2 outgoing connections
                                  2,       // allow up to 2 channels to be used, 0 and 1
                                  0,       // assume unlimited incoming bandwidth
                                  0);      // assume unlimited outgoing bandwidth
    if (!host) 
    {
        Logger::critical("Failed to create ENet host");
        return nullptr;
    }

    return host;
}

ENetPeer* ClientENetSystem::ConnectToServer(ENetHost* host_, const std::string& hostname_, UInt16 port_) 
{
    ENetAddress address;
    enet_address_set_host(&address, hostname_.c_str());
    address.port = port_;

    // start the connection, allocating the two channels 0 and 1
    ENetPeer* peer = enet_host_connect(host_, &address, 2, 0);

    return peer;
}

void ClientENetSystem::SpinUp()
{
    // TODO: move to .ini file
    String address = "localhost";
    UInt16 port = 5050;

    auto* host = InitENetHost();
    if (!host) 
    {
        Logger::critical("Failed to start ENet host");
        return;
    }

    auto* peer = ConnectToServer(host, address, port);
    if (!peer) 
    {
        Logger::critical("Failed to connect to ENet server");
        return;
    }
    Logger::info("Started ENet client");

    auto& registry = Engine::Registry();
    registry.set<ENetHost*>(host);
    registry.set<ENetPeer*>(peer);
    registry.set<client::NetworkContext>();
}

void ClientENetSystem::Run()
{
    auto& registry = Engine::Registry();
    auto* host = registry.ctx<ENetHost*>();
    auto& clientNetworkContext = registry.ctx<client::NetworkContext>();
    ENetEvent event;

    while (enet_host_service(host, &event, 0) > 0) 
    {
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT: 
            {
                clientNetworkContext.PacketSink().connect<&ClientENetSystem::SendPacketToServer>(*this);
                Logger::info("Connected to server");
                break;
            }
            case ENET_EVENT_TYPE_DISCONNECT: 
            {
                clientNetworkContext.PacketSink().disconnect<&ClientENetSystem::SendPacketToServer>(*this);
                Logger::info("Disonnected from server");
                break;
            }
            case ENET_EVENT_TYPE_RECEIVE: 
            {
                // deserialize packet
                Packet decodedPacket = packet::deserialize(event.packet->data, event.packet->dataLength);

                // receive packet for client
                std::visit([&](auto &&decoded_packet) {
                    Logger::info("Processing packet");
                    // process_packet(registry, clientEntity, decodedPacket);
                }, decodedPacket.var);

                // clean up the packet because we're done with it
                enet_packet_destroy(event.packet);
                break;
            }
            default:
                break;
        }
    }

    // set RTT?
}

void ClientENetSystem::SendPacketToServer(const Packet& packet)
{
    auto& registry = Engine::Registry();
    UInt32 flags = 0;
    auto data = packet::serialize(packet);
    auto* host = registry.ctx<ENetHost*>();
    auto* peer = registry.ctx<ENetPeer*>();
    
    ENetPacket* enet_packet = enet_packet_create(data.data(), data.size(), flags);
    enet_peer_send(peer, flags, enet_packet);
}

void ClientENetSystem::WindDown() 
{
    auto& registry = Engine::Registry();
    auto* host = registry.ctx<ENetHost*>();
    auto* peer = registry.ctx<ENetPeer*>();

    if (peer)
    {
        enet_peer_disconnect(peer, 0);
    }
    enet_host_destroy(host);
    enet_deinitialize();

    registry.unset<ENetHost*>();
    registry.unset<ENetPeer*>();
}
