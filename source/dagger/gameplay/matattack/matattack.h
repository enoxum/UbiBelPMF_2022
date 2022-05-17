#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"
#include "core/game/transforms.h"
#include "core/graphics/sprite.h"
#include "specialabilitysystem.h"



using namespace dagger;

namespace matattack
{
    struct CharacterInfo
    {
        Float32 speed;
        Float32 side;
        String animationName;
    };

    void SetupWorld(int lvl, String fstCharSprite, String sndCharSprite, String fstCharAnimation, String sndCharAnimation, SpecialAbilities specAttack1, SpecialAbilities specAttack2);
    void SetLevelChooser();
    void EndGame(String char_won);

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
