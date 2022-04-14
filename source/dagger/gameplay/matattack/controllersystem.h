#pragma once

#include "core/core.h"
#include "core/system.h"

#include "charactercontrollerfsm.h"

using namespace dagger;

namespace matattack
{
	class ControllerSystem : public System
	{
	public:

		FSMCharacterController characterFSM;

		String SystemName() override {
			return "Controller System";
		}

		void Run() override;

	};
}