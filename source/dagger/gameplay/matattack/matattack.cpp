#include "matattack.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"
#include "core/game/transforms.h"

#include "gameplay/common/simple_collisions.h"

#include "movementsystem.h"
#include "controllersystem.h"
#include "gravitysystem.h"
#include "jumpingsystem.h"

using namespace dagger;
using namespace matattack;

void Matattack::GameplaySystemsSetup()
{
    auto& engine = Engine::Instance();
    engine.AddSystem<SimpleCollisionsSystem>();
    engine.AddSystem<ControllerSystem>();
    engine.AddSystem<MovementSystem>();
    engine.AddSystem<GravitySystem>();
    engine.AddSystem<JumpingSystem>();

}

// konzistentno pisanje imena fja
// neka mala promena
void setCamera()
{
    auto* camera = Engine::GetDefaultResource<Camera>();
    camera->mode = ECameraMode::FixedResolution;
    camera->size = { 1920, 1080 };
    camera->zoom = 1.25;
    camera->position = { 0, 0, 0 };
    camera->Update();
}

struct Character
{
    Entity entity;
    Sprite& sprite;
    InputReceiver& input;
    CharacterInfo& char_info;
    Transform& transform;
    SimpleCollision& simple_collision;
    Animator& animator;
    Gravity& gravity;

    static Character Get(Entity entity)
    {
        auto& reg = Engine::Registry();
        auto& sprite = reg.get_or_emplace<Sprite>(entity);
        auto& input = reg.get_or_emplace<InputReceiver>(entity);
        auto& char_info = reg.get_or_emplace<CharacterInfo>(entity);
        auto& transform = reg.get_or_emplace<Transform>(entity);
        auto& simple_collision = reg.get_or_emplace<SimpleCollision>(entity);
        auto& anim = reg.get_or_emplace<Animator>(entity);
        auto& gravity = reg.get_or_emplace<Gravity>(entity);

        return Character{ entity, sprite, input, char_info, transform, simple_collision, anim, gravity };
    }

    static Character Create( String input_ = "", Vector2 position_ = { 0, 0 }, String sprite_path = "matattack:characters:chickboy:idle:idle1")
    {
        auto& reg = Engine::Registry();
        auto entity = reg.create();

        ATTACH_TO_FSM(FSMCharacterController, entity);

        auto chr = Character::Get(entity);

        chr.sprite.scale = { 1.5, 1.5 };
        chr.sprite.position = { position_, 0.0f };
        chr.sprite.size = { 50, 50 };

        AssignSprite(chr.sprite, sprite_path);
        AnimatorPlay(chr.animator, "matattack:idle");

        if (input_ != "")
            chr.input.contexts.push_back(input_);

        chr.transform.position = { position_, 0.0f };

        chr.simple_collision.size = { 50, 50 };
        chr.simple_collision.pos = chr.transform.position;
        chr.simple_collision.is_collidable = false;
        chr.simple_collision.is_moveable = true;

        chr.char_info.speed = 100;

        // up to debate (the value) 
        chr.gravity.weight = 200.7F;

        return chr;
    }
};


void setSingleBlock(int x, int y, int z, String path_to_sprite, unsigned size_x, unsigned size_y, bool is_collidable, bool is_moveable) {

    auto& engine = Engine::Instance();
    auto& reg = engine.Registry();

    {
        auto block = reg.create();
        auto& sprite = reg.get_or_emplace<Sprite>(block);

        AssignSprite(sprite, path_to_sprite);
        sprite.size = { size_x, size_y };
        sprite.position = { x, y, z };

        auto& simple_collision = reg.emplace<SimpleCollision>(block);
        simple_collision.size = sprite.size;
        simple_collision.pos = sprite.position;
        simple_collision.is_collidable = is_collidable;
        simple_collision.is_moveable = is_moveable;

        auto& transform = reg.emplace<Transform>(block);
        transform.position = sprite.position;
    }
}

void setPlatform(int start_x, int start_y, int start_z, unsigned num_of_iterations, String path) {
    for (unsigned i = 0u; i < num_of_iterations; ++i)
    {
        setSingleBlock(start_x, start_y, start_z, path, 50, 50, true, false);
        start_x += 50;
    }
}

