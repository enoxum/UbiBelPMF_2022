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
    

    for(const auto plt: viewCollisions) 
    {
        auto &col = viewCollisions.get<SimpleCollision>(plt);
        Transform& solidObjectPosition = viewCollisions.get<Transform>(plt);
        
        if (col.colided && Engine::Registry().valid(col.colidedWith) && view.contains(col.colidedWith))
        {
            SimpleCollision& collision = view.get<SimpleCollision>(col.colidedWith);
            Transform& playerPosition = view.get<Transform>(col.colidedWith);
            Player& p = view.get<Player>(col.colidedWith);
          
            Vector2 collisionSides = col.GetCollisionSides(playerPosition.position, collision, solidObjectPosition.position);

            Sprite& platformSpriteSize = viewCollisions.get<Sprite>(plt);
            Sprite& playerSpriteSize = view.get<Sprite>(col.colidedWith);

            auto platformHeight = platformSpriteSize.size.y / 2;
            auto playerHeight = playerSpriteSize.size.y / 2;
            auto platformWidth = platformSpriteSize.size.x / 2;
            auto playerWidth = playerSpriteSize.size.x / 2;

            if (collisionSides.y > 0 && playerPosition.position.y + playerHeight > (solidObjectPosition.position.y - platformHeight))
            {
                col.colided = false;
                playerPosition.position.y = solidObjectPosition.position.y - platformHeight - playerHeight;
            }

            if (collisionSides.y < 0)
            {
                playerPosition.position.y = solidObjectPosition.position.y + platformHeight + playerHeight;
                p.jumping = false;
            }
            else {
                p.jumping = true;
            }

            if (collisionSides.x < 0)
            {
                playerPosition.position.x = solidObjectPosition.position.x + platformWidth + playerWidth;
            }
            
            if (collisionSides.x > 0)
            {
                playerPosition.position.x = solidObjectPosition.position.x - (platformWidth + playerWidth);
            }

            col.colided = false;
        }
    }
}
