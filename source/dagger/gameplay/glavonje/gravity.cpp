
#include "gravity.h"

#include "gameplay/common/simple_collisions.h"
#include "core/game/transforms.h"
#include "gameplay/glavonje/glavonje_main.h"

using namespace dagger;
using namespace glavonje;

const double GravitySystem::gravityForce = 0.28f;

void GravitySystem::SpinUp()
{
    Logger::critical("spin up");   
}

void GravitySystem::WindDown()
{
    Logger::critical("wind down");
}

void GravitySystem::Run(){
    auto& reg = Engine::Registry();

    auto ents = reg.view<Transform, Velocity>();

    for (const auto ent: ents) 
    {
        Transform& posit = ents.get<Transform>(ent);
        posit.position.y -= (GravitySystem::gravityForce) * 1.2f;
    }
}