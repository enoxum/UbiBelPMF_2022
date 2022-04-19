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
		auto& sprite = view.get<Sprite>(*it);
		auto& simple_collision = view.get<SimpleCollision>(*it);


		simple_collision.pos.y = transform.position.y;
		transform.position.y -= gravity.weight * Engine::DeltaTime();
		sprite.position.y = transform.position.y;

		//Logger::trace("treci deo");

		it++;
	
	}
}
