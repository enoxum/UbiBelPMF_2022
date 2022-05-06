#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"



using namespace dagger;

namespace glavonje
{
    void CreateBall(ColorRGBA ballColor, Vector3 ballSpeed, Vector3 ballPosition);

    class Glavonje : public Game
    {
        inline String GetIniFile() override
        {
            return "glavonje.ini";
        };

        void GameplaySystemsSetup() override;
        void WorldSetup() override;
    };
    
}