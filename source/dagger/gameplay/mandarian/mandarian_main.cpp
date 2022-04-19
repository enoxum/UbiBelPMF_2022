#include "mandarian_main.h"

#include "core/graphics/shaders.h"
#include "core/graphics/window.h"

#include "mandarian_controller.h"
#include "mandarian_enemy.h"
#include "mandarian_camera_focus_system.h"

using namespace mandarian;
using namespace dagger;


void MandarianGame::SetupCamera()
{
    auto *camera = Engine::GetDefaultResource<Camera>();
    camera->mode = ECameraMode::FixedResolution;
    camera->size = { 800, 600 };
    camera->zoom = 0.5;
    camera->position = { 0, 0, 0 };
    camera->Update();
}

void MandarianGame::CreateMap() 
{
    auto& reg = Engine::Registry();
    auto entity = reg.create();
    auto& sprite = reg.get_or_emplace<Sprite>(entity);
    AssignSprite(sprite, "logos:dagger");
    sprite.position.z = 10;
}

void MandarianGame::CreateEnemies(Entity mandarian)
{
    Enemy::Create({ -200.0f, -200.0f });
    Enemy::Create({ -200.0f,  200.0f });
    Enemy::Create({  200.0f, -200.0f });
    Enemy::Create({  200.0f,  200.0f });

    Engine::GetDefaultResource<EnemyMovementSystem>()->SetMandarian(mandarian);
}

void MandarianGame::GameplaySystemsSetup() 
{
    auto &engine = Engine::Instance();

    engine.AddPausableSystem<MandarianControllerSystem>();
    engine.AddPausableSystem<SimplePhysicsSystem>();
    engine.AddPausableSystem<MandarianCameraFocusSystem>();
    engine.AddPausableSystem<EnemyMovementSystem>();
}

void MandarianGame::WorldSetup()
{
    ShaderSystem::Use("standard");

    SetupCamera();
    //CreateMap();

    auto character = Character::Create();
    CreateEnemies(character.entity);    
}