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

using namespace dagger;
using namespace matattack;

void Matattack::GameplaySystemsSetup()
{
    auto& engine = Engine::Instance();
    engine.AddSystem<SimpleCollisionsSystem>();
    engine.AddSystem<ControllerSystem>();
    engine.AddSystem<MovementSystem>();
}

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

    static Character Get(Entity entity)
    {
        auto& reg = Engine::Registry();
        auto& sprite = reg.get_or_emplace<Sprite>(entity);
        auto& input = reg.get_or_emplace<InputReceiver>(entity);
        auto& char_info = reg.get_or_emplace<CharacterInfo>(entity);
        auto& transform = reg.get_or_emplace<Transform>(entity);
        auto& simple_collision = reg.get_or_emplace<SimpleCollision>(entity);
        auto& anim = reg.get_or_emplace<Animator>(entity);

        return Character{ entity, sprite, input, char_info, transform, simple_collision, anim };
    }

    static Character Create( String input_ = "", Vector2 position_ = { 0, 0 }, String sprite_path = "matattack:characters:chickboy:idle:idle1")
    {
        auto& reg = Engine::Registry();
        auto entity = reg.create();

        ATTACH_TO_FSM(FSMCharacterController, entity);

        auto chr = Character::Get(entity);

        // ako budemo hteli da budu razlicitih velicina likovi da budu, ovde menjamo!
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

        chr.char_info.speed = 100;

        return chr;
    }
};


void setSingleBlock(int x, int y, int z, String path_to_sprite, unsigned size_x, unsigned size_y, bool is_collidable) {

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

        auto& transform = reg.emplace<Transform>(block);
        transform.position = sprite.position;
    }
}

void setPlatform(int start_x, int start_y, int start_z, unsigned num_of_iterations) {
    for (unsigned i = 0u; i < num_of_iterations; ++i)
    {
        setSingleBlock(start_x, start_y, start_z, "matattack:tiles:tile_with_grass", 50, 50, true);
        start_x += 50;
    }
}

// postavlja pozadinu
void createBackdrop(String background_path)
{

    auto& engine = Engine::Instance();
    auto& reg = engine.Registry();

    float zPos = 1.f;

    // background 
    // mozda bismo hteli da ovo ide jos levo i desno par puta, neki for?
    {
        auto back = reg.create();
        auto& sprite = reg.get_or_emplace<Sprite>(back);

        AssignSprite(sprite, background_path);
        sprite.position.z = 10;
    }

}

void setMap() {

    createBackdrop("matattack:background:sky");

    // setting the trees (the trees need to be behind the player and the platforms, whats why they have a greater z value)
    setSingleBlock(-300, -125, 10, "matattack:tiles:tree", 100, 100, false);
    setSingleBlock(600, 75, 10, "matattack:tiles:tree", 100, 100, false);


    // da li zelimo da platforme budu isto z kao i player? => verovatno
    // middle platform
    setPlatform(-350, -200, 0, 16);
    // left and right platforms
    setPlatform(-600, 0, 0, 6);
    setPlatform(400, 0, 0, 6);

}



void Matattack::WorldSetup()
{
    ShaderSystem::Use("standard");
    matattack::SetupWorld();
}

void matattack::SetupWorld()
{
    setCamera();
    setMap();
    
    auto mainChar = Character::Create("ASDW", { -100, -150 }, "matattack:characters:chickboy:idle:idle1");
    auto sndChar = Character::Create("Arrows", { 100, -150 }, "matattack:characters:chickboy:idle:idle1");
}
