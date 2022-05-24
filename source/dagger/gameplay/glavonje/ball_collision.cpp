
#include "gravity.h"

#include "gameplay/common/simple_collisions.h"
#include "core/game/transforms.h"
#include "gameplay/glavonje/glavonje_main.h"
#include "ball_collision.h"

using namespace dagger;
using namespace glavonje;

Float32 minusPom = 0.13f;

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

    //  arr = [player1, player2, ball, goal1, goal2, field]
    //  for transform, velocity, collision in arr:
    //      if entityHasComponent<FloorTag>(collision.collidedWith):
    //          resolveCollisinWithFloor(transform, velocity, collision)
    //      if entityHasComponent<GoalTag>(collision.collidedWith):
    //          resolveCollisinWithGoal(transform, velocity, collision)
    //      
    //
    ball.each([this](Transform& transform, Velocity& velocity, SimpleCollision& scollision){
        

        if(scollision.colided && Engine::Registry().valid(scollision.colidedWith)){
            //transform.position.y += 50000.0f * Engine::DeltaTime()/10;
            //transform.position.y += 60.0f;
            Float32 var = 60.0f;
            while(var > 0.0f || minusPom <= 0.1f){
                transform.position.y += minusPom;
                var -= 0.1f;
            }
            if(minusPom <= 0.1f)
                minusPom = 0.13f;
            else
                minusPom -= 0.08f;
            scollision.colided = false;
        }
    });
}