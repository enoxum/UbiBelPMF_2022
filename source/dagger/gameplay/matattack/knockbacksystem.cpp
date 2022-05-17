#include "knockbacksystem.h"
#include "gravitysystem.h"

#include "core/engine.h"
#include "core/game/transforms.h"
#include "core/graphics/sprite.h"

#include "gameplay/common/simple_collisions.h"

void KnockbackSystem::Run()
{
	auto view = Engine::Registry().view<Gravity, Transform, SimpleCollision, KnockbackInfo>();


	auto it = view.begin();

	while (it != view.end()) {
		auto& gravity = view.get<Gravity>(*it);
		auto& transform = view.get<Transform>(*it);
		auto& simple_collision = view.get<SimpleCollision>(*it);
		auto& knockback_info = view.get<KnockbackInfo>(*it);
		if (knockback_info.is_knocked)
		{
			if (knockback_info.horizontal_speed == 0)
			{
				gravity.speed -= knockback_info.base_vertical_speed;
				knockback_info.horizontal_speed = knockback_info.base_horizontal_speed;
				simple_collision.colided = false;
			}
			transform.position.x -= knockback_info.horizontal_speed * knockback_info.direction * Engine::DeltaTime();
			knockback_info.horizontal_speed -= knockback_info.horizontal_decrease;
			if (gravity.speed == 0 || knockback_info.horizontal_speed <= 0)
			{
				knockback_info.is_knocked = false;
				knockback_info.horizontal_speed = 0.0f;
			}
		}
		it++;

	}
}
