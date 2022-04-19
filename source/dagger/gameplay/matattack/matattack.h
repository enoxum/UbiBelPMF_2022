#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"

using namespace dagger;

namespace matattack
{

    // ovu komponentu pravimo, da bismo razlikovali one koje slusaju input, i na njega se pomeraju!
    struct CharacterInfo
    {
        int speed{ 50 };
    };

    void SetupWorld();

    class Matattack : public Game
    {
        inline String GetIniFile() override
        {
            return "matattack.ini";
        };

        void GameplaySystemsSetup() override;
        void WorldSetup() override;
    };
}
