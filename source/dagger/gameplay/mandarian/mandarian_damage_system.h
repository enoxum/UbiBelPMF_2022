#pragma once

#include "core/core.h"
#include "core/system.h"
#include "mandarian_enemy.h"

using namespace dagger;

namespace mandarian
{

    struct Enemy;

    struct Health
    {
        Float32 current;
        Float32 min;
        Float32 max;
        Bool immortal;
    };

    struct Damage
    {
        UInt32 amount;
    };

    class MandarianDamageSystem
        : public System
    {
        inline String SystemName() override {
            return "Mandarian Damage System";
        };

        void DealDamage(Enemy, Float32);
        void Kill(Enemy);

        void Run() override;
    };
}