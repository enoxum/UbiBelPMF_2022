#pragma once
#include "core/core.h"
#include "core/net/packet/packet.h"


namespace client {

    using namespace dagger::packet;

    struct NetworkContext 
    {
        Sequence<Entity> createdEntities;
        Sequence<Entity> destroyedEntities;

        entt::sigh<void(const Packet&)> packetSignal;
        auto PacketSink() { return entt::sink{packetSignal}; }
    };

    Entity MakeClientEntity(Registry &registry);


    inline void ClientReceivePacket(Entity clientEntity_, Packet &packet) 
    {
    }
}