#include "solid_object_interaction.h"
#include "gravity.h"
#include "player_controller.h"

#include "gameplay/common/simple_collisions.h"
#include "core/game/transforms.h"
#include "core/graphics/sprite.h"

#include<iostream>

using namespace dagger;
using namespace team_game;

void SolidObjectInteractionSystem::SpinUp()
{
    Logger::critical("spin up");   
}

void SolidObjectInteractionSystem::WindDown()
{
    Logger::critical("wind down");
}

void SolidObjectInteractionSystem::Run() 
{

    auto& engine = Engine::Instance();
    auto& reg = engine.Registry();

    auto viewCollisions = Engine::Registry().view<Platform, Transform, SimpleCollision, Sprite>();
    auto view = Engine::Registry().view<Player, Transform, SimpleCollision, Sprite>();

    for(const auto player: view) 
    {
        auto &col = view.get<SimpleCollision>(player);
        auto &p = view.get<Player>(player);
        
        if (col.colided && Engine::Registry().valid(col.colidedWith) && viewCollisions.contains(col.colidedWith))
        {
            Platform& plt = viewCollisions.get<Platform>(col.colidedWith);

            SimpleCollision& collision = viewCollisions.get<SimpleCollision>(col.colidedWith);
            Transform& solidObjectPosition = viewCollisions.get<Transform>(col.colidedWith);
            Transform& playerPosition = view.get<Transform>(player);
          
            Vector2 collisionSides = col.GetCollisionSides(playerPosition.position, collision, solidObjectPosition.position);

            Sprite& platformSpriteSize = viewCollisions.get<Sprite>(col.colidedWith);
            Sprite& playerSpriteSize = view.get<Sprite>(player);

            auto platformHeight = platformSpriteSize.size[1] / 2;
            auto playerHeight = playerSpriteSize.size[1] / 2;
            auto platformOffset = platformSpriteSize.size[0] / 2;
            auto playerOffset = playerSpriteSize.size[0] / 2;


            if (collisionSides.x < 0)
            {
                playerPosition.position[0] = solidObjectPosition.position[0] + platformOffset + playerOffset;
            }
            
            if (collisionSides.x > 0)
            {
                playerPosition.position[0] = solidObjectPosition.position[0] - (platformOffset + playerOffset);
            }

            if (collisionSides.y > 0)
            {
                col.colided = false;
                playerPosition.position[1] = solidObjectPosition.position[1] - platformHeight - playerHeight;
            }

            if (collisionSides.y < 0)
            {
                playerPosition.position[1] = solidObjectPosition.position[1] + platformHeight + playerHeight  
                                            + GravitySystem::gravityForce;
            }

            col.colided = false;
        }
    }
}
