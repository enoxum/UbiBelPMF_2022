#include "glavonje_server.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/game/transforms.h"

using namespace dagger;
using namespace glavonje;

void GlavonjeServer::CoreSystemsSetup()
{
    auto& engine = Engine::Instance();
    engine.AddSystem<InputSystem>();
    engine.AddSystem<TransformSystem>();
}

void GlavonjeServer::GameplaySystemsSetup()
{

}

void GlavonjeServer::WorldSetup()
{
}
