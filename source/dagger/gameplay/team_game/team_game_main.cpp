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
//#include <unistd.h>
// #include <windows.h>
#include <vector>
#include <map>

#include "gameplay/platformer/camera_focus.h"
#include <gameplay/team_game/storage.h>
#include <core/graphics/text.h>
#include <gameplay/team_game/timer.h>
#include "mainmenu.h"


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
    engine.AddPausableSystem<StorageSystem>();
    engine.AddPausableSystem<TimerSystem>();
    engine.AddSystem<mainmenu>();


    engine.AddSystem<platformer::CameraFollowSystem>();
}

void TeamGame::WorldSetup()
{
    ShaderSystem::Use("standard");

    Engine::GetDefaultResource<Audio>()->PlayLoop("escape");

    auto* camera = Engine::GetDefaultResource<Camera>();
    camera->mode = ECameraMode::FixedResolution;
    camera->size = { 800, 600 };
    camera->zoom = 0.5;
    camera->position = { 0, 0, 0 };
    camera->Update();

    team_game::SetupWorld();
}

void team_game::SetupWorld()
{
    auto& engine = Engine::Instance();
    auto& reg = engine.Registry();

    float zPos = 1.f;
    std::string fileName = "level_loader.txt";
    
    {
        auto menu = reg.create();
        auto& sprite = reg.emplace<Sprite>(menu);
        AssignSprite(sprite, "Background:background_with_introduction");
        sprite.size = { 1700, 1220 };
        auto mm = reg.emplace<MainMenu_>(menu);
        auto& text = reg.emplace<Text>(menu);
        text.spacing = 0.6f;
        String msg = "Press Enter to start the game!";
        text.Set("pixel-font", msg, { 0, -9 ,0 });

        //In front of you is a room where you need to find a way out. 
        //You can move using the left, right and up arrows. Collect lost items and use them in the right way,
        //to be one step closer to getting out. When you collect the item and get to the place where you think you should use it,
        //  press the number button on the keyboard that corresponds to the ordinal number of the item in storage and you will see
        //  if you have successfully overcome that obstacle.
        //Pay attention to the timer to make the final score better. Good luck!
      
    }

    {
        engine.ToggleSystemsPause(true);
        team_game::initPlayer(zPos);
        team_game::initMap(zPos, fileName);
        
    }
    // {
    //     auto entity = reg.create();
    //     auto& sprite = reg.emplace<Sprite>(entity);
    //     AssignSprite(sprite, "logos:character");
    //     float ratio = sprite.size.y / sprite.size.x;
    //     sprite.size = { 100 / ratio, 100  };

    //     auto& transform = reg.emplace<Transform>(entity);
    //     transform.position = { 0, 0, zPos };

    //     auto& col = reg.emplace<SimpleCollision>(entity);
    //     col.size = sprite.size;

    //     reg.emplace<Player>(entity);
    //     reg.emplace<Gravity>(entity);

    //     reg.emplace<platformer::CameraFollowFocus>(entity);
    // }

    // {
    //     auto entity = reg.create();
    //     auto& sprite = reg.emplace<Sprite>(entity);
    //     AssignSprite(sprite, "logos:dagger");
    //     float ratio = sprite.size.y / sprite.size.x;
    //     sprite.size = { 100 / ratio, 100  };

    //     auto& transform = reg.emplace<Transform>(entity);
    //     transform.position = { 330 , 100, zPos };

    //     auto& col = reg.emplace<SimpleCollision>(entity);
    //     col.size = sprite.size;

    //     Item& i = reg.emplace<Item>(entity);
    //     i.id = "Dagger 1";
    // }

    // {
    //     auto entity = reg.create();
    //     auto& sprite = reg.emplace<Sprite>(entity);
    //     AssignSprite(sprite, "logos:ubisoft");
    //     float ratio = sprite.size.y / sprite.size.x;
    //     sprite.size = { 100 / ratio, 100 };

    //     auto& transform = reg.emplace<Transform>(entity);
    //     transform.position = { -200 , 100, zPos };

    //     auto& col = reg.emplace<SimpleCollision>(entity);
    //     col.size = sprite.size;

    //     Item& i = reg.emplace<Item>(entity);
    //     i.id = "Ubisoft";

    // }


    // {
    //     auto entity = reg.create();
    //     auto& sprite = reg.emplace<Sprite>(entity);
    //     AssignSprite(sprite, "platformerRocks:SimpleRockPlatform");
    //     float ratio = sprite.size.y / sprite.size.x;
    //     sprite.size = { 180, 30  };

    //     auto& transform = reg.emplace<Transform>(entity);
    //     transform.position = { -200 , 0, zPos };

    //     auto& col = reg.emplace<SimpleCollision>(entity);
    //     col.size = sprite.size;
        
    //     Platform& i = reg.emplace<Platform>(entity);
    //     i.id = "PLTLeft";
    // }


    // {
    //     auto entity = reg.create();
    //     auto& sprite = reg.emplace<Sprite>(entity);
    //     AssignSprite(sprite, "platformerRocks:SimpleRockPlatform");
    //     float ratio = sprite.size.y / sprite.size.x;
    //     sprite.size = { 120, 30  };

    //     auto& transform = reg.emplace<Transform>(entity);
    //     transform.position = { 330 , 0, zPos };

    //     auto& col = reg.emplace<SimpleCollision>(entity);
    //     col.size = sprite.size;
        
    //     Platform& i = reg.emplace<Platform>(entity);
    //     i.id = "PLTRight";
    // }

    // {
    //     auto entity = reg.create();
    //     auto& sprite = reg.emplace<Sprite>(entity);
    //     AssignSprite(sprite, "platformerRocks:SimpleRockPlatform");
    //     float ratio = sprite.size.y / sprite.size.x;
    //     sprite.size = { 500, 30  };

    //     auto& transform = reg.emplace<Transform>(entity);
    //     transform.position = { 0 , -80, zPos };

    //     auto& col = reg.emplace<SimpleCollision>(entity);
    //     col.size = sprite.size;
        
    //     Platform& i = reg.emplace<Platform>(entity);
    //     i.id = "PLTBottom";
    // }

    // {
    //     auto entity = reg.create();
    //     auto& sprite = reg.emplace<Sprite>(entity);
    //     AssignSprite(sprite, "platformerRocks:SimpleRockPlatform");
    //     float ratio = sprite.size.y / sprite.size.x;
    //     sprite.size = { 300, 30  };

    //     auto& transform = reg.emplace<Transform>(entity);
    //     transform.position = { 0 , 150, zPos };

    //     auto& col = reg.emplace<SimpleCollision>(entity);
    //     col.size = sprite.size;
        
    //     Platform& i = reg.emplace<Platform>(entity);
    //     i.id = "PLTTop";
    // }

     {
         auto timer = reg.create();
         auto& text = reg.emplace<Text>(timer);
         text.spacing = 0.6f;
         reg.emplace<Time>(timer);
     }


}
