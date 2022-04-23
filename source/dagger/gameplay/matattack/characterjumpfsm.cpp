#include "characterjumpfsm.h"
#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/game/transforms.h"

#include "matattack.h"
#include "gameplay/common/simple_collisions.h"

using namespace dagger;


void FSMCharacterJump::OnGround::Enter(FSMCharacterJump::StateComponent& state_)
{
	auto& animator = Engine::Registry().get<Animator>(state_.entity);
	//AnimatorPlay(animator, "matattack:idle");
}

void FSMCharacterJump::OnGround::Run(FSMCharacterJump::StateComponent& state_)
{
	auto&& [input,simple_collision] = Engine::Registry().get<InputReceiver,SimpleCollision>(state_.entity);

	if (EPSILON_NOT_ZERO(input.Get("jump")))
	{
		GoTo(EJumpStates::GoingUp, state_);
	}

	if (simple_collision.colided) {
		GoTo(EJumpStates::GoingDown, state_);
	}
}

void FSMCharacterJump::OnGround::Exit(FSMCharacterJump::StateComponent& state_) {}

void FSMCharacterJump::GoingUp::Enter(FSMCharacterJump::StateComponent& state_)
{
	auto&& [animator, character, upspeed] = Engine::Registry().get<Animator, matattack::CharacterInfo, UpSpeed>(state_.entity);
	upspeed.upspeed = upspeed.baseSpeed;
	//AnimatorPlay(animator, "matattack:jumping");
}

void FSMCharacterJump::GoingUp::Run(FSMCharacterJump::StateComponent& state_)
{
	auto&& [sprite, input, character, transform, upspeed] =
		Engine::Registry().get<Sprite, InputReceiver, matattack::CharacterInfo, Transform, UpSpeed>(state_.entity);

	Float32 jump = input.Get("jump");

	if (!EPSILON_NOT_ZERO(jump) || upspeed.upspeed <= 0)
	{
		GoTo(EJumpStates::GoingDown, state_);
	}

	transform.position.y += upspeed.upspeed * Engine::DeltaTime();
	upspeed.upspeed -= upspeed.decrease * Engine::DeltaTime();

}

void FSMCharacterJump::GoingUp::Exit(FSMCharacterJump::StateComponent& state_) {}

void FSMCharacterJump::GoingDown::Enter(FSMCharacterJump::StateComponent& state_)
{
	auto&& [animator, character, upspeed] = Engine::Registry().get<Animator, matattack::CharacterInfo, UpSpeed>(state_.entity);
	upspeed.upspeed = 0;
	//AnimatorPlay(animator, "matattack:falling");
}

void FSMCharacterJump::GoingDown::Run(FSMCharacterJump::StateComponent& state_)
{
	auto&& [sprite, input, character, transform, simple_collision, upspeed] =
		Engine::Registry().get<Sprite, InputReceiver, matattack::CharacterInfo, Transform, SimpleCollision, UpSpeed>(state_.entity);

	if (simple_collision.colided) {
		GoTo(EJumpStates::OnGround, state_);
	}

}

void FSMCharacterJump::GoingDown::Exit(FSMCharacterJump::StateComponent& state_) {}