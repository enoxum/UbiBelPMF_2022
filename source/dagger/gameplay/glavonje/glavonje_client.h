#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"

using namespace dagger;

namespace glavonje
{
    class GlavonjeClient : public Game
    {
        inline String GetIniFile() override
        {
            return "glavonje.ini";
        };

        // tmp
        void CoreSystemsSetup() override;

        void GameplaySystemsSetup() override;
        void WorldSetup() override;
    };
    
}