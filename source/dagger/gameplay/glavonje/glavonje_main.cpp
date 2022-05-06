#include "glavonje_main.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"
#include "core/game/transforms.h"



//#include "gameplay/common/simple_collisions.h"

using namespace dagger;
using namespace glavonje;

void Glavonje::GameplaySystemsSetup(){

}


struct HeadBall{
        Vector3 position{0,0,0};
        Vector3 speed{0,0,0};
        bool touchWithGoal{false};
    };

void glavonje::CreateBall(ColorRGBA ballColor, Vector3 ballSpeed, Vector3 ballPosition){
    auto& reg = Engine::Registry();
    auto entity = reg.create();
    auto& sprite = reg.emplace<Sprite>(entity);

    AssignSprite(sprite, "PingPong:ball");
    sprite.size = Vector2(10, 10);

    sprite.color = ballColor;

    auto& transform = reg.emplace<Transform>(entity);
    transform.position = ballPosition;
    transform.position.z = ballPosition.z;
    auto& ball = reg.emplace<HeadBall>(entity);
    ball.speed = ballSpeed;
}

struct Gol
{
    Entity entity;
    Sprite& sprite;
    

    static Gol Get(Entity entity){
        auto& reg = Engine::Registry();
        auto& sprite = reg.get_or_emplace<Sprite>(entity);
        

        return Gol{entity, sprite};

    }

    static Gol Create( 
        ColorRGB color_ = { 0, 0, 0 }, 
        Vector2 position_ = { 0, 0 })

    {
        auto& reg = Engine::Registry();
        auto entity = reg.create();

        auto chr = Gol::Get(entity);
        
        chr.sprite.scale = { 1, 1 };
        chr.sprite.position = { position_, 0.0f };
        chr.sprite.color = { color_, 1.0f };
        chr.sprite.size = Vector2(100,100);
        AssignSprite(chr.sprite, "souls_like_knight_character:IDLE:idle1");

    
        return chr;
    }
};

struct Character
{
    Entity entity;
    Sprite& sprite;
    InputReceiver& inputR;
    

    static Character Get(Entity entity){
        auto& reg = Engine::Registry();
        auto& sprite = reg.get_or_emplace<Sprite>(entity);
        auto& inputR = reg.get_or_emplace<InputReceiver>(entity);

        return Character{entity, sprite, inputR};

    }

    static Character Create(
        String input_ = "", 
        ColorRGB color_ = { 1, 1, 1 }, 
        Vector2 position_ = { 0, 0 })
    
    {
        auto& reg = Engine::Registry();
        auto entity = reg.create();

        auto chr = Character::Get(entity);

        chr.sprite.scale = { 1, 1 };
        chr.sprite.position = { position_, 0.0f };
        chr.sprite.color = { color_, 1.0f };
        

        AssignSprite(chr.sprite, "souls_like_knight_character:IDLE:idle1");

        if(input_ != "")
            chr.inputR.contexts.push_back(input_);


        return chr;
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

//field    

    {
        auto& reg = Engine::Registry();
        auto back = reg.create();
        auto& sprite = reg.get_or_emplace<Sprite>(back);
        
        AssignSprite(sprite, "EmptyWhitePixel");
        sprite.color = { 0, 1, 0, 1 };
        sprite.size = { 100, 200 };
        sprite.scale = { 10, 1 };
        sprite.position = { 0, -125, 1 };
    }

    auto mainChar = Character::Create("ASDW", { 1, 1, 1 }, { -100, 0 });

    auto sndChar = Character::Create("Arrows", { 1, 0, 0 }, { 100, 0 });


    auto leftGol = Gol::Create( {0,0,0}, {-390, 0});
    auto rightGoal = Gol::Create( {0,0,0}, {390,0});

    CreateBall({1,1,1,1}, {5, 5, 0}, {0, 50, 0});
}


