#include "mandarian_enemy.h"

using namespace dagger;
using namespace mandarian;

Enemy Enemy::Get(Entity entity)
{
    auto &reg = Engine::Registry();
    auto &sprite = reg.get_or_emplace<Sprite>(entity);
    auto &transform = reg.get_or_emplace<Transform>(entity);
    auto &body = reg.get_or_emplace<Body>(entity);
    auto &health = reg.get_or_emplace<Health>(entity);

    return Enemy{ entity, sprite, transform, body, health };
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

    enemy.health.current = 100.0f;
    enemy.health.max = 100.0f;
    enemy.health.min = 0.0f;
    enemy.health.immortal = false;

    return enemy;
}

void EnemyMovementSystem::Run()
{
    auto &mandarianTransform = Engine::Registry().get<Transform>(mandarian);
    Engine::Registry().view<Transform, Body, EnemyTag>().each(
        [&](Transform &transform, Body &body, EnemyTag &tag)
        {
            Vector2 direction;
            
            direction.x = mandarianTransform.position.x - transform.position.x;
            direction.y = mandarianTransform.position.y - transform.position.y;

            direction = NORMALIZE(direction);

            body.applyForce(50.0f * direction);
        }
    );
}