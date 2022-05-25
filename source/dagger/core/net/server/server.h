#pragma once
#include "core/core.h"
#include "core/net/v4/packet/packet.hpp"


namespace server {

    using namespace dagger::packet;

    struct NetworkContext 
    {
        // queue of clients that should be created on next tick
        Sequence<Entity> pendingCreatedClients;

        entt::sigh<void(Entity, const Packet&)> packetSignal;
        auto PacketSink() { return entt::sink{packetSignal}; }
    };

    Entity MakeClientEntity(Registry &registry);


    void ServerReceivePacket(Entity clientEntity_, Packet &packet) 
    {
    }
}