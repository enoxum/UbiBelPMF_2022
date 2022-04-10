#pragma once

#include "core/core.h"
#include "core/game/finite_state_machine.h"

namespace mandarian
{
	enum struct EMandarianStates
	{
		Idle,
		Running
	};

	struct MandarianControllerFSM : public FSM<EMandarianStates>
	{
		DEFINE_STATE(MandarianControllerFSM, EMandarianStates, Idle);
		DEFINE_STATE(MandarianControllerFSM, EMandarianStates, Running);

		MandarianControllerFSM()
		{
			CONNECT_STATE(EMandarianStates, Idle);
			CONNECT_STATE(EMandarianStates, Running);
		}
	};

};