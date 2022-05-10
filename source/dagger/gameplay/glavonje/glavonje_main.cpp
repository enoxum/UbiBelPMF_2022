#include "glavonje_main.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"
#include "core/game/transforms.h"


#include "gameplay/common/simple_collisions.h"
#include "gameplay/glavonje/gravity.h"


using namespace dagger;
using namespace glavonje;

void Glavonje::GameplaySystemsSetup(){
    auto& engine = Engine::Instance();
    engine.AddSystem<SimpleCollisionsSystem>();
    engine.AddSystem<GravitySystem>();
}

void glavonje::CreateBall(ColorRGBA ballColor_, Vector3 ballSpeed_, Vector3 ballPosition_){
    auto& reg = Engine::Registry();
    auto ballEntity = reg.create();
    auto& sprite = reg.emplace<Sprite>(ballEntity);

    AssignSprite(sprite, "PingPong:ball");
    sprite.size = Vector2(10, 10);
    sprite.color = ballColor_;

    auto& transform = reg.emplace<Transform>(ballEntity);
    transform.position = ballPosition_;
    auto& velocity = reg.emplace<Velocity>(ballEntity);
    velocity.speed = ballSpeed_;
}

struct Goal
{
    Entity entity;
    Sprite& sprite;

    static Goal Create( 
        ColorRGB color_ = { 0, 0, 0 }, 
        Vector2 position_ = { 0, 0 })
    {
        auto& reg = Engine::Registry();
        auto goalEntity = reg.create();

        auto& sprite = reg.get_or_emplace<Sprite>(goalEntity);
        auto goal = Goal{goalEntity, sprite};
        

        goal.sprite.scale = { 1, 1 };
        goal.sprite.position = { position_, 0.0f };
        goal.sprite.color = { color_, 1.0f };
        goal.sprite.size = Vector2(100,100);
        AssignSprite(goal.sprite, "souls_like_knight_character:IDLE:idle1");

    
        return goal;
    }
};

struct Character
{
    Entity entity;
    Sprite& sprite;
    InputReceiver& inputRcv;

    static Character Create(
        String input_ = "", 
        ColorRGB color_ = { 1, 1, 1 }, 
        Vector2 position_ = { 0, 0 })
    
    {
        auto& reg = Engine::Registry();
        auto characterEntity = reg.create();

        auto& sprite = reg.get_or_emplace<Sprite>(characterEntity);
        auto& inputRcv = reg.get_or_emplace<InputReceiver>(characterEntity);

        auto character = Character{characterEntity, sprite, inputRcv};;

        character.sprite.scale = { 1, 1 };
        character.sprite.position = { position_, 0.0f };
        character.sprite.color = { color_, 1.0f };

        AssignSprite(character.sprite, "souls_like_knight_character:IDLE:idle1");

        if (input_ != "") 
            character.inputRcv.contexts.push_back(input_);

        return character;
    }

};

void Glavonje::WorldSetup(){
    ShaderSystem::Use("standard");

    auto* camera = Engine::GetDefaultResource<Camera>();
    camera->mode = ECameraMode::FixedResolution;
    camera->size = { 800, 600 };
    camera->zoom = 1;
    camera->position = { 0, 0, 0 };
    camera->Update();

    // Setting up the goal field    
    {
        auto& reg = Engine::Registry();
        auto goalFieldEntity = reg.create();
        auto& sprite = reg.get_or_emplace<Sprite>(goalFieldEntity);
        
        AssignSprite(sprite, "EmptyWhitePixel");
        sprite.color = { 0, 1, 0, 1 };
        sprite.size = { 100, 200 };
        sprite.scale = { 10, 1 };
        sprite.position = { 0, -125, 1 };
    }

    auto leftCharacter = Character::Create("ASDW", { 1, 1, 1 }, { -100, 0 });
    auto rightCharacter = Character::Create("Arrows", { 1, 0, 0 }, { 100, 0 });


    auto leftGoal = Goal::Create( {0,0,0}, {-390, 0});
    auto rightGoal = Goal::Create( {0,0,0}, {390,0});

    CreateBall({1,1,1,1}, {5, 5, 0}, {0, 50, 0});
}


