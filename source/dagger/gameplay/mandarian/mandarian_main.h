#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"

using namespace dagger;

namespace mandarian
{
    class MandarianGame : public Game
    {
    public:
        inline String GetIniFile() override
        {
            return "mandarian.ini";
        };

        void GameplaySystemsSetup() override;
        void WorldSetup() override;

    private:
        void SetupCamera();
        void CreateMap();
        void CreateEnemies(Entity mandarian);
    };

};