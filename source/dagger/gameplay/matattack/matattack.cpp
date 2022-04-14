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

// ???????? => kako se snadjem sa ovim include silnim
#include "controllersystem.h"

using namespace dagger;
using namespace matattack;

void Matattack::GameplaySystemsSetup()
{
    auto& engine = Engine::Instance();
    engine.AddSystem<SimpleCollisionsSystem>();
    engine.AddSystem<ControllerSystem>();
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


void setSingleBlock(int x, int y, int z, String path_to_sprite, unsigned size_x, unsigned size_y) {

    auto& engine = Engine::Instance();
    auto& reg = engine.Registry();

    {
        auto back = reg.create();
        auto& sprite = reg.get_or_emplace<Sprite>(back);

        AssignSprite(sprite, path_to_sprite);
        sprite.size = { size_x, size_y };
        sprite.position = { x, y, z };    
    }
}

void setPlatform(int start_x, int start_y, int start_z, unsigned num_of_iterations) {
    for (unsigned i = 0u; i < num_of_iterations; ++i)
    {
        setSingleBlock(start_x, start_y, start_z, "matattack:tiles:tile_with_grass", 100, 100);
        start_x += 100;
    }
}

void setMap() {
    
    // setting the trees (the trees need to be behind the player and the platforms, whats why they have a greater z value)
    setSingleBlock(-300, -100, 10, "matattack:tiles:tree", 100, 100);
    setSingleBlock(600, 100, 10, "matattack:tiles:tree", 100, 100);


    // da li zelimo da platforme budu isto z kao i player? => verovatno
    // middle platform
    setPlatform(-300, -200, 0, 7);
    // left and right platforms
    setPlatform(-600, 0, 0, 3);
    setPlatform(400, 0, 0, 3);

}


// postavlja pozadinu
void createBackdrop()
{

    auto& engine = Engine::Instance();
    auto& reg = engine.Registry();

    float zPos = 1.f;

    // background 
    // mozda bismo hteli da ovo ide jos levo i desno par puta, neki for?
    {
        auto back = reg.create();
        auto& sprite = reg.get_or_emplace<Sprite>(back);

        AssignSprite(sprite, "matattack:background:sky");
        sprite.position.z = 10;
    }

    setMap();

    /*{
        auto entity = reg.create();
        auto& sprite = reg.emplace<Sprite>(entity);
        AssignSprite(sprite, "logos:dagger");
        float ratio = sprite.size.y / sprite.size.x;
        sprite.size = { 500 / ratio, 500 };

        auto& transform = reg.emplace<Transform>(entity);
        transform.position = { 0, 0, zPos };

        auto& col = reg.emplace<SimpleCollision>(entity);
        col.size = sprite.size;
    }*/
}

void createPlayers()
{

    auto& engine = Engine::Instance();
    auto& reg = engine.Registry();

    {
        auto player = reg.create();

        // dodajemo komponentu sprite, entitetu player
        auto& sprite = reg.get_or_emplace<Sprite>(player);
        // dodajemo komponenti sprite, sliku ...
        AssignSprite(sprite, "EmptyWhitePixel");
        sprite.size = { 30, 30 };

        // dodajemo komponentu Transform, entitenu player
        auto& transform = reg.emplace<Transform>(player);
        transform.position = { 0, 0, 0 };

        auto& character = reg.emplace<Character>(player);
        // up to debate
        character.speed = 100;

        auto& input = reg.emplace<InputReceiver>(player);
        input.contexts.push_back("ASDW");

        ATTACH_TO_FSM(FSMCharacterController, player);

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
    createBackdrop();
    createPlayers();
}
