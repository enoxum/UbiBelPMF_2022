#include "server_state_sync_system.h"
#include "core/engine.h"
#include "core/net/common/net.h"
#include "core/net/server/server.h"
#include "core/net/server/enet_server_system.h"
#include "core/net/common/message.h"

using namespace dagger;
using namespace dagger::net;

void ServerStateSyncSystem::Run()
{
    auto& registry = Engine::Registry();
    auto& ctx = registry.ctx<server::NetworkContext>();

    auto& clientEntityMap = registry.ctx<ClientEntityMap>().map;
    // TODO: iterate over NetworkedComponents
    registry.view<NetworkedTag, Transform>().each([&](auto _, const Transform& transform_) {
        for (const auto& [_, clientEntity] : clientEntityMap) 
        {
            ctx.packetSignal.publish(clientEntity, Packet{transform_});
        }
    });

}
