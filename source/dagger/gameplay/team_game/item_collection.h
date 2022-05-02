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
    };

    struct CollectedItem {
        String id;
    };

    class ItemCollectionSystem : public System {
    public:
        inline String SystemName() { return "Item collection system"; }
        void Run() override;

        void SpinUp() override;
        void WindDown() override;
    };

}