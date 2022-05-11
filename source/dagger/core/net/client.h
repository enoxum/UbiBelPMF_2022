#include "core/core.h"
#include "core/net/connection.h"
#include "core/net/message.h"

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
                try
                {
                    m_connection = OwningPtr<Connection<T>>{}; // TODO

                    // resolve hostname or smth
                } catch (std::exception& e)
                {
                    Logger::critical("Failed to connect");
                    return false;
                }
                return true;
            }

            void Disconnect() 
            {
                if (IsConnected()) 
                {
                    m_connection->Disconnect();
                }
                // cleanup
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
            // context or thread or smth

            OwningPtr<Connection<T>> m_connection;
        private:
            // stores incoming messages
            TSQueue<OwnedMessage<T>> m_inMessageQueue;
        };
    }
}