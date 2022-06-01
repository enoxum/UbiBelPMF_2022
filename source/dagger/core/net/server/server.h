#pragma once
#include "core/core.h"
#include "core/net/packet/packet.h"


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


    inline void ServerReceivePacket(Entity clientEntity_, Packet &packet) 
    {
    }
}