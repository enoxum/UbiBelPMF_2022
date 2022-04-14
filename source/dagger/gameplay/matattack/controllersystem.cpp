
#include "controllersystem.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"

using namespace matattack;

void ControllerSystem::Run()
{
    Engine::Registry().view<FSMCharacterController::StateComponent>()
        .each([&](FSMCharacterController::StateComponent& state_)
            {
                characterFSM.Run(state_);
            });
}