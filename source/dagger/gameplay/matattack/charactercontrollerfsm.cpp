#include "charactercontrollerfsm.h"
#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/game/transforms.h"

#include "matattack.h"

using namespace dagger;

// Idle


void CharacterControllerFSM::Idle::Enter(CharacterControllerFSM::StateComponent& state_)
{
	//Logger::trace("idle_enter");
	//auto& animator = Engine::Registry().get<Animator>(state_.entity);
	//AnimatorPlay(animator, "souls_like_knight_character:IDLE");
}

DEFAULT_EXIT(CharacterControllerFSM, Idle);

void CharacterControllerFSM::Idle::Run(CharacterControllerFSM::StateComponent& state_)
{
	auto& input = Engine::Registry().get<InputReceiver>(state_.entity);

	//Logger::trace("idle_run");

	if (EPSILON_NOT_ZERO(input.Get("run")) || EPSILON_NOT_ZERO(input.Get("jump")))
	{
		GoTo(ECharacterStates::Running, state_);
	}
}


// Running

void CharacterControllerFSM::Running::Enter(CharacterControllerFSM::StateComponent& state_)
{
	Logger::trace("running_enter");
	//auto& animator = Engine::Registry().get<Animator>(state_.entity);
	//AnimatorPlay(animator, "souls_like_knight_character:RUN");
}

// same as: DEFAULT_EXIT(CharacterControllerFSM, Running);
void CharacterControllerFSM::Running::Exit(CharacterControllerFSM::StateComponent& state_)
{}

void CharacterControllerFSM::Running::Run(CharacterControllerFSM::StateComponent& state_)
{

	//Logger::trace("running_run");


	auto&& [sprite, input, character, transform] =
		Engine::Registry().get<Sprite, InputReceiver, matattack::Character, Transform>(state_.entity);

	Float32 run = input.Get("run");
	Float32 jump = input.Get("jump");

	Logger::trace(jump);

	if (EPSILON_ZERO(run) && EPSILON_ZERO(jump))
	{
		GoTo(ECharacterStates::Idle, state_);
	}
	else
	{
		// zasto je ovo postojalo??
		//sprite.scale.x = run;
		//sprite.scale.y = jump;

		// zasto su ovde samo sprite menjali poziciju, a ne i od transform-a?
		//sprite.position.x = transform.position.x;
		sprite.position.x += character.speed * run * Engine::DeltaTime();
		transform.position.x += character.speed * run * Engine::DeltaTime();

		// trebalo bi specijalno stanje, kad je jump, pa u njega da idemo, ali neka ostane ovde za sad
		// => isto spec stanje za padanje tj gravitacija
		sprite.position.y += character.speed * jump * Engine::DeltaTime();
		transform.position.y += character.speed * jump * Engine::DeltaTime();

		// ovde bi ubacili gravitaciju, da uvek pada => ili bi bio sistem??
	}
}