#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"

using namespace dagger;

namespace team_game
{
    struct Gravity {
        char c;
    };

    class GravitySystem : public System {

    public:
        static const double gravityForce;

        inline String SystemName() { return "Gravity control system"; }
        void Run() override;

        void SpinUp() override;
        void WindDown() override;

    };

}