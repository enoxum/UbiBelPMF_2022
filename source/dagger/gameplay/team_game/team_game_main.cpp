#include "team_game_main.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/audio.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"
#include "core/game/transforms.h"

#include "gameplay/common/simple_collisions.h"
#include "player_controller.h"
#include "item_collection.h"
#include "solid_object_interaction.h"
#include "gravity.h"
#include "gameplay/team_game/Utilities/string_utility.h"
#include "gameplay/team_game/Utilities/map_generator_utility.h"


#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <map>


using namespace dagger;
using namespace team_game;

void TeamGame::GameplaySystemsSetup()
{
    auto& engine = Engine::Instance();
    engine.AddSystem<SimpleCollisionsSystem>();
    engine.AddPausableSystem<PlayerControlSystem>();
    engine.AddPausableSystem<SolidObjectInteractionSystem>();
    engine.AddPausableSystem<ItemCollectionSystem>();
    engine.AddPausableSystem<GravitySystem>();
}

void TeamGame::WorldSetup()
{
    ShaderSystem::Use("standard");

    Engine::GetDefaultResource<Audio>()->PlayLoop("escape");

    auto* camera = Engine::GetDefaultResource<Camera>();
    camera->mode = ECameraMode::FixedResolution;
    camera->size = { 1200, 900 };
    camera->zoom = 1;
    camera->position = { 0, 0, 0 };
    camera->Update();

    team_game::SetupWorld();
}

void team_game::SetupWorld()
{
    float zPos = 1.f;
    std::string fileName = "level_loader.txt";

    team_game::initPlayer(zPos);   
    team_game::initMap(zPos, fileName);
    
}