void createBackdrop(String background_path)
{

    auto& engine = Engine::Instance();
    auto& reg = engine.Registry();

    float zPos = 1.f;

    {
        auto back = reg.create();
        auto& sprite = reg.get_or_emplace<Sprite>(back);

        AssignSprite(sprite, background_path);
        sprite.position.z = 10;
    }

}

void setMap1() {

    createBackdrop("matattack:background:sky");

    // setting the trees (the trees need to be behind the player and the platforms, whats why they have a greater z value)
    setSingleBlock(-300, -225, 10, "matattack:tiles:tree", 100, 100, false, false);
    setSingleBlock(600, -50, 10, "matattack:tiles:tree", 100, 100, false, false);
    setSingleBlock(200, 120, 10, "matattack:tiles:bush", 50, 40, false, false);
    setSingleBlock(-200, 120, 10, "matattack:tiles:big_crate", 40, 40, false, false);
    setSingleBlock(300, -255, 10, "matattack:tiles:big_crate", 40, 40, false, false);
    setSingleBlock(400, 250, 10, "matattack:tiles:cloud2", 200, 100, false, false);
    setSingleBlock(-470, 250, 10, "matattack:tiles:cloud1", 130, 100, false, false);
    setSingleBlock(0, 300, 10, "matattack:tiles:cloud3", 120, 100, false, false);
    // da li zelimo da platforme budu isto z kao i player? => verovatno
    // middle platform
    setPlatform(-350, -300, 0, 16, "matattack:tiles:tile_with_grass");
    // left and right platforms
    setPlatform(-600, -125, 0, 6, "matattack:tiles:tile_with_grass");
    setPlatform(400, -125, 0, 6, "matattack:tiles:tile_with_grass");

    setPlatform(-350, 75, 0, 16, "matattack:tiles:tile_with_grass");

}

void setMap2() {

    createBackdrop("matattack:background:desert");

    setSingleBlock(-300, -250, 10, "matattack:tiles:skeleton", 100, 50, false, false);
    setSingleBlock(300, -225, 10, "matattack:tiles:cactus", 80, 100, false, false);
    setSingleBlock(600, -80, 10, "matattack:tiles:skeleton", 100, 50, false, false);
    setSingleBlock(200, 120, 10, "matattack:tiles:bush_desert", 75, 50, false, false);
    setSingleBlock(-200, 120, 10, "matattack:tiles:bush_desert", 75, 50, false, false);
    setPlatform(-350, -300, 0, 16, "matattack:tiles:tile_rock");
    setPlatform(-600, -125, 0, 6, "matattack:tiles:tile_rock");
    setPlatform(400, -125, 0, 6, "matattack:tiles:tile_rock");
    setPlatform(-350, 75, 0, 16, "matattack:tiles:tile_rock");

}

void setMap3() {

    createBackdrop("matattack:background:forest");

    setSingleBlock(-250, -200, 10, "matattack:tiles:tree_forest", 125, 150, false, false);
    setSingleBlock(300, 175, 10, "matattack:tiles:tree_forest", 125, 150, false, false);
    setSingleBlock(300, -260, 10, "matattack:tiles:rock", 50, 30, false, false);
    setSingleBlock(600, -85, 10, "matattack:tiles:rock", 50, 30, false, false);
    setPlatform(-350, -300, 0, 16, "matattack:tiles:tile_stone");
    setPlatform(-600, -125, 0, 6, "matattack:tiles:tile_stone");
    setPlatform(400, -125, 0, 6, "matattack:tiles:tile_stone");
    setPlatform(-350, 75, 0, 16, "matattack:tiles:tile_stone");

}

void setLevel() {
    int lvl = std::rand() % 3 + 1;
    switch (lvl)
    {case 1:
        setMap1(); break;
    case 2: 
        setMap2(); break;
    case 3:
        setMap3(); break;
    default:
        break;
    }

}

void Matattack::WorldSetup()
{
    ShaderSystem::Use("standard");
    matattack::SetupWorld();
}

void matattack::SetupWorld()
{
    setCamera();
    setLevel();
    //setMap1(); 
    
    auto mainChar = Character::Create("ASDW", { -100, 250 }, "matattack:characters:chickboy:idle:idle1");
    auto sndChar = Character::Create("Arrows", { 100, 250 }, "matattack:characters:chickboy:idle:idle1");
}
