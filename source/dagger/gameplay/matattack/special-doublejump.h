#pragma once
#include "core/core.h"
#include "core/engine.h"
#include "ispecialability.h"

namespace matattack
{
    class DoubleJump : public ISpecialAbility
    {
    public:
        void Run(const Entity& character) override;
    };
}