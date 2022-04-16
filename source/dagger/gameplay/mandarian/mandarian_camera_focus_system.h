#pragma once

#include "core/core.h"
#include "core/system.h"

using namespace dagger;

namespace mandarian
{
    struct MandarianCameraFollowFocus
    {
        UInt32 weight{ 1 };
    };

    class MandarianCameraFocusSystem
        : public System
    {
        inline String SystemName() override {
            return "Mandarian Camera Focus System";
        };

        void Run() override;
    };
}