#pragma once
#include "core/core.h"
#include "core/game/finite_state_machine.h"
#include "events.h"


enum struct EAttackStates
{
	NoAction,
	Attacking,
	IsAttacked
};

struct FSMCharacterAttack : public FSM<EAttackStates>
{
	DEFINE_STATE(FSMCharacterAttack, EAttackStates, NoAction);
	DEFINE_STATE(FSMCharacterAttack, EAttackStates, Attacking);
	DEFINE_STATE(FSMCharacterAttack, EAttackStates, IsAttacked);

	bool DetectPlayerCollision(PlayerCollisionEvent ev);

	FSMCharacterAttack()
	{
		CONNECT_STATE(EAttackStates, NoAction);
		CONNECT_STATE(EAttackStates, Attacking);
		CONNECT_STATE(EAttackStates, IsAttacked);
	}
};