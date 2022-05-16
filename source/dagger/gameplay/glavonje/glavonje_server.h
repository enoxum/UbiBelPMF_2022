#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"

using namespace dagger;

namespace glavonje
{
    class GlavonjeServer : public Game
    {
        inline String GetIniFile() override
        {
            return "glavonje.ini";
        };

        void GameplaySystemsSetup() override;
        void WorldSetup() override;
    };
    
}