#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"

#include "core/graphics/sprite.h"
#include "core/game/transforms.h"
#include "core/input/inputs.h"

using namespace dagger;

namespace mandarian
{

    struct Character
    {
        Entity entity;
        Sprite &sprite;
        Transform &transform;
        InputReceiver &input;

        static Character Get(Entity);

        static Character Create(
                ColorRGB color_ = { 1.0f, 1.0f, 1.0f}, 
                Vector2 position_ = { 0.0f, 0.0f },
                Vector2 scale_ = { 10.0f, 10.0f },
                String input_ = String{ "mandarian" });
    };

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

    };

};