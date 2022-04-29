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
        Float32 speed;
        bool is_colliding_with_other_player{ false };
        bool is_attacking{ false };
        bool is_attacked{ false };
        int hp{ 100 };
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
