#pragma once

#include "core/core.h"
#include "core/net/message.h"

namespace dagger
{
    namespace net
    {
        template<typename T>
        class IServer 
        {
        public:
            IServer(UInt16 port) 
            {

            }

            virtual ~IServer()
            {
                Stop();
            }
        public:
            bool Start()
            {
                WaitForClientConnection();
            }

            void Stop()
            {

            }

            void WaitForClientConnection() 
            {

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

            void MessageAllClients(const Message& msg)
            {

            }

            void Update(size_t maxNumberOfMessages_ = SIZE_MAX)
            {
                size_t msg_count = 0;
                while (msg_count < maxNumberOfMessages_ && !m_inMessageQueue.empty())
                {
                    // TODO: change to pop_front
                    auto ownedMsg = m_inMessageQueue.front();
                    m_inMessageQueue.pop();

                    OnMessage(ownedMsg.remote, ownedMsg.msg);
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
            TSQueue<OwnedMessage<T> m_inMessageQueue;
        }
    }
}