#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"

#include "item_collection.h"
#include<vector>

#include "mainmenu.h"
#include <core/graphics/text.h>

using namespace dagger;

namespace team_game
{
    struct Player {
        bool jumping = false;
    };

    class PlayerControlSystem : public System {

        double step = 0.0f;
        //bool jumping = false;
        double jumpVelocity = 0.0f;
        bool m_restart = false;

    public:
        inline String SystemName() { return "Player control system"; }
        void Run() override;

        void OnEndOfFrame();

        void SpinUp() override;
        void WindDown() override;

    private:
        void OnKeyboardEvent(KeyboardEvent kEvent_);

    };

}