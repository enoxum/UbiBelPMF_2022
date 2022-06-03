#pragma once

#include <variant>
#include "core/core.h"
#include "core/net/common/message.h"

#include "core/game/transforms.h"
#include "core/input/inputs.h"

namespace dagger::packet {

struct Packet 
{
    // Packet() = default;
    // Packet(const Transform& transform_);

    // TODO: somehow connect NetworkedComponents and this
    std::variant<
        Transform,
        InputReceiver
    > var;
};

Packet deserialize(UInt8* rawData_, UInt64 dataLength_);
Sequence<UInt8> serialize(const Packet& packet_);

void serialize(const Transform& transform_, UInt8 variantIdx_, Sequence<UInt8>& data_);
void deserialize(Sequence<UInt8>& data_, Transform& transform_);

void serialize(const InputReceiver& input_, UInt8 variantIdx_, Sequence<UInt8>& data_);
void deserialize(Sequence<UInt8>& data_, InputReceiver& input_);

template<typename T, IS_TRIVIALLY_COPYABLE(T)>
Sequence<UInt8>& operator << (Sequence<UInt8>& data_, const T& field)
{
    size_t insertionIdx = data_.size();
    data_.resize(data_.size() + sizeof(T));
    std::memcpy(data_.data() + insertionIdx, &field, sizeof(T));
    return data_;
}

template<typename T, IS_TRIVIALLY_COPYABLE(T)>
Sequence<UInt8>& operator >> (Sequence<UInt8>& data_, T& field)
{
    size_t takeIdx = data_.size() - sizeof(T);
    std::memcpy(&field, data_.data() + takeIdx, sizeof(T));
    data_.resize(takeIdx);
    return data_;
}



}
