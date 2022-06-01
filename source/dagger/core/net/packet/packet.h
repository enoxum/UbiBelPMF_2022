#pragma once

#include <variant>
#include "core/core.h"

namespace dagger::packet {

struct Jump {};
struct Shoot {};

struct Packet 
{
    double timestamp;
    std::variant<
        Jump,
        Shoot
    > var;
};

Packet deserialize(UInt8* data_, UInt64 dataLength_);
Sequence<UInt8> serialize(const Packet& packet_);

}
