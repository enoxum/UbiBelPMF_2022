#pragma once
#include "core/core.h"
#include "core/game/finite_state_machine.h"

enum struct ECharacterStates
{
	Idle,
	Running
};

struct FSMCharacterController : public FSM<ECharacterStates>
{
	DEFINE_STATE(FSMCharacterController, ECharacterStates, Idle);
	DEFINE_STATE(FSMCharacterController, ECharacterStates, Running);

	FSMCharacterController()
	{
		CONNECT_STATE(ECharacterStates, Idle);
		CONNECT_STATE(ECharacterStates, Running);
	}
};