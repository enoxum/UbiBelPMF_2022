#include "mandarian_main.h"

#include "core/graphics/shaders.h"
#include "core/graphics/window.h"

using namespace mandarian;
using namespace dagger;

void MandarianGame::SetupCamera()
{
    auto *camera = Engine::GetDefaultResource<Camera>();
    camera->mode = ECameraMode::FixedResolution;
    camera->size = { 800, 600 };
    camera->zoom = 1;
    camera->position = { 0, 0, 0 };
    camera->Update();
}

void MandarianGame::GameplaySystemsSetup() 
{

}

void MandarianGame::WorldSetup()
{
    ShaderSystem::Use("standard");

    SetupCamera();
}