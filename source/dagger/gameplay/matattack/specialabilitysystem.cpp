#include "specialabilitysystem.h"
#include "attacksystem.h"
#include "matattack.h"
#include "special-dash.h"
#include "special-doublejump.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"
#include "core/game/transforms.h"

using namespace matattack;

void SpecialAbilitySystem::SpinUp() {
	specialAbilities.push_back(new Dash());
	specialAbilities.push_back(new DoubleJump());
}

void SpecialAbilitySystem::Run() {
	auto view = Engine::Registry().view<InputReceiver, SpecialInfo>();

	auto it = view.begin();

	while (it != view.end())
	{
		auto& input = view.get<InputReceiver>(*it);
		auto& special_info = view.get<SpecialInfo>(*it);
		if (EPSILON_NOT_ZERO(input.Get("special")) && special_info.current_cooldown <= 0)
		{
			specialAbilities[special_info.name]->Start(*it);
		}

		specialAbilities[special_info.name]->Run(*it);

		if (special_info.current_cooldown > 0)
		{
			special_info.current_cooldown -= Engine::DeltaTime();
		}

		if(special_info.current_charges != special_info.max_charges)
		{
			special_info.current_chargetime += Engine::DeltaTime();
			if (special_info.current_chargetime >= special_info.chargetime) {
				special_info.current_charges++;
				special_info.current_chargetime = 0;
			}
		}

		it++;
	}
}