#include "mandarian_controller_fsm.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"

#include "gameplay/common/simple_physics.h"
#include "gameplay/mandarian/mandarian_controller.h"

using namespace dagger;
using namespace mandarian;

DEFAULT_ENTER(MandarianControllerFSM, Idle);
DEFAULT_EXIT(MandarianControllerFSM, Idle);

void MandarianControllerFSM::Idle::Run(MandarianControllerFSM::StateComponent& state_) 
{
	auto& input = Engine::Registry().get<InputReceiver>(state_.entity);

	if (EPSILON_NOT_ZERO(input.Get("runUp")) ||
		EPSILON_NOT_ZERO(input.Get("runDown")) ||
		EPSILON_NOT_ZERO(input.Get("runLeft")) ||
		EPSILON_NOT_ZERO(input.Get("runRight")))
	{
		GoTo(EMandarianStates::Running, state_);
	}
}

DEFAULT_ENTER(MandarianControllerFSM, Running);
DEFAULT_EXIT(MandarianControllerFSM, Running);

void MandarianControllerFSM::Running::Run(MandarianControllerFSM::StateComponent& state_) 
{
	auto&& [sprite, body, input] = Engine::Registry().get<Sprite, Body, InputReceiver>(state_.entity);

    Float32 runUp = input.Get("runUp");
    Float32 runDown = input.Get("runDown");
    Float32 runLeft = input.Get("runLeft");
    Float32 runRight = input.Get("runRight");

    if (EPSILON_ZERO(runUp) &&
		EPSILON_ZERO(runDown) &&
		EPSILON_ZERO(runLeft) &&
		EPSILON_ZERO(runRight))
	{
		GoTo(EMandarianStates::Idle, state_);
	}
	else
	{
		Vector2 runningForce = { 0.0f, 0.0f };

		runningForce.y += runUp;
		runningForce.y -= runDown;
		runningForce.x -= runLeft;
		runningForce.x += runRight;

		if (EPSILON_NOT_ZERO(runningForce.x) && EPSILON_NOT_ZERO(runningForce.y))
			runningForce = NORMALIZE(runningForce);


		body.applyForce(100.0f * runningForce);
	}
}
