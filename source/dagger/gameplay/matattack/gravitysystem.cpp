#include "gravitysystem.h"

#include "core/engine.h"
#include "core/game/transforms.h"
#include "core/graphics/sprite.h"

#include "gameplay/common/simple_collisions.h"

void GravitySystem::Run() 
{
	auto view = Engine::Registry().view<Gravity, Transform, Sprite, SimpleCollision>();


	auto it = view.begin();

	while (it != view.end()) {
		
		//Logger::trace("prvi deo");

		auto& gravity = view.get<Gravity>(*it);
		auto& transform = view.get<Transform>(*it);
		auto& simple_collision = view.get<SimpleCollision>(*it);


		if (!simple_collision.colided) 
		{
			gravity.speed += gravity.increase * Engine::DeltaTime();
			simple_collision.pos.y = transform.position.y;
			transform.position.y -= gravity.speed * Engine::DeltaTime();
		}

		//Logger::trace("treci deo");

		it++;
	
	}
}
