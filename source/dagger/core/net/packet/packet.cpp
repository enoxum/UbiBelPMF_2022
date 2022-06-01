#include "core/net/packet/packet.h"

using namespace dagger::packet;

Packet dagger::packet::deserialize(UInt8* data_, UInt64 dataLength_) 
{
    return Packet{};
}

Sequence<UInt8> dagger::packet::serialize(const Packet& packet_)
{
    return Sequence<UInt8>{};
}

