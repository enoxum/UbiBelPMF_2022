#pragma once
#include "core/core.h"
#include "core/engine.h"
#include "ispecialability.h"

namespace matattack
{
    struct DamageBoostInfo {
        SInt32 boost = 5;
        bool boost_added = false;
        // verovatno bolji nacin => pitaj bakija
        Float32 boost_duration = 0;
        Float32 max_boost_duration = 10;

    };

    class DamageBoost : public ISpecialAbility
    {
    public:
        void Init(const Entity& character) override;
        void Start(const Entity& character) override;
        void Run(const Entity& character) override;
    private:
        DamageBoostInfo damage_boost_info;
    };
}