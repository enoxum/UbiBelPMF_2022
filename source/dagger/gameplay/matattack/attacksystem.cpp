#include "attacksystem.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"

using namespace matattack;

void AttackSystem::DealDamage(AttackInfo& attacker_info, AttackInfo& victim_info)
{
	victim_info.hp -= attacker_info.attack_damage;
	victim_info.imunity_duration = victim_info.base_imunity_duration;
	Logger::critical(victim_info.hp);
}

void AttackSystem::DetectPlayerCollision()
{
	auto view = Engine::Registry().view<AttackInfo>();
	auto it1 = view.begin();
	auto it2 = it1;
	it2++;
	auto& p1_attack_info = view.get<AttackInfo>(*it1);
	auto& p2_attack_info = view.get<AttackInfo>(*it2);

	if (p1_attack_info.is_attacking && p2_attack_info.imunity_duration == 0)
	{
		DealDamage(p1_attack_info,p2_attack_info);
	}

	if (p2_attack_info.is_attacking && p1_attack_info.imunity_duration == 0)
	{
		DealDamage(p2_attack_info, p1_attack_info);
	}
}


void AttackSystem::SpinUp() 
{
    Engine::Dispatcher().sink<PlayerCollisionEvent>().connect<&AttackSystem::DetectPlayerCollision>(this);
};

void AttackSystem::Run()
{
	auto view = Engine::Registry().view<InputReceiver, Animator, AttackInfo>();

	auto it = view.begin();

	while (it != view.end())
	{
		auto& input = view.get<InputReceiver>(*it);
		auto& animator = view.get<Animator>(*it);
		auto& attack_info = view.get<AttackInfo>(*it);
		
		if (EPSILON_NOT_ZERO(input.Get("attack"))) {
			attack_info.is_attacking = true;
		}
		else {
			attack_info.is_attacking = false;
		}

		if (attack_info.imunity_duration > 0) {
			attack_info.imunity_duration--;
		}

		it++;
	}
}

void AttackSystem::WindDown() 
{
    Engine::Dispatcher().sink<PlayerCollisionEvent>().disconnect<&AttackSystem::DetectPlayerCollision>(this);
};