#include "mandarian_enemy.h"

using namespace dagger;
using namespace mandarian;

Enemy Enemy::Get(Entity entity)
{
    auto &reg = Engine::Registry();
    auto &sprite = reg.get_or_emplace<Sprite>(entity);
    auto &transform = reg.get_or_emplace<Transform>(entity);
    auto &body = reg.get_or_emplace<Body>(entity);

    return Enemy{ entity, sprite, transform, body };
}

Enemy Enemy::Create(
            Vector2 position_,
            ColorRGB color_,
            Vector2 scale_)
{
    auto &reg = Engine::Registry();
    auto entity = reg.create();
    reg.emplace<EnemyTag>(entity);
    auto enemy = Enemy::Get(entity);

    AssignSprite(enemy.sprite, "EmptyWhitePixel");
    enemy.sprite.scale = { scale_ };
    enemy.sprite.color = { color_, 1.0f };

    enemy.transform.position = { position_, 0.0f };

    return enemy;
}
