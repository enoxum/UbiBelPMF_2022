#pragma once
#include "ispecialability.h"
#include "core/core.h"
#include "core/system.h"

using namespace dagger;

enum SpecialAbilities
{
    DASH = 0,
    UP_BOOST = 1,
    HEAL = 2,
    ATTACK_BOOST = 3,
};

namespace matattack
{
    struct SpecialInfo {
        SpecialAbilities name;

        Float32 duration = 0;
        Float32 current_duration = 0;

        Float32 cooldown = 0;
        Float32 current_cooldown = 0;

        SInt16 max_charges = 0;
        SInt16 current_charges = 0;

        Float32 chargetime = 0;
        Float32 current_chargetime = 0;


    };

    struct SpecialBarInfo {
        Float32 full_scale = 0;
        bool bar = true;
    };

    struct SpecialBarBackInfo {
        bool active = true;
    };

    class SpecialAbilitySystem : public System
    {
    public:
        String SystemName() override {
            return "Character Special Ability System";
        }

        std::vector<ISpecialAbility*> specialAbilities;

        void SpinUp() override;
        void Run() override;
    };
}