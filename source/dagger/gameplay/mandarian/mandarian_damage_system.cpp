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

    return Damaging{ entity, data};
}

Damaging Damaging::Create(Float32 damage_, Float32 radius_, Vector2 position_, Bool global_)
{
    auto &reg = Engine::Registry();
    auto entity = reg.create();
    reg.emplace<DamagingTag>(entity);
    auto damaging = Damaging::Get(entity);

    damaging.data.damage = damage_;
    damaging.data.radius = radius_;
    damaging.data.position = position_;
    damaging.data.global = global_;
    
    return damaging;
}

void MandarianDamageSystem::DealDamage(Enemy enemy, Damaging damaging) 
{
    std::cerr << abs(enemy.transform.position.x - damaging.data.position.x) << "Prva razlika" << std::endl;
    std::cerr << abs(enemy.transform.position.y - damaging.data.position.y) << "Druga razlika" << std::endl;
    if ((abs(enemy.transform.position.x - damaging.data.position.x) < damaging.data.radius 
    &&  abs(enemy.transform.position.y - damaging.data.position.y) < damaging.data.radius)
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
    auto &eng = Engine::Registry();

    auto player_ent = eng.view<Player>()[0];
    auto player = Character::Get(player_ent);

    auto damaging = Damaging::Create(0.2f, 100.0f, player.transform.position, false);
    
    auto damaging_ent = eng.view<DamagingTag>()[0];

    auto enemies = eng.view<EnemyTag>();
	for (auto &enemy_ent : enemies) 
    {
        auto enemy = Enemy::Get(enemy_ent);   
        DealDamage(enemy, damaging);
	} 

    eng.destroy(damaging_ent);
}

