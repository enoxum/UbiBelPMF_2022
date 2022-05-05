#pragma once
#include "core/core.h"
#include "core/engine.h"

namespace matattack
{
    class ISpecialAbility
    {
    public:
        virtual void Run(const Entity &character) = 0;
    };
}