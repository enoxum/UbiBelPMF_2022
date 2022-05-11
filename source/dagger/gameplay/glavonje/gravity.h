#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"

using namespace dagger;

namespace glavonje{
    class GravitySystem : public System {

    public:
        static const double gravityForce;

        inline String SystemName() { return "Gravity System"; }
        void Run() override;

        void SpinUp() override;
        void WindDown() override;

        virtual ~GravitySystem() = default;

    };
}
