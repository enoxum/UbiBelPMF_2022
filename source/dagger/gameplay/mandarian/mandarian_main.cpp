#include "mandarian_main.h"

#include "core/graphics/shaders.h"
#include "core/graphics/window.h"
#include "core/graphics/animation.h"

#include "mandarian_controller.h"
#include "mandarian_enemy.h"
#include "mandarian_camera_focus_system.h"
#include "mandarian_spell_system.h"

#include "mandarian_level.h"
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

void MandarianGame::GenerateMap(String path, int mapHeight, int mapWidth, int borderHeight, int borderWidth) {
    std::ofstream myfile;
    myfile.open(path);
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0,1.0);

    for (int i = 0; i < mapHeight; i++) {
        for (int j = 0; j < mapWidth; j++) {
            if (i < (mapHeight - borderHeight) / 2 || i > (mapHeight + borderHeight) / 2 ||
                j < (mapWidth - borderWidth) / 2 || j > (mapWidth + borderWidth) / 2) {
                myfile << "G";
            } else if (i == (mapHeight - borderHeight) / 2 || i == (mapHeight + borderHeight) / 2 ||
                j == (mapWidth - borderWidth) / 2 || j == (mapWidth + borderWidth) / 2 ) {
                myfile << "B";
            } else {
                myfile << "G";
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
    float zPos = 2.f;
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
            AddSprite(scale, tileSize, zPos, Space, "mandarian:ground", n, m, i, j);
            // add border
            if (lines[i][j] == 'B') {
                AddSprite(scale, tileSize, zPos, Space, "MiniWorldSprites:Nature:DeadTrees", n, m, i, j);
            }
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
    engine.AddPausableSystem<MandarianSpellSystem>();
    engine.AddPausableSystem<MandarianMovementConstraintSystem>();
    engine.AddPausableSystem<LevelSystem>();
    engine.AddPausableSystem<EnemyDeathSystem>();
    engine.AddPausableSystem<EnemyDemageSystem>();
}

void MandarianGame::WorldSetup()
{
    ShaderSystem::Use("standard");

    SetupCamera();
    GenerateMap("../source/dagger/gameplay/mandarian/map.txt", 100, 100, 50, 50);
    CreateMap();

    auto character = Character::Create();

    Engine::GetDefaultResource<MandarianSpellSystem>()->SetMandarian(character.entity); 
    Spell::Create("Aura of Mandarian", 1.0f, "aura:CAST:aura1", "aura:CAST").AddEffects(new FixTo(character.entity), new Aura(100.0f, 100.0f, character.entity)); 

    Engine::GetDefaultResource<EnemyDemageSystem>()->SetMandarian(character.entity);
    Engine::GetDefaultResource<EnemyMovementSystem>()->SetMandarian(character.entity);
    Engine::GetDefaultResource<LevelSystem>()->SetMandarian(character.entity);
}