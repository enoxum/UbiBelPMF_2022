#pragma once

#include "core/core.h"
#include "core/system.h"

using namespace dagger;

namespace mandarian
{
    class MandarianMovementConstraintSystem
        : public System
    {
        const float HEIGHT = 1500.0f;
        const float WIDTH = 1500.0f;
        inline String SystemName() override {
            return "Mandarian Movement Constraint System";
        };

        void Run() override;
    };
}