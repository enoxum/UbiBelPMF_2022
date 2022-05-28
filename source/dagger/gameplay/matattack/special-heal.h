#pragma once
#include "core/core.h"
#include "core/engine.h"
#include "ispecialability.h"

namespace matattack
{
    struct HealInfo {
        SInt32 heal_amount = 10;
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