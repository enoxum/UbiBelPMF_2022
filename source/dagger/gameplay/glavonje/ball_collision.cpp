
#include "gravity.h"

#include "gameplay/common/simple_collisions.h"
#include "core/game/transforms.h"
#include "gameplay/glavonje/glavonje_main.h"
#include "ball_collision.h"

using namespace dagger;
using namespace glavonje;


void BallCollisionSystem::SpinUp()
{
    Logger::critical("spin up");   
}

void BallCollisionSystem::WindDown()
{
    Logger::critical("wind down");
}

void BallCollisionSystem::Run(){
    auto& engine = Engine::Instance();
    auto& reg = engine.Registry();

    auto ball = reg.view<Transform,Velocity, SimpleCollision>();

    
    ball.each([this](Transform& transform, Velocity& velocity, SimpleCollision& scollision){
        

        if(scollision.colided){
            transform.position.y += 100000.0f * Engine::DeltaTime() / 2.0f;
            scollision.colided = false;
        }
    });
}