#include "special-dash.h"
#include "specialabilitysystem.h"
#include "matattack.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"
#include "core/game/transforms.h"

using namespace matattack;

void Dash::Init(const Entity& character)
{
	auto& special_info = Engine::Registry().get<SpecialInfo>(character);

	special_info.max_charges = 2;
	special_info.current_charges = 2;

	special_info.duration = 2000;
	special_info.current_duration = 0;

	special_info.cooldown = 0.5;
	special_info.current_cooldown = 0;

	special_info.current_chargetime = 0;
	special_info.chargetime = 10;
}

void Dash::Start(const Entity& character)
{
	auto& special_info = Engine::Registry().get<SpecialInfo>(character);

	if (special_info.current_charges > 0)
	{
		special_info.current_charges--;
		special_info.current_cooldown = special_info.cooldown;
		special_info.current_duration = special_info.duration;
		dash_info.speed = dash_info.max_speed;
	}
}

void Dash::Run(const Entity& character)
{
	auto&& [special_info, transform, character_info] = Engine::Registry().get<SpecialInfo,Transform,CharacterInfo>(character);
	
	if (special_info.current_duration > 0)
	{
		
		transform.position.x += special_info.current_duration * Engine::DeltaTime() * character_info.side;

		special_info.current_duration -= dash_info.speed_decrease;
	}

}
