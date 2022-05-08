#include "special-damage.h"
#include "specialabilitysystem.h"
#include "matattack.h"
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

void DamageBoost::Init(const Entity& character)
{
	auto& special_info = Engine::Registry().get<SpecialInfo>(character);

	special_info.max_charges = 2;
	special_info.current_charges = 2;

	special_info.duration = 0;
	special_info.current_duration = 0;

	special_info.cooldown = 0.5;
	special_info.current_cooldown = 0;

	special_info.current_chargetime = 0;
	special_info.chargetime = 10;
}

void DamageBoost::Start(const Entity& character)
{
	auto& special_info = Engine::Registry().get<SpecialInfo>(character);

	if (special_info.current_charges > 0)
	{
		special_info.current_charges--;
		special_info.current_cooldown = special_info.cooldown;
		special_info.current_duration = special_info.duration;
		damage_boost_info.boost_duration = damage_boost_info.max_boost_duration;
		damage_boost_info.boost_added = false;
	}
}

void DamageBoost::Run(const Entity& character)
{
	auto&& [special_info, character_info, attack_info] = Engine::Registry().get<SpecialInfo, CharacterInfo, AttackInfo>(character);

	if (damage_boost_info.boost_duration > 0)
	{
		special_info.current_duration -= Engine::DeltaTime();

		damage_boost_info.boost_duration -= Engine::DeltaTime();

		if (!damage_boost_info.boost_added)
		{
			damage_boost_info.boost_added = true;
			attack_info.attack_damage += damage_boost_info.boost;
		}
	}
	else
	{
		attack_info.attack_damage = attack_info.max_attack_damage;
	}

}
