#pragma once

#include "core/core.h"
#include "core/net/message.h"
#include <thread>
#include <enet/enet.h>

namespace dagger
{
    namespace net
    {
        template<typename T>
        class IServer 
        {
        public:
            IServer(UInt16 port_) 
            {
                ENetAddress address;
                enet_address_set_host(&address, "127.0.0.1");
                address.port = port_;
                // add connection for server

                auto connection = SharedPtr<Connection<T>>{new Connection<T>{Connection<T>::EOwner::Server, &m_inMessageQueue, &address, 32}};
                m_connections.emplace_back(connection);
            }

            virtual ~IServer()
            {
                Stop();
            }
        public:
            bool Start()
            {
                Logger::info("Started server");
                m_listening_thread = std::thread([this]() {
                    // TODO: refactor
                    while (1) {
                        m_connections.front()->Listen(
                            [&](UInt16 peerID)  // onConnect
                            {
                                // auto queue = ViewPtr<TSQueue<OwnedMessage<T>>>{m_inMessageQueue}
                                auto connection = SharedPtr<Connection<T>>{new Connection<T>{Connection<T>::EOwner::Server, &m_inMessageQueue}};
                                m_connections.emplace_back(connection);
                                m_connections.back()->ConnectToClient(m_id_counter++); 

                                Logger::info(fmt::format("New connection: {}", m_connections.back()->GetId()));
                            }, 
                            [](UInt16 peerID)
                            {
                                Logger::info(fmt::format("Disconnected: {}", peerID));
                            },
                            [](ENetPacket* packet)
                            {
                                Logger::info(fmt::format("Got packet"));
                                // TODO: deserialize to Message<T>
                            });
                    }
                });
            }

            void Stop()
            {
                if (m_listening_thread.joinable()) {
                    m_listening_thread.join();
                }
            }


            void MessageClient(SharedPtr<Connection<T>> client, const Message<T>& msg) 
            {
                if (client && client->IsConnected()) 
                {
                    client->Send(msg);
                } 
                else
                {
                    OnClientDisconnect(client);
                    // TODO remove client connection
                }
            }

            void MessageAllClients(const Message<T>& msg, SharedPtr<Connection<T>> ignore_connection_ = nullptr)
            {
                for (auto& client : m_connections)
                {
                    if (client && client->IsConnected())
                    {
                        if (client != ignore_connection_)
                        {
                            client->Send(msg);
                        }
                    } 
                    else 
                    {
                        OnClientDisconnect(client);
                    }
                }
                // remove disconnected

            }

            void Update(UInt64 maxNumberOfMessages_ = SIZE_MAX)
            {
                UInt64 msg_count = 0;
                while (msg_count < maxNumberOfMessages_ && !m_inMessageQueue.empty())
                {
                    auto ownedMsg = m_inMessageQueue.pop_front();
                    OnMessage(ownedMsg.remote, ownedMsg.msg);
                    msg_count++;
                }
            }

        protected:
            virtual bool OnClientConnect(SharedPtr<Connection<T>> client)
            {
                return false;
            }

            virtual bool OnClientDisconnect(SharedPtr<Connection<T>> client) 
            {

            }

            virtual void OnMessage(SharedPtr<Connection<T>> client, Message<T>& msg)
            {

            }
        protected:
            Sequence<SharedPtr<Connection<T>>> m_connections;

            UInt64 m_id_counter{};
            TSQueue<OwnedMessage<T>> m_inMessageQueue;
            std::thread m_listening_thread;
        };
    }
}