#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"

using namespace dagger;

namespace team_game
{
    struct Time {
        char c;
    };

    class TimerSystem : public System {

    private:
        double seconds;
    public:

        inline String SystemName() { return "Timer system"; }
        void Run() override;
        void SpinUp() override;
        void WindDown() override;

    };

}