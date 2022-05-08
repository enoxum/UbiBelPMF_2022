#pragma once
#include "core/core.h"
#include "core/engine.h"
#include "ispecialability.h"

namespace matattack
{
    struct HealInfo {
        SInt32 max_heal_amount = 50;
        SInt32 heal_decrease = 1;
        SInt32 heal_amount = 0;
    };

    class Heal : public ISpecialAbility
    {
    public:
        void Init(const Entity& character) override;
        void Start(const Entity& character) override;
        void Run(const Entity& character) override;
    private:
        HealInfo heal_info;
    };
}