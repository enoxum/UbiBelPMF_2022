#pragma once
#include "ispecialability.h"
#include "core/core.h"
#include "core/system.h"

using namespace dagger;

enum SpecialAbilities
{
    DASH = 0,
    DOUBLE_JUMP = 1
};

namespace matattack
{
    struct SpecialInfo {
        SpecialAbilities special_name;
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