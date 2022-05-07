#include "mandarian_damage_system.h"

#include "core/engine.h"
#include "mandarian_controller.h"
#include <iostream>

using namespace dagger;
using namespace mandarian;

Damaging Damaging::Get(Entity entity)
{
    auto &reg = Engine::Registry();
    auto &data = reg.get_or_emplace<DamageData>(entity);
    auto &transform = reg.get_or_emplace<Transform>(entity);

    return Damaging{ entity, data, transform };
}

Damaging Damaging::Create(Float32 damage_, Float32 radius_, Vector3 position_, Bool global_)
{
    auto &reg = Engine::Registry();
    auto entity = reg.create();
    reg.emplace<DamagingTag>(entity);
    auto damaging = Damaging::Get(entity);

    damaging.data.damage = damage_;
    damaging.data.radius = radius_;
    damaging.data.global = global_;
    damaging.transform.position = position_;
    
    return damaging;
}

void MandarianDamageSystem::DealDamage(Enemy enemy, Damaging damaging) 
{
    if ((abs(enemy.transform.position.x - damaging.transform.position.x) < damaging.data.radius 
    &&  abs(enemy.transform.position.y - damaging.transform.position.y) < damaging.data.radius)
    || damaging.data.global)
    {
        enemy.health.current -= damaging.data.damage;

        if(enemy.health.current <= 0.0f)
        {
            Kill(enemy);
        }
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

void MandarianDamageSystem::Run()
{
    auto &reg = Engine::Registry();

    auto damaging_ent = reg.view<DamagingTag>()[0];
    auto damaging = Damaging::Get(damaging_ent);

    auto enemies = reg.view<EnemyTag>();
	for (auto &enemy_ent : enemies) 
    {
        auto enemy = Enemy::Get(enemy_ent);   
        DealDamage(enemy, damaging);
	} 

    reg.destroy(damaging_ent);
}

