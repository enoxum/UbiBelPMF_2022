#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"
#include "core/game/transforms.h"
#include "core/graphics/sprite.h"



using namespace dagger;

namespace matattack
{

    // ovu komponentu pravimo, da bismo razlikovali one koje slusaju input, i na njega se pomeraju!
    struct CharacterInfo
    {
        Float32 speed;
        String animationName;
    };

    struct ArrowInfo
    {
        Sprite& arrowSprite;
        Transform& arrowTransform;
    };

    void SetupWorld(int lvl, String fstCharSprite, String sndCharSprite, String fstCharAnimation, String sndCharAnimation);
    void SetLevelChooser();
    void CreateBackdrop(String background_path);

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
