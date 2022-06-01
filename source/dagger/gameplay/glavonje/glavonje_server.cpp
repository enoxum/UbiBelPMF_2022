#include "glavonje_server.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/game/transforms.h"

#include "core/net/server/server.h"
#include "core/net/server/enet_server_system.h"
#include "core/net/server/server_state_sync_system.h"

using namespace dagger;
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
}
