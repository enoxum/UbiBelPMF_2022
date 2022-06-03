#include "glavonje_server.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/game/transforms.h"

#include "core/net/common/net.h"
#include "core/net/server/server.h"
#include "core/net/server/enet_server_system.h"
#include "core/net/server/server_state_sync_system.h"

using namespace dagger;
using namespace dagger::net;
using namespace glavonje;

void GlavonjeServer::CoreSystemsSetup()
{
    auto& engine = Engine::Instance();
    engine.AddSystem<InputSystem>();
    engine.AddSystem<TransformSystem>();
    engine.AddSystem<ServerENetSystem>();
    engine.AddSystem<ServerStateSyncSystem>();
}

void GlavonjeServer::GameplaySystemsSetup()
{

}

void GlavonjeServer::WorldSetup()
{
    // TEMP
    auto& reg = Engine::Registry();
    auto ent = reg.create();
    reg.emplace<NetworkedTag>(ent);
    auto& tr = reg.emplace<Transform>(ent);
    tr.position.x = 4;
    tr.position.y = 3;

}
