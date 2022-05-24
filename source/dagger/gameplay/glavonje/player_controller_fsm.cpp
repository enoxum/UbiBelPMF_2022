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
	

//new IDLE rn state
//void FSMPlayerController::Idle::Run(FSMPlayerController::StateComponent& state_){

 //   auto& input = Engine::Registry().get<InputReceiver>(state_.entity);
	
//	if (EPSILON_NOT_ZERO(input.Get("runUp")) || EPSILON_NOT_ZERO(input.Get("runDown"))
//     || EPSILON_NOT_ZERO(input.Get("runLeft")) || EPSILON_NOT_ZERO(input.Get("runRight")))
//	{
//		GoTo(EPlayerStates::Running, state_);
//	}

//}
 

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


//run with jumping
//void FSMPlayerController::Running::Run(FSMPlayerController::StateComponent& state_){
  //  auto&& [sprite, input, player] = Engine::Registry().get<Sprite, InputReceiver, glavonje::PlayerCharacter>(state_.entity);

    //Float32 runUp = input.Get("runUp");
    //Float32 runDown = input.Get("runDown");
    //Float32 runLeft = input.Get("runLeft");
    //Float32 runRight = input.Get("runRight");

	//if (EPSILON_ZERO(runUp) && EPSILON_ZERO(runDown) && EPSILON_ZERO(runLeft) && EPSILON_ZERO(runRight))
	//{
	//	player.velocity.x = 0.0f;
	//	player.velocity.y = 0.0f
	//	GoTo(EPlayerStates::Idle, state_);
	//}
	//else
	//{
	//	Vector2 runningForce = { 0.0f, 0.0f };

	//	runningForce.y += runUp;
	//	runningForce.y -= runDown;
	//	runningForce.x -= runLeft;
	//	runningForce.x += runRight;

	//	if (EPSILON_NOT_ZERO(runningForce.x) && EPSILON_NOT_ZERO(runningForce.y))
	//		runningForce = NORMALIZE(runningForce);

	//
	//	player.velocity.x = 45.0f * runningForce.x;
	//	player.velocity.y = 45.0f * runningForce.y;
	//}
//}


