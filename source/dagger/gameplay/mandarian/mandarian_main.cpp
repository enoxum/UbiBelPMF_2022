#include "mandarian_main.h"

#include "core/graphics/shaders.h"
#include "core/graphics/window.h"

#include "mandarian_controller.h"
#include "mandarian_enemy.h"
#include "mandarian_camera_focus_system.h"
#include "mandarian_movement_constraint_system.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <random>

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

void MandarianGame::GenerateMap(String path, int map_height, int map_width, int border_height, int border_width) {
    std::ofstream myfile;
    myfile.open(path);
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0,1.0);

    for (int i = 0; i < map_height; i++) {
        for (int j = 0; j < map_width; j++) {
            if (i == (map_height - border_height) / 2 || i == (map_height + border_height) / 2 ||
                j == (map_height - border_height) / 2 || j == (map_height + border_height) / 2 ) {
                myfile << "B";
            } else {
                double number = distribution(generator);
                if (number < 0.05) {
                    myfile << "M";
                } else {
                    myfile << "G";
                }
            }
        }
        myfile << "\n";
    }
    myfile.close();
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

   
    float n = lines.size();
    float m = lines[0].size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // add grass
            AddSprite(scale, tileSize, zPos, Space, "MiniWorldSprites:Ground:TexturedGrass", n, m, i, j);
            // add mandarines
            if (lines[i][j] == 'M') {
                AddSprite(scale * 0.5f, tileSize, zPos, Space, "MiniWorldSprites:tangerin", n, m, i, j);
            } 
            // add border
            if (lines[i][j] == 'B') {
                AddSprite(scale, tileSize, zPos, Space, "MiniWorldSprites:Nature:DeadTrees", n, m, i, j);
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
    engine.AddPausableSystem<MandarianMovementConstraintSystem>();
    engine.AddPausableSystem<EnemyMovementSystem>();
}

void MandarianGame::WorldSetup()
{
    ShaderSystem::Use("standard");

    SetupCamera();
    GenerateMap("../source/dagger/gameplay/mandarian/map.txt", 100, 100, 50, 50);
    CreateMap();

    auto character = Character::Create();
    CreateEnemies(character.entity);    
}