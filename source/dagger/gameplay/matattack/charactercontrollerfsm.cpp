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
	AnimatorPlay(animator, "matattack:idle");
}

DEFAULT_EXIT(FSMCharacterController, Idle);

void FSMCharacterController::Idle::Run(FSMCharacterController::StateComponent& state_)
{
	auto& input = Engine::Registry().get<InputReceiver>(state_.entity);

	if (EPSILON_NOT_ZERO(input.Get("run")))
	{
		GoTo(ECharacterStates::Running, state_);
	}

	if (EPSILON_NOT_ZERO(input.Get("jump")))
	{
		GoTo(ECharacterStates::Jumping, state_);
	}
	
}

// Jumping
void FSMCharacterController::Jumping::Enter(FSMCharacterController::StateComponent& state_)
{
	auto& animator = Engine::Registry().get<Animator>(state_.entity);
	// animacija za skok, trenutno nemamo!
}

DEFAULT_EXIT(FSMCharacterController, Jumping);

void FSMCharacterController::Jumping::Run(FSMCharacterController::StateComponent& state_)
{

	auto&& [sprite, input, character, transform, simple_colision] =
		Engine::Registry().get<Sprite, InputReceiver, matattack::CharacterInfo, Transform, SimpleCollision>(state_.entity);

	Float32 jump = input.Get("jump");

	if (EPSILON_ZERO(jump)) {
		GoTo(ECharacterStates::Idle, state_);
	}
	else {
		sprite.position = transform.position;
	}
}


// Running
void FSMCharacterController::Running::Enter(FSMCharacterController::StateComponent& state_)
{
	auto& animator = Engine::Registry().get<Animator>(state_.entity);
	AnimatorPlay(animator, "matattack:run");
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
		sprite.position = transform.position;

	}
}

