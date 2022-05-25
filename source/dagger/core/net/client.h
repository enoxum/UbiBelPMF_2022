#include "core/core.h"
#include "core/net/connection.h"
#include "core/net/message.h"
#include <thread>

namespace dagger 
{
    namespace net 
    {
        template<typename T>
        class IClient
        {
        public:
            IClient() {}

            virtual ~IClient() 
            {
                Disconnect();
            }

        public:
            bool Connect(const std::string& host_, const UInt16 port_) 
            {
                m_connection = SharedPtr<Connection<T>>{new Connection<T>{Connection<T>::EOwner::Client, &m_inMessageQueue}}; 
                Start();
                return m_connection->ConnectToServer(host_, port_);
            }

            bool Start()
            {
                Logger::info("Started listening on client");
                m_listening_thread = std::thread([this]() {
                    // TODO: refactor
                    while (1) {
                        m_connection->Listen(
                            [&](UInt16 peerID)  // onConnect
                            {
                                Logger::info(fmt::format("New connection"));
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


            void Disconnect() 
            {
                if (IsConnected()) 
                {
                    m_connection->Disconnect();
                }
                // cleanup
                if (m_listening_thread.joinable()) 
                {
                    m_listening_thread.join();
                }
            }

            bool IsConnected() 
            {
                return m_connection && m_connection->IsConnected();
            }

            TSQueue<OwnedMessage<T>>& Incoming()
            {
                return m_inMessageQueue;
            }
        public:
            void Send(const Message<T>& msg) {
                m_connection->Send(msg);
            }
        protected:
            SharedPtr<Connection<T>> m_connection;
            std::thread m_listening_thread;
        private:
            // stores incoming messages
            TSQueue<OwnedMessage<T>> m_inMessageQueue;
        };
    }
}