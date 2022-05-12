#include "gravity.h"
#include "player_controller.h"

#include "gameplay/common/simple_collisions.h"
#include "core/game/transforms.h"

#include<iostream>

using namespace dagger;
using namespace team_game;

const double GravitySystem::gravityForce = 1.0f;

void GravitySystem::SpinUp()
{
    Logger::critical("spin up");   
}

void GravitySystem::WindDown()
{
    Logger::critical("wind down");
}

void GravitySystem::Run() 
{
    auto& reg = Engine::Registry();
    auto ents = reg.view<Transform, const Gravity>();

    for (const auto ent: ents) 
    {
        Transform& pos = ents.get<Transform>(ent);
        pos.position.y -= GravitySystem::gravityForce * Engine::DeltaTime() * 300;
    }
    
}
