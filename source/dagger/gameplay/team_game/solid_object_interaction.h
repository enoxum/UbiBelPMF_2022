#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"

using namespace dagger;

namespace team_game
{
    struct Platform {
        String id;
    };

    class SolidObjectInteractionSystem : public System {
    public:
        inline String SystemName() { return "Solid object interaction system"; }
        void Run() override;

        void SpinUp() override;
        void WindDown() override;
    };

}