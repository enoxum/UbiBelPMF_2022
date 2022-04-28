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
    auto viewCollisions = Engine::Registry().view<Item, Transform, SimpleCollision>();
    auto view = Engine::Registry().view<Player, Transform, SimpleCollision>();

    for(const auto player: view) 
    {
        auto &col = view.get<SimpleCollision>(player);
        Player& p = view.get<Player>(player);  

        if (col.colided && Engine::Registry().valid(col.colidedWith))
        {
            SimpleCollision& collision = viewCollisions.get<SimpleCollision>(col.colidedWith);
            Transform& transform = viewCollisions.get<Transform>(col.colidedWith);

            // move item to "invisible place"
            transform.position = { INFINITY, INFINITY, INFINITY};

            Item& item = Engine::Registry().get<Item>(col.colidedWith);

            if (std::count(p.items.begin(), p.items.end(), item) < 1)
            {
                p.items.push_back(item);
            }    

            col.colided = false;
        }
    }
}
