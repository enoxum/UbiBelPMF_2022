#pragma once

#include "core/core.h"
#include "core/system.h"

#include "core/game/transforms.h"
#include "gameplay/common/simple_physics.h"

using namespace dagger;

namespace mandarian
{

    class MandarianSpellSystem
        : public System
    {
        inline String SystemName() override 
        {
            return "Mandarian Damage System";
        };

        void Run() override;
    };

};