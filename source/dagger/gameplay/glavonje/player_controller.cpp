#include "player_controller.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"

using namespace glavonje;



void PlayerControllerSystem::Run()
{
    Engine::Registry().view<FSMPlayerController::StateComponent>()
        .each([&](FSMPlayerController::StateComponent& state_)
            {
                playerFSM.Run(state_);
            });
}