#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"

using namespace dagger;

namespace team_game
{
    class StorageSystem : public System {

    private:
        Vector2 screenSize = { 0.0, 0.0 };
        int selectedItem = 0;
        void OnKeyboardEvent(KeyboardEvent kEvent_);

    public:

        inline String SystemName() { return "Storage system"; }
        void Run() override;
        void SpinUp() override;
        void WindDown() override;

    };

}