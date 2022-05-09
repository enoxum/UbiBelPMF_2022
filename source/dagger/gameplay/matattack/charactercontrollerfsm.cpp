#include "charactercontrollerfsm.h"
#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/game/transforms.h"

#include "matattack.h"
#include "gameplay/common/simple_collisions.h"

using namespace dagger;

// Idle
void FSMCharacterController::Idle::Enter(FSMCharacterController::StateComponent& state_)
{
	auto& animator = Engine::Registry().get<Animator>(state_.entity);
	auto& char_info = Engine::Registry().get<matattack::CharacterInfo>(state_.entity);
	AnimatorPlay(animator, "matattack:idle:" + char_info.animationName);
}

DEFAULT_EXIT(FSMCharacterController, Idle);

void FSMCharacterController::Idle::Run(FSMCharacterController::StateComponent& state_)
{
	auto& input = Engine::Registry().get<InputReceiver>(state_.entity);

	if (EPSILON_NOT_ZERO(input.Get("run")))
	{
		GoTo(ECharacterStates::Running, state_);
	}
	
}
// Running
void FSMCharacterController::Running::Enter(FSMCharacterController::StateComponent& state_)
{
	auto& animator = Engine::Registry().get<Animator>(state_.entity);
	auto& char_info = Engine::Registry().get<matattack::CharacterInfo>(state_.entity);
	AnimatorPlay(animator, "matattack:run:" + char_info.animationName);
}

// same as: DEFAULT_EXIT(CharacterControllerFSM, Running);
void FSMCharacterController::Running::Exit(FSMCharacterController::StateComponent& state_)
{}

void FSMCharacterController::Running::Run(FSMCharacterController::StateComponent& state_)
{

	auto&& [sprite, input, character, transform, simple_colision] =
		Engine::Registry().get<Sprite, InputReceiver, matattack::CharacterInfo, Transform, SimpleCollision>(state_.entity);

	Float32 run = input.Get("run");

	if (EPSILON_ZERO(run))
	{
		GoTo(ECharacterStates::Idle, state_);
	}
	else
	{
		sprite.scale.x = run*1.5; // rotira dok trci sprite
		//sprite.scale.y = jump;

		// zasto su ovde samo sprite menjali poziciju, a ne i od transform-a?
		//sprite.position.x = transform.position.x;
		//sprite.position.x += character.speed * run * Engine::DeltaTime();
		sprite.position = transform.position;

		//transform.position.x += character.speed * run * Engine::DeltaTime();

		// trebalo bi specijalno stanje, kad je jump, pa u njega da idemo, ali neka ostane ovde za sad
		// => isto spec stanje za padanje tj gravitacija
		//sprite.position.y = transform.position.y;
		//transform.position.y += character.speed * jump * Engine::DeltaTime();

		// ovde bi ubacili gravitaciju, da uvek pada => ili bi bio sistem??
	}
}