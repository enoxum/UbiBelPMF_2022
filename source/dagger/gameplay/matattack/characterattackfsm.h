#pragma once
#include "core/core.h"
#include "core/game/finite_state_machine.h"
#include "events.h"

struct AttackInfo {
	bool is_attacking = false;
	bool is_attacked = false;
	SInt32 attack_damage = 10;
	SInt32 hp = 100;
};


enum struct EAttackStates
{
	NoAction,
	IsAttacked
};

struct FSMCharacterAttack : public FSM<EAttackStates>
{
	DEFINE_STATE(FSMCharacterAttack, EAttackStates, NoAction);
	DEFINE_STATE(FSMCharacterAttack, EAttackStates, IsAttacked);

	void DetectPlayerCollision(PlayerCollisionEvent ev);

	FSMCharacterAttack()
	{
		CONNECT_STATE(EAttackStates, NoAction);
		CONNECT_STATE(EAttackStates, IsAttacked);
	}
};