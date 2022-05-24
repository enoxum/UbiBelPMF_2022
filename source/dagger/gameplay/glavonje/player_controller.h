#pragma once

#include "core/core.h"
#include "core/system.h"
#include "gameplay/glavonje/player_controller_fsm.h"

using namespace dagger;

namespace glavonje
{	
	struct PlayerCharacter
	{
		Vector2 velocity{ 0.0f, 0.0f };
		Float32 speed{1.0f};
		int goals{0};

	};

	class PlayerControllerSystem
		: public System
	{
		FSMPlayerController playerFSM;

	public:
		String SystemName() override {
			return "Player Controller System";
		}

		void Run() override;
	};
}