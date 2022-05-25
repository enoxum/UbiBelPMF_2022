#include "specialabilitysystem.h"
#include "attacksystem.h"
#include "matattack.h"
#include "special-dash.h"
#include "special-upboost.h"
#include "special-heal.h"
#include "special-damage.h"

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
	specialAbilities.push_back(new UpBoost());
	specialAbilities.push_back(new Heal());
	specialAbilities.push_back(new DamageBoost());
}

void SpecialAbilitySystem::Run() {
	auto view = Engine::Registry().view<InputReceiver, SpecialInfo>();
	auto bars = Engine::Registry().view<SpecialBarInfo, Sprite, Transform>();
	auto barbacks = Engine::Registry().view<SpecialBarBackInfo, Sprite, Transform>();


	auto it = view.begin();
	auto bar1it = bars.begin();
	auto bar2it = bars.begin();

	auto barbackit = barbacks.begin();

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
		
		if (bar1it != bars.end() && bar2it != bars.end() && barbackit != barbacks.end()) {
			bar2it++;
			auto& bar1_sprite = bars.get<Sprite>(*bar1it);
			auto& bar1_info = bars.get<SpecialBarInfo>(*bar1it);
			auto& bar1_transform = bars.get<Transform>(*bar1it);

			auto& bar2_sprite = bars.get<Sprite>(*bar2it);
			auto& bar2_info = bars.get<SpecialBarInfo>(*bar2it);
			auto& bar2_transform = bars.get<Transform>(*bar2it);

			auto& barback_transform = barbacks.get<Transform>(*barbackit);


			if (special_info.current_charges != special_info.max_charges) {
				if (special_info.current_charges == 0) {
					bar2_sprite.scale = { 0,bar2_sprite.scale.y };
					bar1_sprite.scale = { bar1_info.full_scale * special_info.current_chargetime / special_info.chargetime,bar1_sprite.scale.y };
				}
				if (special_info.current_charges == 1) {
					bar2_sprite.scale = { bar2_info.full_scale * special_info.current_chargetime / special_info.chargetime,bar2_sprite.scale.y };
					bar1_sprite.scale = { bar1_info.full_scale,bar1_sprite.scale.y };
				}
			}
			bar1_transform.position = { barback_transform.position - Vector3(bar1_info.full_scale*388 - bar1_sprite.scale.x * 388 / 2 + 2, 0, 0) };
			bar2_transform.position = { barback_transform.position + Vector3(bar2_sprite.scale.x * 388 / 2 + 2, 0, 0) };

			bar1it++;
			bar1it++;
			bar2it++;
			barbackit++;
		}

		it++;
	}
}