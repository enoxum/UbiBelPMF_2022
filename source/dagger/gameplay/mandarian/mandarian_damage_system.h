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

    struct DamagingTag
    {
        Bool tag;
    };

    struct DamageData
    {
        Float32 damage;
        Float32 radius;
        Bool global;
    };

    struct Damaging
    {
        Entity entity;
        DamageData &data;
        Transform &transform;

        static Damaging Get(Entity entity);
        static Damaging Create(Float32 damage, Float32 radius, Vector3 position, Bool global);
    };

    class MandarianDamageSystem
        : public System
    {
        inline String SystemName() override {
            return "Mandarian Damage System";
        };

        void DealDamage(Enemy, Damaging);
        void Kill(Enemy);

        void Run() override;
    };
}