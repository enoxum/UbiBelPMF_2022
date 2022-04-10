#include "mandarian_controller_fsm.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/game/transforms.h"

#include "gameplay/mandarian/mandarian_controller.h"

using namespace dagger;
using namespace mandarian;

void MandarianControllerFSM::Idle::Enter(MandarianControllerFSM::StateComponent& state_)
{
}

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


// Running

void MandarianControllerFSM::Running::Enter(MandarianControllerFSM::StateComponent& state_) 
{
}

DEFAULT_EXIT(MandarianControllerFSM, Running);

void MandarianControllerFSM::Running::Run(MandarianControllerFSM::StateComponent& state_) 
{
	auto&& [sprite, transform, input] = Engine::Registry().get<Sprite, Transform, InputReceiver>(state_.entity);

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
		Vector2 runningVelocity = { 0.0f, 0.0f };

		runningVelocity.y += runUp;
		runningVelocity.y -= runDown;
		runningVelocity.x -= runLeft;
		runningVelocity.x += runRight;

		if (EPSILON_NOT_ZERO(runningVelocity.x) && EPSILON_NOT_ZERO(runningVelocity.y))
			runningVelocity = NORMALIZE(runningVelocity);

		transform.position.x += 100 * runningVelocity.x * Engine::DeltaTime();
		transform.position.y += 100 * runningVelocity.y * Engine::DeltaTime();
	}
}
