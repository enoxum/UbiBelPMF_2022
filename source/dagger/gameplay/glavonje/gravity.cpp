#include "gravity.h"

#include "gameplay/common/simple_collisions.h"
#include "core/game/transforms.h"

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

    auto ents = reg.view<Transform, const Gravity>();

    for (const auto ent: ents) 
    {
        Transform& pos = ents.get<Transform>(ent);
        pos.position.y -= (GravitySystem::gravityForce) * 1.2f;
    }
}