#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"

using namespace dagger;

namespace glavonje{

    struct Gravity{
        char s;
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
