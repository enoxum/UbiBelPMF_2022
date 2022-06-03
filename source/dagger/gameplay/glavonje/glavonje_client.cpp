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
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"
#include "core/game/transforms.h"
#include "core/graphics/sprite_render.h"
#include "core/graphics/tool_render.h"
#include "core/graphics/textures.h"
#include "core/graphics/animations.h"
#include "core/graphics/gui.h"
#include "tools/diagnostics.h"

using namespace dagger;
using namespace glavonje;


void GlavonjeClient::CoreSystemsSetup()
{
    auto& engine = Engine::Instance();
    engine.AddSystem<WindowSystem>();
    engine.AddSystem<InputSystem>();
    engine.AddSystem<ShaderSystem>();
    engine.AddSystem<TextureSystem>();
    engine.AddSystem<SpriteRenderSystem>();
    engine.AddSystem<AnimationSystem>();
    engine.AddSystem<TransformSystem>();
    engine.AddSystem<ClientENetSystem>();
#if !defined(NDEBUG)
    engine.AddSystem<DiagnosticSystem>();
    engine.AddSystem<GUISystem>();
    engine.AddSystem<ToolMenuSystem>();
    engine.AddSystem<ToolRenderSystem>();
#endif //!defined(NDEBUG)

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


