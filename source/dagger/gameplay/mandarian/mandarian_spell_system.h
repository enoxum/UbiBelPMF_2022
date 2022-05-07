#pragma once

#include "core/core.h"
#include "core/system.h"

#include "core/game/transforms.h"
#include "gameplay/common/simple_physics.h"
#include "core/graphics/sprite.h"

using namespace dagger;

namespace mandarian
{

    struct SpellTag
    {
        Bool tag;
    };

    struct Aura
    {
        Float32 cooldown;
        Float32 damage;
        Float32 radius;
        Bool global;  
    };

    struct AuraOfMandarian
    {
        Entity entity;
        Aura &aura;
        Sprite &sprite;
        Transform &transform;

        static AuraOfMandarian Get(Entity entity);
        static AuraOfMandarian Create(Float32 cooldown_ = 10.0f
                                    , Float32 damage_ = 0.2f
                                    , Float32 radius_ = 100.0f
                                    , Bool global_ = false);
    };

    class MandarianSpellSystem
        : public System
    {
        inline String SystemName() override 
        {
            return "Mandarian Damage System";
        };

        void CastAuraOfMandarian();
        void Run() override;
    };

};