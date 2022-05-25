#pragma once

#include "core/system.h"
#include "core/core.h"
#include "core/net/v4/packet/packet.hpp"
#include <enet/enet.h>
    
using namespace dagger;
using namespace dagger::packet;

class ClientENetSystem : public System
{
    inline String SystemName() { return "Client ENet System"; }

    void SpinUp() override;
    void Run() override;
    void WindDown() override;

private:
    ENetHost* InitENetHost();
    ENetPeer* ConnectToServer(ENetHost* host_, const String& hostname_, UInt16 port_);
    void SendPacketToServer(const Packet& packet_);
};