#include "special-heal.h"
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

void Heal::Init(const Entity& character)
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

void Heal::Start(const Entity& character)
{
	auto& special_info = Engine::Registry().get<SpecialInfo>(character);

	if (special_info.current_charges > 0)
	{
		special_info.current_charges--;
		special_info.current_cooldown = special_info.cooldown;
		special_info.current_duration = special_info.duration;
		heal_info.heal_amount = heal_info.max_heal_amount;
	}
}

void Heal::Run(const Entity& character)
{
	auto&& [special_info, character_info, attack_info] = Engine::Registry().get<SpecialInfo, CharacterInfo, AttackInfo>(character);

	if (heal_info.heal_amount > 0)
	{
		special_info.current_duration -= Engine::DeltaTime();
		//heal_info.heal_amount -= heal_info.heal_decrease;
		attack_info.hp = std::min(attack_info.hp + heal_info.max_heal_amount, attack_info.max_hp);
		heal_info.heal_amount = 0;


	}

}