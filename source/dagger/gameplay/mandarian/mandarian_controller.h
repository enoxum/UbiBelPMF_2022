#pragma once

#include "core/core.h"
#include "core/system.h"
#include "gameplay/mandarian/mandarian_controller_fsm.h"

#include "core/graphics/sprite.h"
#include "core/game/transforms.h"
#include "core/input/inputs.h"

#include "gameplay/common/simple_physics.h"

using namespace dagger;

namespace mandarian 
{
    struct Character
    {
        Entity entity;
        Sprite &sprite;
        Transform &transform;
        Body &body;
        InputReceiver &input;

        static Character Get(Entity);

        static Character Create(
                ColorRGB color_ = { 1.0f, 1.0f, 1.0f}, 
                Vector2 position_ = { 0.0f, 0.0f },
                Vector2 scale_ = { 10.0f, 10.0f },
                String input_ = String{ "mandarian" });
    };

    struct Player {
        bool b;
    };

	class MandarianControllerSystem
		: public System
	{
		MandarianControllerFSM mandarianFSM;

	public:
		String SystemName() override {
			return "Mandarian Controller System";
		}

		void Run() override;
	};

}