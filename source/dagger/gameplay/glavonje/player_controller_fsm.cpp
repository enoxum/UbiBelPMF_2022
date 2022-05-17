#include "player_controller_fsm.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/game/transforms.h"

#include "gameplay/glavonje/player_controller.h"

using namespace dagger;

void FSMPlayerController::Idle::Enter(FSMPlayerController::StateComponent& state_){
    auto& animation = Engine::Registry().get<Animator>(state_.entity);
    // AnimatorPlay(animation, "souls_like_knight_character:IDLE");
}

DEFAULT_EXIT(FSMPlayerController, Idle);

void FSMPlayerController::Idle::Run(FSMPlayerController::StateComponent& state_){

    auto& input = Engine::Registry().get<InputReceiver>(state_.entity);

    if (EPSILON_NOT_ZERO(input.Get("run")))
	{
		GoTo(EPlayerStates::Running, state_);
	}

}

void FSMPlayerController::Running::Enter(FSMPlayerController::StateComponent& state_){
    auto& animator = Engine::Registry().get<Animator>(state_.entity);

    // AnimatorPlay(animator, "souls_like_knight_character:RUN");
}

DEFAULT_EXIT(FSMPlayerController, Running);

void FSMPlayerController::Running::Run(FSMPlayerController::StateComponent& state_){
    auto&& [sprite,transform, input, player] = Engine::Registry().get<Sprite,Transform, InputReceiver, glavonje::PlayerCharacter>(state_.entity);

    Float32 run = input.Get("run");

	if (EPSILON_ZERO(run))
	{
		GoTo(EPlayerStates::Idle, state_);
	}
	else
	{
		sprite.scale.x = run;
		transform.position.x += (player.speed*1.5f) * sprite.scale.x * Engine::DeltaTime();
	}
}


