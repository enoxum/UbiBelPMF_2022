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

void FSMCharacterAttack::NoAction::Enter(FSMCharacterAttack::StateComponent& state_)
{
	//auto& animator = Engine::Registry().get<Animator>(state_.entity);
	//AnimatorPlay(animator, "matattack:idle");
}

void FSMCharacterAttack::NoAction::Run(FSMCharacterAttack::StateComponent& state_)
{
	auto&& [char_info, input] = Engine::Registry().get<matattack::CharacterInfo, InputReceiver>(state_.entity);
	// sviPlayeri = view()<CharacterInfo>;

	if (EPSILON_NOT_ZERO(input.Get("attack")))
	{
		GoTo(EAttackStates::Attacking, state_);
	}

	if (char_info.is_colliding_with_other_player && char_info.is_attacked) {
		GoTo(EAttackStates::IsAttacked, state_);
	}
}

DEFAULT_EXIT(FSMCharacterAttack, NoAction);


// kada napada
void FSMCharacterAttack::Attacking::Enter(FSMCharacterAttack::StateComponent& state_)
{
	auto& animator = Engine::Registry().get<Animator>(state_.entity);
	// ovako neka animacija vrv
	//AnimatorPlay(animator, "matattack:attack");
	auto& char_info = Engine::Registry().get<matattack::CharacterInfo>(state_.entity);
	char_info.is_attacking = true;
}

void FSMCharacterAttack::Attacking::Run(FSMCharacterAttack::StateComponent& state_)
{
	auto&& [char_info, input] = Engine::Registry().get<matattack::CharacterInfo, InputReceiver>(state_.entity);

	char_info.is_attacking = false;
	
	if (char_info.is_attacked) {
		GoTo(EAttackStates::IsAttacked, state_);
	}
	else {
		GoTo(EAttackStates::NoAction, state_);
	}
	
}

DEFAULT_EXIT(FSMCharacterAttack, Attacking);



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
	auto&& [char_info, input] = Engine::Registry().get<matattack::CharacterInfo, InputReceiver>(state_.entity);

	// sistem koji te odgurava

	char_info.hp -= 10;

	char_info.is_attacked = false;
	Logger::trace(char_info.hp);

	GoTo(EAttackStates::NoAction, state_);
}

DEFAULT_EXIT(FSMCharacterAttack, IsAttacked);

// moramo char_info.is_attacked da stavimo na false, nakon sto je jelte hit-ovan
