#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"

using namespace dagger;

namespace team_game
{
    struct Time {
        double seconds = 0.0;
    };

    class TimerSystem : public System {

    private:
    public:

        inline String SystemName() { return "Timer system"; }
        void Run() override;
        void SpinUp() override;
        void WindDown() override;

    };

}