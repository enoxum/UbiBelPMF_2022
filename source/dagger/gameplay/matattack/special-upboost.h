#pragma once
#include "core/core.h"
#include "core/engine.h"
#include "ispecialability.h"

namespace matattack
{
    struct UpBoostInfo {
        Float32 speed = 500.0F;
    };

    class UpBoost : public ISpecialAbility
    {
    public:
        void Init(const Entity& character) override;
        void Start(const Entity& character) override;
        void Run(const Entity& character) override;

        UpBoostInfo upboost_info;
    };
}