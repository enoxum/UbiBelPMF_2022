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
    camera->size = { 800, 600 };
    camera->zoom = 1;
    camera->position = { 0, 0, 0 };
    camera->Update();
}


// postavlja pozadinu
void createBackdrop()
{

    auto& engine = Engine::Instance();
    auto& reg = engine.Registry();

    float zPos = 1.f;

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
        character.speed = 55;

        auto& input = reg.emplace<InputReceiver>(player);
        input.contexts.push_back("ASDW");

        ATTACH_TO_FSM(CharacterControllerFSM, player);

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
