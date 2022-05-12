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

#include "gameplay/platformer/camera_focus.h"
#include <gameplay/team_game/storage.h>


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

    {
        auto entity = reg.create();
        auto& sprite = reg.emplace<Sprite>(entity);
        AssignSprite(sprite, "logos:character");
        float ratio = sprite.size.y / sprite.size.x;
        sprite.size = { 100 / ratio, 100  };

        auto& transform = reg.emplace<Transform>(entity);
        transform.position = { 0, 0, zPos };

        auto& col = reg.emplace<SimpleCollision>(entity);
        col.size = sprite.size;

        reg.emplace<Player>(entity);
        reg.emplace<Gravity>(entity);

        reg.emplace<platformer::CameraFollowFocus>(entity);
    }

    {
        auto entity = reg.create();
        auto& sprite = reg.emplace<Sprite>(entity);
        AssignSprite(sprite, "logos:dagger");
        float ratio = sprite.size.y / sprite.size.x;
        sprite.size = { 100 / ratio, 100  };

        auto& transform = reg.emplace<Transform>(entity);
        transform.position = { 330 , 100, zPos };

        auto& col = reg.emplace<SimpleCollision>(entity);
        col.size = sprite.size;

        Item& i = reg.emplace<Item>(entity);
        i.id = "Dagger 1";
    }

    {
        auto entity = reg.create();
        auto& sprite = reg.emplace<Sprite>(entity);
        AssignSprite(sprite, "logos:ubisoft");
        float ratio = sprite.size.y / sprite.size.x;
        sprite.size = { 100 / ratio, 100 };

        auto& transform = reg.emplace<Transform>(entity);
        transform.position = { -200 , 100, zPos };

        auto& col = reg.emplace<SimpleCollision>(entity);
        col.size = sprite.size;

        Item& i = reg.emplace<Item>(entity);
        i.id = "Ubisoft";

    }


    {
        auto entity = reg.create();
        auto& sprite = reg.emplace<Sprite>(entity);
        AssignSprite(sprite, "platformerRocks:SimpleRockPlatform");
        float ratio = sprite.size.y / sprite.size.x;
        sprite.size = { 180, 30  };

        auto& transform = reg.emplace<Transform>(entity);
        transform.position = { -200 , 0, zPos };

        auto& col = reg.emplace<SimpleCollision>(entity);
        col.size = sprite.size;
        
        Platform& i = reg.emplace<Platform>(entity);
        i.id = "PLTLeft";
    }


    {
        auto entity = reg.create();
        auto& sprite = reg.emplace<Sprite>(entity);
        AssignSprite(sprite, "platformerRocks:SimpleRockPlatform");
        float ratio = sprite.size.y / sprite.size.x;
        sprite.size = { 120, 30  };

        auto& transform = reg.emplace<Transform>(entity);
        transform.position = { 330 , 0, zPos };

        auto& col = reg.emplace<SimpleCollision>(entity);
        col.size = sprite.size;
        
        Platform& i = reg.emplace<Platform>(entity);
        i.id = "PLTRight";
    }

    {
        auto entity = reg.create();
        auto& sprite = reg.emplace<Sprite>(entity);
        AssignSprite(sprite, "platformerRocks:SimpleRockPlatform");
        float ratio = sprite.size.y / sprite.size.x;
        sprite.size = { 500, 30  };

        auto& transform = reg.emplace<Transform>(entity);
        transform.position = { 0 , -80, zPos };

        auto& col = reg.emplace<SimpleCollision>(entity);
        col.size = sprite.size;
        
        Platform& i = reg.emplace<Platform>(entity);
        i.id = "PLTBottom";
    }

    {
        auto entity = reg.create();
        auto& sprite = reg.emplace<Sprite>(entity);
        AssignSprite(sprite, "platformerRocks:SimpleRockPlatform");
        float ratio = sprite.size.y / sprite.size.x;
        sprite.size = { 300, 30  };

        auto& transform = reg.emplace<Transform>(entity);
        transform.position = { 0 , 150, zPos };

        auto& col = reg.emplace<SimpleCollision>(entity);
        col.size = sprite.size;
        
        Platform& i = reg.emplace<Platform>(entity);
        i.id = "PLTTop";
    }
}
