#pragma once
#include "core/core.h"
#include "core/net/v4/packet/packet.hpp"


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


    void ServerReceivePacket(Entity clientEntity_, Packet &packet) 
    {
    }
}