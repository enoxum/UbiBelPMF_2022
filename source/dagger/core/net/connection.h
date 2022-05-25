#pragma once

#include "core/net/message.h"
#include "core/core.h"
#include <enet/enet.h>

// Temporary
enum class EMsgType : UInt32 {
    Shoot,
};

namespace dagger {
    namespace net {
        template<typename T>
        class Connection : public std::enable_shared_from_this<Connection<T>>
        {
        public:
            enum class EOwner 
            {
                Server, Client
            };

            Connection(EOwner owner_, ViewPtr<TSQueue<OwnedMessage<T>>> inMessageQueue_, ViewPtr<ENetAddress> address_ = nullptr, UInt8 out_conn_num_ = 2) 
                : m_owner(owner_), m_inMessageQueue(*inMessageQueue_)
            {

                InitENet(address_, out_conn_num_);
            }

            virtual ~Connection() 
            {
                DeInitENet();
            }

        public:
            void ConnectToClient(UInt64 id_ = 0)
            {
                if (m_owner == EOwner::Server) 
                {
                    m_id = id_;
                }
            } 

            bool ConnectToServer(const String& hostName_, UInt16 port_) 
            {
                if (m_owner == EOwner::Client)
                {
                    ENetAddress address;
                    enet_address_set_host(&address, hostName_.c_str());
                    address.port = port_;

                    m_peer = enet_host_connect(m_host.get(), &address, 2, 0);
                    if (!m_peer) {
                        Logger::critical(fmt::format("Couldn't connect to peer: {}:{}", hostName_, port_));
                        return false;
                    }
                    return true;
                }
                return false;
            }
            bool Disconnect() 
            { 
                DeInitENet();
                return true; 
            }
            bool IsConnected() const 
            { 
                return true; // TODO: change this 
            }
            UInt64 GetId() const
            {
                return m_id;
            } 
        public:
            void Send(const Message<T>& msg) 
            {
                UInt32 flags = 0;
                ENetPacket* packet = enet_packet_create(&msg, msg.Size(), flags);
                enet_peer_send(m_peer.get(), flags, packet);
            }

            template<typename OnConnect, typename OnDisconnect, typename OnMessage>
            void Listen(OnConnect onConnect_, OnDisconnect onDisconnect_, OnMessage onMessage_) 
            {
                ENetEvent event;

                while (enet_host_service(m_host.get(), &event, 1000) > 0) {
                    const auto peerID = event.peer->incomingPeerID;

                    switch (event.type) {
                        case ENET_EVENT_TYPE_CONNECT: 
                        {
                            enet_peer_timeout(event.peer, 0, 10000, 30000);
                            onConnect_(peerID);
                            fmt::print("Connected %d", peerID);
                            break;
                        }
                        case ENET_EVENT_TYPE_DISCONNECT: 
                        {
                            onDisconnect_(peerID);
                            fmt::print("Disonnected %d", peerID);
                            break;
                        }
                        // UMESTO CALL BACKOVA KORISTI ENTT SINK 
                        // SLANJE PORUKA IZMEDJU CLIENTA I SERVERA
                        // STATE SYNC VS INPUT
                        case ENET_EVENT_TYPE_RECEIVE: 
                        {
                            onMessage_(event.packet);
                            // clean up the packet now that we're done using it
                            enet_packet_destroy(event.packet);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }

        private:
            bool InitENet(ViewPtr<ENetAddress> address_, UInt32 out_conn_num_) 
            {
                m_host = enet_host_create(address_.get(), out_conn_num_, 2, 0, 0);
                if (!m_host) {
                    Logger::critical("Failed to create ENet host");
                }
                return true;
            }

            void DeInitENet() 
            {
                enet_host_destroy(m_host.get());
                enet_deinitialize();
            }
        
        protected:
            // add a socket here
            ViewPtr<ENetPeer> m_peer{nullptr};
            ViewPtr<ENetHost> m_host{nullptr};
            EOwner m_owner;
            UInt64 m_id{0};

            // this queue has messages that will be sent to the remote side 
            TSQueue<Message<T>> m_outMessageQueue;
            // this queue holds all messages that are received from the remote side
            // the owner of Connection should suply the inMessageQueue
            TSQueue<OwnedMessage<T>>& m_inMessageQueue;
        };
    }
}