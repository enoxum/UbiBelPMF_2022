#include "special-upboost.h"
#include "matattack.h"
#include "specialabilitysystem.h"
#include "gravitysystem.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"
#include "core/game/transforms.h"

using namespace matattack;

void UpBoost::Init(const Entity& character)
{
	auto& special_info = Engine::Registry().get<SpecialInfo>(character);

	special_info.max_charges = 2;
	special_info.current_charges = 2;

	special_info.duration = 0;
	special_info.current_duration = 0;

	special_info.cooldown = 0.5;
	special_info.current_cooldown = 0;

	special_info.current_chargetime = 0;
	special_info.chargetime = 2;
}

void UpBoost::Start(const Entity& character)
{
	auto&& [special_info,gravity] = Engine::Registry().get<SpecialInfo,Gravity>(character);

	if (special_info.current_charges > 0)
	{
		special_info.current_charges--;
		special_info.current_cooldown = special_info.cooldown;
		gravity.speed = -upboost_info.speed;
		Logger::critical("Boost");
	}
}

void UpBoost::Run(const Entity& character)
{
}
