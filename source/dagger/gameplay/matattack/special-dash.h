#pragma once
#include "core/core.h"
#include "core/engine.h"
#include "ispecialability.h"

namespace matattack
{
    struct DashInfo {
        Float32 max_speed = 2000;
        Float32 speed_decrease = 50;
        Float32 speed = 0;
    };

    class Dash : public ISpecialAbility
    {
    public:
        void Init(const Entity& character) override;
        void Start(const Entity& character) override;
        void Run(const Entity& character) override;
    private:
        DashInfo dash_info;
    };
}