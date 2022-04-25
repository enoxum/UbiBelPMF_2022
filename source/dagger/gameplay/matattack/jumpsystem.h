#pragma once

#include "core/core.h"
#include "core/system.h"

#include "characterjumpfsm.h"

using namespace dagger;

namespace matattack
{
	class JumpSystem : public System
	{
	public:

		FSMCharacterJump jumpFSM;

		String SystemName() override {
			return "Jump System";
		}

		void Run() override;

	};
}