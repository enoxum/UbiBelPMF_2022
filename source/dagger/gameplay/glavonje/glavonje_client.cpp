#include "glavonje_client.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"
#include "core/game/transforms.h"
#include <enet/enet.h>

#include "core/net/client/client.h"
#include "core/net/client/enet_client_system.h"

using namespace dagger;
using namespace glavonje;


void GlavonjeClient::CoreSystemsSetup()
{
    auto& engine = Engine::Instance();
    engine.AddSystem<InputSystem>();
    engine.AddSystem<TransformSystem>();
}

void GlavonjeClient::GameplaySystemsSetup()
{

}

void GlavonjeClient::WorldSetup(){
    // ShaderSystem::Use("standard");
    // auto* camera = Engine::GetDefaultResource<Camera>();
    // camera->mode = ECameraMode::FixedResolution;
    // camera->size = { 800, 600 };
    // camera->zoom = 1;
    // camera->position = { 0, 0, 0 };
    // camera->Update();



}


