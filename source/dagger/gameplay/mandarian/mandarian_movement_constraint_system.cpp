#include "mandarian_movement_constraint_system.h"
#include "mandarian_controller.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/graphics/sprite.h"
#include "core/graphics/window.h"

#include <iostream>

using namespace dagger;
using namespace mandarian;

void MandarianMovementConstraintSystem::Run()
{
    auto players = Engine::Registry().view<const Player, Transform>();
	for (auto player : players) {
        auto &t = players.get<Transform>(player);
		if (t.position.x <= - WIDTH / 2) {
            t.position.x = -WIDTH / 2;
        } else if (t.position.x >= WIDTH / 2) {
            t.position.x = WIDTH / 2;
        } else if (t.position.y <= -HEIGHT / 2) {
            t.position.y = -HEIGHT / 2;
        } else if (t.position.y >= HEIGHT / 2) {
            t.position.y = HEIGHT / 2;
        }
	}

}