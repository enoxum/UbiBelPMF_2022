#include "mandarian_main.h"

#include "core/graphics/shaders.h"
#include "core/graphics/window.h"

#include "mandarian_controller.h"
#include "mandarian_enemy.h"
#include "mandarian_camera_focus_system.h"

#include <fstream>
#include <iostream>
#include <vector>

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

void AddSprite(Vector2 scale, float tileSize, float zPos, float Space, std::string spriteName, int width, int height, int i, int j) {
    auto& reg = Engine::Registry();
    auto entity = reg.create();
    auto& sprite = reg.get_or_emplace<Sprite>(entity);
    AssignSprite(sprite, spriteName);
    sprite.size = scale * tileSize;
    auto& transform = reg.emplace<Transform>(entity);
    transform.position.x = (0.5f + j + j * Space - static_cast<float>(width * (1 + Space)) / 2.f) * tileSize;
    transform.position.y = (0.5f + i + i * Space - static_cast<float>(height * (1 + Space)) / 2.f) * tileSize;
    transform.position.z = zPos;
}

void MandarianGame::CreateMap() 
{
    
    Vector2 scale(1, 1);
    constexpr float tileSize = 30.f;
    float zPos = 1.f;
    float Space = 0.0f;

    std::string line;
    std::ifstream myfile("../source/dagger/gameplay/mandarian/map.txt");   
    std::vector<std::string> lines;

    while (getline(myfile,line)) {
        lines.push_back(line);
    }
    myfile.close();

   
    int height = lines.size();
    int width = lines[0].size();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // add grass
            AddSprite(scale, tileSize, zPos, Space, "MiniWorldSprites:Ground:TexturedGrass", width, height, i, j);
            // add mandarines
            if (lines[i][j] == 'M') {
                AddSprite(scale * 0.5f, tileSize, zPos, Space, "MiniWorldSprites:tangerin", width, height, i, j);
            }
        }
    }
    
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
    CreateMap();

    auto character = Character::Create();
    CreateEnemies(character.entity);    
}