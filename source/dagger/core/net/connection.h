#pragma once

#include "core/net/message.h"
#include "core/core.h"

namespace dagger {
    namespace net {
        template<typename T>
        class Connection : public std::enable_shared_from_this<Connection<T>>
        {
        public:
            Connection() {}

            virtual ~Connection() {}

        public:
            bool ConnectToServer();
            bool Disconnect();
            bool IsConnected() const;
        
        public:
            bool Send(const Message<T>& msg);
        
        protected:
            // add a socket here

            TSQueue<Message<T>> m_outMessageQueue;
            // the owner of Connection should suply the inMessageQueue
            TSQueue<OwnedMessage<T>>& m_inMessageQueue;
        };
    }
}