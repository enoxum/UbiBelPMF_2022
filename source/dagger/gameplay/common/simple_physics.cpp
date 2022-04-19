#include "simple_physics.h"

#include "core/engine.h"
#include "core/game/transforms.h"

using namespace dagger;


void Body::applyForce(Vector2 force_)
{
    force.x += force_.x;
    force.y += force_.y;
}

void SimplePhysicsSystem::Run() 
{
    Engine::Registry().view<Body, Transform>().each(
        [&](auto &body, auto &transform) 
        {
            body.force *= drag;
            if (EPSILON_ZERO(body.force.x)) body.force.x = 0.0f;
            if (EPSILON_ZERO(body.force.y)) body.force.y = 0.0f;
            
//            Logger::trace("Force: ({}, {})", body.force.x, body.force.y);

            Vector2 acceleration = { 0.0f, 0.0f };

            acceleration.x = body.force.x / body.mass;
            acceleration.y = body.force.y / body.mass;

            body.velocity.x += acceleration.x * Engine::DeltaTime();
            body.velocity.y += acceleration.y * Engine::DeltaTime();

            body.velocity *= friction;

            if (EPSILON_ZERO(body.velocity.x)) body.velocity.x = 0.0f;
            if (EPSILON_ZERO(body.velocity.y)) body.velocity.y = 0.0f;

            //Logger::trace("Velocity: ({}, {})", body.velocity.x, body.velocity.y);

            transform.position.x += body.velocity.x * Engine::DeltaTime();
            transform.position.y += body.velocity.y * Engine::DeltaTime();
        }
    );
} 
