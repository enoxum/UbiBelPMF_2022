#pragma once

#include "core/core.h"
#include "core/system.h"
#include "gameplay/glavonje/player_controller_fsm.h"

using namespace dagger;

namespace glavonje
{
	struct PlayerCharacter
	{
		float speed{ 1.0 };
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