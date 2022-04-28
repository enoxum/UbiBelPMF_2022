#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"

using namespace dagger;

namespace team_game
{
    // bool operator== (const Item& item1, const Item& item2) 
    struct Item {
        String id;

        friend bool operator== (const Item& item1, const Item& item2) {
            return item1.id == item2.id;
        }   
    };

    class ItemCollectionSystem : public System {
    public:
        inline String SystemName() { return "Item collection system"; }
        void Run() override;

        void SpinUp() override;
        void WindDown() override;
    };

}