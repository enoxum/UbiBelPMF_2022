#include "enet_server_system.h"
#include "core/engine.h"
#include <enet/enet.h>
#include "core/net/server/server.h"
#include <variant>

using namespace dagger;

ENetHost* ServerENetSystem::InitENetHost(UInt16 port_) 
{
    if (enet_initialize () != 0) 
    {
        Logger::critical("Failed to initialize ENet");
        return nullptr;
    }

    ENetAddress address;
    address.host = ENET_HOST_ANY;
    enet_address_set_host(&address, "0.0.0.0");
    address.port = port_;

    auto* host = enet_host_create(&address, // the address to bind the server host to
                                   32,      // allow up to 32 clients and/or outgoing connections
                                    2,      // allow up to 2 channels to be used, 0 and 1
                                    0,      // assume unlimited incoming bandwidth
                                    0);     // assume unlimited outgoing bandwidth
    if (!host) 
    {
        Logger::critical("Failed to create ENet host");
        return nullptr;
    }

    return host;
}


void ServerENetSystem::SpinUp()
{
    // TODO: move to .ini file
    UInt16 port = 5050;

    auto* host = InitENetHost(port);
    if (!host) 
    {
        Logger::critical("Failed to start ENet host");
    }

    auto& registry = Engine::Registry();
    registry.set<ENetHost*>(host);
    registry.set<ClientEntityMap>();
    auto& serverNetworkContext = registry.set<server::NetworkContext>();
    serverNetworkContext.PacketSink().connect<&ServerENetSystem::SendPacketToClient>(*this);

    Logger::info("Initialized ENet server on port {}", port);
}

void ServerENetSystem::Run()
{
    auto& registry = Engine::Registry();
    auto* host = registry.ctx<ENetHost*>();
    auto& clientEntityMap = registry.ctx<ClientEntityMap>().map;
    ENetEvent event;

    while (enet_host_service(host, &event, 0) > 0) 
    {
        const auto peerID = event.peer->incomingPeerID;

        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT: 
            {
                // enet_peer_timeout(event.peer, 0, 10000, 30000);
                enet_peer_timeout(event.peer, 0, 1000, 3000);
                auto clientEntity = server::MakeClientEntity(registry);
                registry.emplace<PeerID>(clientEntity, peerID);
                clientEntityMap[peerID] = clientEntity;
                Logger::info("Connected {}", peerID);
                break;
            }
            case ENET_EVENT_TYPE_DISCONNECT: 
            {
                auto& clientEntity = clientEntityMap.at(peerID);
                // TODO destroy client
                clientEntityMap.erase(peerID);
                Logger::info("Disonnected {}", peerID);
                break;
            }
            case ENET_EVENT_TYPE_RECEIVE: 
            {
                // deserialize packet
                Packet decodedPacket = packet::deserialize(event.packet->data, event.packet->dataLength);

                auto& clientEntity = clientEntityMap.at(peerID);
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
}

void ServerENetSystem::WindDown() 
{
    auto& registry = Engine::Registry();

    auto* host = registry.ctx<ENetHost*>();
    enet_host_destroy(host);
    enet_deinitialize();
    registry.unset<ENetHost*>();
    registry.unset<ClientEntityMap>();
}

void ServerENetSystem::SendPacketToClient(Entity clientEntity, const Packet& packet)
{
    auto& registry = Engine::Registry();
    UInt32 flags = 0;
    auto data = packet::serialize(packet);
    auto peerID = registry.get<PeerID>(clientEntity).value;
    auto* host = registry.ctx<ENetHost*>();

    Logger::info("Sending to {}", peerID);
    
    ENetPacket* enet_packet = enet_packet_create(data.data(), data.size(), flags);
    ENetPeer* peer = &host->peers[peerID];
    enet_peer_send(peer, flags, enet_packet);
}
