#include "core/net/packet/packet.h"
#include <algorithm>

using namespace dagger::packet;

// WARNING: ultra hacky & fragile code ahead
// packet consists of the raw data and one byte at the end which determines the type inside the variant

Packet packet::deserialize(UInt8* rawData_, UInt64 dataLength_) 
{
    Sequence<UInt8> data;
    data.reserve(dataLength_);
    std::copy_n(rawData_, dataLength_, std::back_inserter(data));

    UInt8 variantIdx = 0;
    data >> variantIdx;

    // TODO: this can probably be better solved with templates
    if (variantIdx == 0) 
    {
        Transform transform;
        deserialize(data, transform);
        return Packet{transform};
    }

    Logger::critical("Unrecognized type of packet for deserialization");
    return {};
}

Sequence<UInt8> packet::serialize(const Packet& packet_)
{
    Sequence<UInt8> data;

    std::visit([&](auto &&packetData) {
        serialize(packetData, packet_.var.index(), data);
    }, packet_.var);

    return data;
}

void packet::serialize(const Transform& transform_, UInt8 variantIdx_, Sequence<UInt8>& data_) 
{
    data_ << transform_.position.x 
          << transform_.position.y 
          << transform_.velocity.x
          << transform_.velocity.y
          << variantIdx_; // TODO: this shouldn't be the concern of the serialization implentation for Transform
}

void packet::deserialize(Sequence<UInt8>& data_, Transform& transform_) 
{
    data_ >> transform_.velocity.y 
          >> transform_.velocity.x 
          >> transform_.position.y 
          >> transform_.position.x;
}

void packet::serialize(const InputReceiver& input_, UInt8 variantIdx_, Sequence<UInt8>& data_) 
{
    // create a copy because .Get is non const 
    InputReceiver input = input_;
    // serialize inputs Left, Down, Right, Up
    for (auto& key : input.contexts) 
    {
        data_ << input.Get(key);
    }
    data_ << variantIdx_;
}

void packet::deserialize(Sequence<UInt8>& data_, InputReceiver& input_) 
{
    Float32 up, right, down, left;
    data_ >> up
          >> right
          >> down
          >> left;
    input_.values.insert({ "up", up });
    input_.values.insert({ "right", right });
    input_.values.insert({ "down", down });
    input_.values.insert({ "left", left });
}
