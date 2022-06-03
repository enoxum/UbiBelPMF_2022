#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"
#include "core/net/common/message.h"


using namespace dagger;

namespace net_test
{
    class NetTest : public Game
    {
        inline String GetIniFile() override
        {
            return "net_test.ini";
        };

        void CoreSystemsSetup() override;
        void GameplaySystemsSetup() override;
        void WorldSetup() override;
    };
    
}