#pragma once
#include "core/core.h"
#include "core/game/finite_state_machine.h"

struct UpSpeed {
	Float32 baseSpeed;
	Float32 decrease;
	Float32 upspeed;
};

enum struct EJumpStates
{
	OnGround,
	GoingUp,
	GoingDown
};

struct FSMCharacterJump : public FSM<EJumpStates>
{
	DEFINE_STATE(FSMCharacterController, EJumpStates, OnGround);
	DEFINE_STATE(FSMCharacterController, EJumpStates, GoingUp);
	DEFINE_STATE(FSMCharacterController, EJumpStates, GoingDown);

	FSMCharacterJump()
	{
		CONNECT_STATE(EJumpStates, OnGround);
		CONNECT_STATE(EJumpStates, GoingUp);
		CONNECT_STATE(EJumpStates, GoingDown);
	}
};