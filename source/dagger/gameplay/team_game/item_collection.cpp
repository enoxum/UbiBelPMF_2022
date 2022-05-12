#include "item_collection.h"
#include "player_controller.h"

#include "gameplay/common/simple_collisions.h"
#include "core/game/transforms.h"

#include<iostream>

using namespace dagger;
using namespace team_game;

void ItemCollectionSystem::SpinUp()
{
    Logger::critical("spin up");   
}

void ItemCollectionSystem::WindDown()
{
    Logger::critical("wind down");
}

void ItemCollectionSystem::Run() 
{

    auto& engine = Engine::Instance();
    auto& reg = engine.Registry();

    auto viewCollisions = Engine::Registry().view<Item, Transform, SimpleCollision>();
    auto view = Engine::Registry().view<Player, Transform, SimpleCollision>();

    for(const auto player: view) 
    {
        auto &col = view.get<SimpleCollision>(player);
        
        if (col.colided && Engine::Registry().valid(col.colidedWith) && viewCollisions.contains(col.colidedWith))
        {
            // move item to "invisible place"
            Transform& transform = viewCollisions.get<Transform>(col.colidedWith);
            transform.position = { INFINITY, INFINITY, INFINITY };

            Item& collected = viewCollisions.get<Item>(col.colidedWith);

            // set that item is collected
            CollectedItem& i = reg.emplace<CollectedItem>(col.colidedWith);
            i.id = collected.id;

            // prevent entering this if statment again
            col.colided = false;
        }
    }
}
