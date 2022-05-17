#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"

using namespace dagger;

namespace glavonje{
    class BallCollisionSystem : public System {

    public:

        inline String SystemName() { return "BallCollision System"; }
        void Run() override;

        void SpinUp() override;
        void WindDown() override;

        virtual ~BallCollisionSystem() = default;

    };
}