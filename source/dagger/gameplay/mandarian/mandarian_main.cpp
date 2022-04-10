#include "mandarian_main.h"

#include "core/graphics/shaders.h"
#include "core/graphics/window.h"

using namespace mandarian;
using namespace dagger;

Character Character::Get(Entity enity) 
{
    auto &reg = Engine::Registry();
    auto &sprite = reg.get_or_emplace<Sprite>(enity);
    auto &transform = reg.get_or_emplace<Transform>(enity);

    return Character{ enity, sprite, transform };
}

Character Character::Create(
        ColorRGB color_, 
        Vector2 position_,
        Vector2 scale_)
{
    auto &reg = Engine::Registry();
    auto entity = reg.create();

    auto character = Character::Get(entity);

    AssignSprite(character.sprite, "EmptyWhitePixel");
    character.sprite.scale = { scale_ };
    character.sprite.color = { color_, 1.0f };

    character.transform.position = { position_, 0.0f };

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

}

void MandarianGame::WorldSetup()
{
    ShaderSystem::Use("standard");

    SetupCamera();

    auto mandarian = Character::Create();
}