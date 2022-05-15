#include "mandarian_enemy.h"
#include "mandarian_level.h"

using namespace dagger;
using namespace mandarian;

Enemy Enemy::Get(Entity entity)
{
    auto &reg = Engine::Registry();
    auto &sprite = reg.get_or_emplace<Sprite>(entity);
    auto &transform = reg.get_or_emplace<Transform>(entity);
    auto &body = reg.get_or_emplace<Body>(entity);
    auto &collision = reg.get_or_emplace<CircleCollision>(entity);
    auto &health = reg.get_or_emplace<Health>(entity);

    return Enemy{ entity, sprite, transform, body, collision, health };
}

Enemy Enemy::Create(
            UInt8 tier_,
            Vector2 position_,
            Vector2 scale_,
            ColorRGB color_,
            Float32 radius_)
{
    auto &reg = Engine::Registry();
    auto entity = reg.create();
    reg.emplace<EnemyTag>(entity);
    auto enemy = Enemy::Get(entity);

    switch (tier_)
    {
    case 1u:
        AssignSprite(enemy.sprite, "mandarian:tier1enemy");
        enemy.body.mass = 1.0f;
        break;
    case 2u:
        AssignSprite(enemy.sprite, "mandarian:tier2enemy");
        enemy.body.mass = 3.0f;
        break;
    case 3u:
        AssignSprite(enemy.sprite, "mandarian:tier3enemy");
        break;
    default:
        AssignSprite(enemy.sprite, "EmptyWhitePixel");
        break;
    }

    enemy.sprite.scale = { scale_ };
    enemy.sprite.color = { color_, 1.0f };
    
    enemy.transform.position = { position_, 0.0f };

    enemy.collision.radius = radius_;

    enemy.health.current = 100;
    enemy.health.max = 100;

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

            body.setVelocity(30.0f * direction);
        }
    );
}

void EnemyDeathSystem::Run()
{
    Engine::Registry().view<EnemyTag, Health, Transform>().each(
        [&](auto entity, auto &enemyTag, auto &health, auto &transform)
        {
            if (health.current <= 0.0f)
            {
                Mandarin::Create(10u, transform.position);
                Engine::Registry().destroy(entity);
            }
        }
    );
}
