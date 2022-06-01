#include "server_state_sync_system.h"
#include "core/engine.h"
#include "core/net/server/server.h"
#include "core/net/server/enet_server_system.h"

using namespace dagger;

void ServerStateSyncSystem::Run()
{
    auto& registry = Engine::Registry();
    auto& ctx = registry.ctx<server::NetworkContext>();

    Packet packet{};

    auto& clientEntityMap = registry.ctx<ClientEntityMap>().map;
    for (const auto& [_, clientEntity] : clientEntityMap) 
    {
        ctx.packetSignal.publish(clientEntity, packet);
    }
}
