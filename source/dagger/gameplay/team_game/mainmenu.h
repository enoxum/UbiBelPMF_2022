#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"
#include <core/graphics/sprite.h>

using namespace dagger;

namespace team_game {

    struct MainMenu_ {
        bool show = true;
    };

	class mainmenu : public System
	{
    public:

        inline String SystemName() { return "Main menu system"; }
        void Run() override;

        void SpinUp() override;
        void WindDown() override;

    private:
        void OnKeyboardEvent(KeyboardEvent kEvent_);
        bool show = true;
        bool pause = false;
    };
};
