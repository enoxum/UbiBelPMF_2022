#include "mandarian_enemy.h"
#include "mandarian_level.h"
#include "mandarian_controller.h"
#include "mandarian_spell_system.h"

#include "core/graphics/text.h"
#include "core/graphics/animations.h"

using namespace dagger;
using namespace mandarian;

Enemy Enemy::Get(Entity entity)
{
    auto &reg = Engine::Registry();
    auto &sprite = reg.get_or_emplace<Sprite>(entity);
    auto &animator = reg.get_or_emplace<Animator>(entity);
    auto &transform = reg.get_or_emplace<Transform>(entity);
    auto &body = reg.get_or_emplace<Body>(entity);
    auto &collision = reg.get_or_emplace<CircleCollision>(entity);
    auto &health = reg.get_or_emplace<Health>(entity);
    auto &demage = reg.get_or_emplace<Demage>(entity);

    return Enemy{ entity, sprite, animator, transform, body, collision, health, demage };
}

Enemy Enemy::Create(
            UInt8 tier_,
            Vector2 position_,
            Vector2 scale_,
            ColorRGB color_,
            Float32 radius_,
            Float32 demage_)
{
    auto &reg = Engine::Registry();
    auto entity = reg.create();
    reg.emplace<EnemyTag>(entity);
    auto enemy = Enemy::Get(entity);

    switch (tier_)
    {
    case 1u:
        AssignSprite(enemy.sprite, "mandarian:taotie1");
        AnimatorPlay(enemy.animator, "taotie:RUN");
        enemy.health.current = 100;
        enemy.health.max = 100;
        break;
    case 2u:
        AssignSprite(enemy.sprite, "mandarian:tier2enemy");
        enemy.health.current = 125;
        enemy.health.max = 125;
        break;
    case 3u:
        AssignSprite(enemy.sprite, "mandarian:tier3enemy");
        enemy.health.current = 250;
        enemy.health.max = 250;
        break;
    default:
        AssignSprite(enemy.sprite, "EmptyWhitePixel");
        break;
    }

    Logger::trace("Scale: {}, {}", scale_.x, scale_.y);
    enemy.sprite.scale = { scale_ };
    enemy.sprite.color = { color_, 1.0f };
    
    enemy.transform.position = { position_, 0.0f };

    enemy.collision.radius = radius_;

    enemy.demage.points = demage_;

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

void EnemyDemageSystem::Run()
{
    auto &mandarianTransform = Engine::Registry().get<Transform>(mandarian);
    auto &mandarianHealth = Engine::Registry().get<CharacterHealth>(mandarian);
    auto &mandarianStats = Engine::Registry().get<CharacterStats>(mandarian);

    Engine::Registry().view<Transform, Demage>().each(
        [&](const auto enemy, auto &transform, auto &demage)
        {
            if (glm::distance(mandarianTransform.position, transform.position) < mandarianStats.danger) 
            {
                auto demageSum = demage.points - mandarianStats.armor;
                if (demageSum < 0.0f) {
                    demageSum = 0.0f;
                }

                mandarianHealth.points -= demageSum * Engine::DeltaTime();

                if (mandarianHealth.points < 0.0f) {
                    // TODO: Restart game!
                    Engine::GetDefaultResource<SimpleCollisionsSystem>()->Pause();
                    Engine::GetDefaultResource<EnemyMovementSystem>()->Pause();
                    Engine::GetDefaultResource<SimplePhysicsSystem>()->Pause();
                    Engine::GetDefaultResource<MandarianSpellSystem>()->Pause();
                    Engine::GetDefaultResource<LevelSystem>()->Pause();
                    Engine::GetDefaultResource<EnemyDeathSystem>()->Pause();
                    Engine::GetDefaultResource<EnemyDemageSystem>()->Pause();
                    Engine::GetDefaultResource<AnimationSystem>()->Pause();

                    auto entity = Engine::Registry().create();
                    auto &gameover = Engine::Registry().emplace<Text>(entity);
                    gameover.spacing = 0.6f;
                    gameover.Set("pixel-font", "Game Over");
                }         
            }
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
