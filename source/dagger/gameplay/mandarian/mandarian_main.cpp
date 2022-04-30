#include "mandarian_main.h"

#include "core/graphics/shaders.h"
#include "core/graphics/window.h"

#include "mandarian_controller.h"
#include "mandarian_enemy.h"
#include "mandarian_camera_focus_system.h"
#include "mandarian_level.h"

using namespace mandarian;
using namespace dagger;


void MandarianGame::SetupCamera()
{
    auto *camera = Engine::GetDefaultResource<Camera>();
    camera->mode = ECameraMode::FixedResolution;
    camera->size = { 800, 600 };
    camera->zoom = 2;
    camera->position = { 0, 0, 0 };
    camera->Update();
}

void MandarianGame::CreateMap() 
{
    auto& reg = Engine::Registry();
    Vector2 scale(1, 1);
    constexpr int height = 50;
    constexpr int width = 50;
    constexpr float tileSize = 20.f;
    float zPos = 1.f;
    constexpr float Space = 0.0f;

    // add grass
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            auto entity = reg.create();
            auto& sprite = reg.get_or_emplace<Sprite>(entity);
            
            AssignSprite(sprite, "MiniWorldSprites:Ground:TexturedGrass");
            sprite.size = scale * tileSize;
            auto& transform = reg.emplace<Transform>(entity);
            transform.position.x = (0.5f + j + j * Space - static_cast<float>(width * (1 + Space)) / 2.f) * tileSize;
            transform.position.y = (0.5f + i + i * Space - static_cast<float>(height * (1 + Space)) / 2.f) * tileSize;
            transform.position.z = zPos;
        }     
    }

}

void MandarianGame::GameplaySystemsSetup() 
{
    auto &engine = Engine::Instance();

    engine.AddPausableSystem<SimpleCollisionsSystem>();
    engine.AddPausableSystem<EnemyMovementSystem>();
    engine.AddPausableSystem<MandarianControllerSystem>();
    engine.AddPausableSystem<SimplePhysicsSystem>();
    engine.AddPausableSystem<MandarianCameraFocusSystem>();
    engine.AddPausableSystem<LevelSystem>();
}

void MandarianGame::WorldSetup()
{
    ShaderSystem::Use("standard");

    SetupCamera();
    CreateMap();

    auto character = Character::Create();

    Engine::GetDefaultResource<EnemyMovementSystem>()->SetMandarian(character.entity);
    Engine::GetDefaultResource<LevelSystem>()->SetMandarian(character.entity);

    for (int i = 0; i < 10; i++)
    {
        Float32 xPos = 200 * (rand() / static_cast<Float32>(RAND_MAX));
        Float32 yPos = 200 * (rand() / static_cast<Float32>(RAND_MAX));
        Mandarin::Create(10u, { xPos, yPos });
    }
}