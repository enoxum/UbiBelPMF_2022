#include "mandarian_controller.h"

#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"

using namespace mandarian;

void MandarianControllerSystem::Run()
{
    Engine::Registry().view<MandarianControllerFSM::StateComponent>()
        .each([&](MandarianControllerFSM::StateComponent& state_)
            {
                mandarianFSM.Run(state_);
            });
}