#include "characterattackfsm.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/game/transforms.h"

#include "gravitysystem.h"
#include "matattack.h"
#include "gameplay/common/simple_collisions.h"

void FSMCharacterAttack::DetectPlayerCollision(PlayerCollisionEvent ev)
{
	auto view = Engine::Registry().view<AttackInfo>();
	auto it1 = view.begin();
	auto it2 = it1;
	it2++;
	auto &p1_attack_info = view.get<AttackInfo>(*it1);
	auto &p2_attack_info = view.get<AttackInfo>(*it2);

	if (ev.collision)
	{
		if (p1_attack_info.is_attacking)
		{
			p2_attack_info.is_attacked = true;
		}
		else {
			p2_attack_info.is_attacked = false;
		}

		if (p2_attack_info.is_attacking)
		{
			p1_attack_info.is_attacked = true;
		}
		else{
			p1_attack_info.is_attacked = false;
		}
	}
	else {
		p1_attack_info.is_attacked = false;
		p2_attack_info.is_attacked = false;
	}
}

void FSMCharacterAttack::NoAction::Enter(FSMCharacterAttack::StateComponent& state_)
{
	//auto& animator = Engine::Registry().get<Animator>(state_.entity);
	//AnimatorPlay(animator, "matattack:idle");
}

void FSMCharacterAttack::NoAction::Run(FSMCharacterAttack::StateComponent& state_)
{
	auto&& [input, attack_info] = Engine::Registry().get<InputReceiver, AttackInfo>(state_.entity);
	// sviPlayeri = view()<CharacterInfo>;

	if (EPSILON_NOT_ZERO(input.Get("attack")))
	{
		attack_info.is_attacking = true;
	}
	else{
		attack_info.is_attacking = false;
	}

	if (attack_info.is_attacked) {
		GoTo(EAttackStates::IsAttacked, state_);
	}
}

DEFAULT_EXIT(FSMCharacterAttack, NoAction);


// kada napada



// kad je napadnut
void FSMCharacterAttack::IsAttacked::Enter(FSMCharacterAttack::StateComponent& state_)
{
	auto& animator = Engine::Registry().get<Animator>(state_.entity);
	// ovako neka animacija vrv 
	//AnimatorPlay(animator, "matattack:attacked");
	/*auto& char_info = Engine::Registry().get<matattack::CharacterInfo>(state_.entity);
	char_info.is_attacking = true;*/
}

void FSMCharacterAttack::IsAttacked::Run(FSMCharacterAttack::StateComponent& state_)
{
	auto& attack_info = Engine::Registry().get<AttackInfo>(state_.entity);

	// sistem koji te odgurava

	attack_info.hp -= 10;
	Logger::trace(attack_info.hp);

	GoTo(EAttackStates::NoAction, state_);
}

DEFAULT_EXIT(FSMCharacterAttack, IsAttacked);

// moramo char_info.is_attacked da stavimo na false, nakon sto je jelte hit-ovan