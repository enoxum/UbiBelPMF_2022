#include "mandarian_main.h"

#include "core/graphics/shaders.h"
#include "core/graphics/window.h"

#include "mandarian_controller.h"
#include "mandarian_camera_focus_system.h"

using namespace mandarian;
using namespace dagger;

Character Character::Get(Entity entity) 
{
    auto &reg = Engine::Registry();
    auto &sprite = reg.get_or_emplace<Sprite>(entity);
    auto &transform = reg.get_or_emplace<Transform>(entity);
    auto &body = reg.get_or_emplace<Body>(entity);
    auto &input = reg.get_or_emplace<InputReceiver>(entity);

    return Character{ entity, sprite, transform, body, input };
}

Character Character::Create(
        ColorRGB color_, 
        Vector2 position_,
        Vector2 scale_,
        String input_)
{
    auto &reg = Engine::Registry();
    auto entity = reg.create();
    reg.emplace<Player>(entity);
    auto character = Character::Get(entity);

    ATTACH_TO_FSM(MandarianControllerFSM, entity); 

    AssignSprite(character.sprite, "EmptyWhitePixel");
    character.sprite.scale = { scale_ };
    character.sprite.color = { color_, 1.0f };

    character.transform.position = { position_, 0.0f };

    if (input_ != "") 
        character.input.contexts.push_back(input_);

    return character;
}

void MandarianGame::SetupCamera()
{
    auto *camera = Engine::GetDefaultResource<Camera>();
    camera->mode = ECameraMode::FixedResolution;
    camera->size = { 800, 600 };
    camera->zoom = 1;
    camera->position = { 0, 0, 0 };
    camera->Update();
}

void MandarianGame::GameplaySystemsSetup() 
{
    auto &engine = Engine::Instance();

    engine.AddPausableSystem<MandarianControllerSystem>();
    engine.AddPausableSystem<SimplePhysicsSystem>();
    engine.AddPausableSystem<MandarianCameraFocusSystem>();
}

void MandarianGame::WorldSetup()
{
    ShaderSystem::Use("standard");

    SetupCamera();

    Character::Create();
}