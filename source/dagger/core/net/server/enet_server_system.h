#pragma once

#include "core/system.h"
#include "core/core.h"
#include "core/net/v4/packet/packet.hpp"
#include <enet/enet.h>
    
using namespace dagger;
using namespace dagger::packet;

struct PeerID
{
    UInt16 value;
};

struct ClientEntityMap 
{
    Map<UInt16, Entity> map;
};

class ServerENetSystem : public System
{
    inline String SystemName() { return "Server ENet System"; }

    void SpinUp() override;
    void Run() override;
    void WindDown() override;

private:
    ENetHost* InitENetHost(UInt16 port_);
    void SendPacketToClient(Entity clientEntity, const Packet& packet);
};