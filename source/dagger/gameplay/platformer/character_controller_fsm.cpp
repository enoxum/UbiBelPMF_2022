#include "character_controller_fsm.h"
#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "gameplay/platformer/platformer_controller.h"

using namespace dagger;

// Idle


void CharacterControllerFSM::Idle::Enter(CharacterControllerFSM::StateComponent& state_)
{
	auto& animator = Engine::Registry().get<Animator>(state_.entity);
	AnimatorPlay(animator, "souls_like_knight_character:IDLE");
}

DEFAULT_EXIT(CharacterControllerFSM, Idle);

void CharacterControllerFSM::Idle::Run(CharacterControllerFSM::StateComponent& state_) 
{
	auto& input = Engine::Registry().get<InputReceiver>(state_.entity);

	if (EPSILON_NOT_ZERO(input.Get("run")))
	{
		GoTo(ECharacterStates::Running, state_);
	}
}


// Running

void CharacterControllerFSM::Running::Enter(CharacterControllerFSM::StateComponent& state_) 
{
	auto& animator = Engine::Registry().get<Animator>(state_.entity);
	AnimatorPlay(animator, "souls_like_knight_character:RUN");
}

// same as: DEFAULT_EXIT(CharacterControllerFSM, Running);
void CharacterControllerFSM::Running::Exit(CharacterControllerFSM::StateComponent& state_) 
{}

void CharacterControllerFSM::Running::Run(CharacterControllerFSM::StateComponent& state_) 
{
	auto&& [sprite, input, character] = Engine::Registry().get<Sprite, InputReceiver, platformer::PlatformerCharacter>(state_.entity);

	Float32 run = input.Get("run");

	if (EPSILON_ZERO(run))
	{
		GoTo(ECharacterStates::Idle, state_);
	}
	else
	{
		sprite.scale.x = run;
		sprite.position.x += character.speed * sprite.scale.x * Engine::DeltaTime();
	}
}
