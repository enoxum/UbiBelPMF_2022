#include "attacksystem.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"
#include "core/game/transforms.h"

using namespace matattack;

void AttackSystem::DealDamage(AttackInfo& attacker_info, AttackInfo& victim_info, SInt32 num)
{
	victim_info.hp -= attacker_info.attack_damage;
	victim_info.imunity_duration = victim_info.base_imunity_duration;

	auto view1 = Engine::Registry().view<HealthInfo, Sprite>();
	auto it1 = view1.begin();
	auto view2 = Engine::Registry().view<HeartInfo, Sprite>();
	auto ih1 = view2.begin();
	if (num == 1)
	{
		auto& p1_health = view1.get<HealthInfo>(*it1);
		auto& p1_health_sprite = view1.get<Sprite>(*it1);
		auto& p1_heart = view2.get<HeartInfo>(*ih1);
		auto& p1_heart_sprite = view2.get<Sprite>(*ih1);
		AssignSprite(p1_health_sprite, "matattack:items:health_bar" + std::to_string(victim_info.hp));
		if (victim_info.hp == 0)
		{
			p1_health.num_of_hearts--;
			if (!p1_health.num_of_hearts)
			{
				Logger::critical("Player died!");
			}
			else
			{
				AssignSprite(p1_health_sprite, "matattack:items:health_bar");
				AssignSprite(p1_heart_sprite, "matattack:items:" + std::to_string(p1_health.num_of_hearts));
				victim_info.hp = 100;
			}
		}
	}
	else
	{
		auto it2 = it1;
		it2++;
		auto& p2_health = view1.get<HealthInfo>(*it2);
		auto& p2_health_sprite = view1.get<Sprite>(*it2);
		auto ih2 = ih1;
		ih2++;
		auto& p2_heart = view2.get<HeartInfo>(*ih2);
		auto& p2_heart_sprite = view2.get<Sprite>(*ih2);
		AssignSprite(p2_health_sprite, "matattack:items:health_bar" + std::to_string(victim_info.hp));
		if (victim_info.hp == 0)
		{
			p2_health.num_of_hearts--;
			if (!p2_health.num_of_hearts)
			{
				Logger::critical("Player died!");
			}
			else
			{
				AssignSprite(p2_health_sprite, "matattack:items:health_bar");
				AssignSprite(p2_heart_sprite, "matattack:items:" + std::to_string(p2_health.num_of_hearts));
				victim_info.hp = 100;
			}
		}
	}
	

}

void AttackSystem::KnockPlayer(KnockbackInfo& knockback_info, SInt16& direction)
{
	knockback_info.direction = direction;
	knockback_info.is_knocked = true;
}

void AttackSystem::DetectPlayerCollision()
{
	auto view = Engine::Registry().view<AttackInfo,Transform,KnockbackInfo>();
	auto it1 = view.begin();
	auto it2 = it1;
	it2++;
	auto& p1_attack_info = view.get<AttackInfo>(*it1);
	auto& p2_attack_info = view.get<AttackInfo>(*it2);
	auto& p1_knockback_info = view.get<KnockbackInfo>(*it1);
	auto& p2_knockback_info = view.get<KnockbackInfo>(*it2);
	auto& p1_transform = view.get<Transform>(*it1);
	auto& p2_transform = view.get<Transform>(*it2);

	if (p1_attack_info.is_attacking && p2_attack_info.imunity_duration == 0)
	{
		DealDamage(p1_attack_info,p2_attack_info, 2);
		SInt16 direction = p2_transform.position.x - p1_transform.position.x < 0 ? 1 : -1;
		KnockPlayer(p2_knockback_info, direction);
	}

	if (p2_attack_info.is_attacking && p1_attack_info.imunity_duration == 0)
	{
		DealDamage(p2_attack_info, p1_attack_info, 1);
		SInt16 direction = p1_transform.position.x - p2_transform.position.x < 0 ? 1 : -1;
		KnockPlayer(p1_knockback_info, direction);
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

		/*Logger::critical(attack_info.hp);
		Logger::critical(attack_info.attack_damage);*/

		
		if (EPSILON_NOT_ZERO(input.Get("attack")))
		{
			attack_info.is_attacking = true;
		}
		else
		{
			attack_info.is_attacking = false;
		}

		if (attack_info.imunity_duration > 0)
		{
			attack_info.imunity_duration--;
		}

		it++;
	}
}

void AttackSystem::WindDown() 
{
    Engine::Dispatcher().sink<PlayerCollisionEvent>().disconnect<&AttackSystem::DetectPlayerCollision>(this);
};