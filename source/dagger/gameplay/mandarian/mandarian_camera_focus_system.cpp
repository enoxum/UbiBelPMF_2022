#include "mandarian_camera_focus_system.h"
#include "mandarian_controller.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/graphics/sprite.h"
#include "core/graphics/window.h"

#include <iostream>

using namespace dagger;
using namespace mandarian;

void MandarianCameraFocusSystem::Run()
{
    auto* camera = Engine::GetDefaultResource<Camera>();
    auto players = Engine::Registry().view<const Player, Transform>();
	for (auto player : players) {
        auto &t = players.get<Transform>(player);
		camera->position = t.position;
	}    
}

