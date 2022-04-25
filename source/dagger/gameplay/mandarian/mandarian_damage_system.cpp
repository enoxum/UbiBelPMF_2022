#include "mandarian_damage_system.h"

#include "core/engine.h"
#include "mandarian_controller.h"
#include <iostream>

using namespace dagger;
using namespace mandarian;

void MandarianDamageSystem::DealDamage(Enemy enemy, Float32 damage) 
{
    enemy.health.current -= damage;

    if(enemy.health.current <= 0.0f)
    {
        Kill(enemy);
    }
}

void MandarianDamageSystem::Kill(Enemy enemy)
{
    if(!enemy.health.immortal) 
    {
        enemy.health.current = enemy.health.min;
        Engine::Registry().destroy(enemy.entity);
    }
}

// void MandarianDamageSystem::Kill(Entity entity)
// {
//     auto &reg = Engine::Registry();
//     auto &health = reg.get<Health>(entity);
//     if(!health.immortal) 
//     {
//         enemy.health.current = enemy.health.min;
//         Engine::Registry().destroy(enemy.entity);
//     }
// }


void MandarianDamageSystem::Run()
{
    auto p_entity = Engine::Registry().view<Player>()[0];
    auto enemies = Engine::Registry().view<EnemyTag>();
	for (auto &e_entity : enemies) 
    {
        auto enemy = Enemy::Get(e_entity);
        auto player = Character::Get(p_entity);
        
        if (abs(enemy.transform.position.x - player.transform.position.x) < 100.0f 
        &&  abs(enemy.transform.position.y - player.transform.position.y) < 100.0f)
            DealDamage(enemy, 0.2f);
	}    
}

