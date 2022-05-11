#pragma once
#include "core/core.h"

namespace dagger {
    namespace net {
        template <typename T, ENUM_ONLY(T)>
        struct MessageHeader 
        {
            T id{};
            UInt32 size = 0; 
        };

        template <typename T, ENUM_ONLY(T)>
        struct Message
        {
            MessageHeader<T> header{};
            Sequence<UInt8> body;

            size_t Size() const 
            {
                return sizeof(MessageHeader<T>) + body.size();
            }

            template<typename DataType, IS_TRIVIALLY_COPYABLE(DataType)>
            friend Message<T>& operator << (Message<T>& msg, const DataType& data)
            {
                size_t insertion_idx = msg.body.size();
                msg.body.resize(msg.body.size() + sizeof(DataType));
                std::memcpy(msg.body.data() + insertion_idx, &data, sizeof(DataType));
                msg.header.size = msg.Size();
                return msg;
            }

            template<typename DataType, IS_TRIVIALLY_COPYABLE(DataType)>
            friend Message<T>& operator >> (Message<T>& msg, DataType& data)
            {
                size_t take_idx = msg.body.size() - sizeof(DataType);
                std::memcpy(&data, msg.body.data() + take_idx, sizeof(DataType));
                msg.body.resize(take_idx);
                msg.header.size = msg.Size();
                return msg;
            }
        };

        template<typename T>
        class Connection;
    
        template <typename T>
        struct OwnedMessage 
        {
            SharedPtr<Connection<T>> remote = nullptr;
            Message<T> msg;
        };
    }
}