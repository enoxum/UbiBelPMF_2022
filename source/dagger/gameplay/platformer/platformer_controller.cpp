#include "platformer_controller.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"

using namespace platformer;

void PlatformerControllerSystem::Run()
{
    Engine::Registry().view<CharacterControllerFSM::StateComponent>()
        .each([&](CharacterControllerFSM::StateComponent& state_)
            {
                characterFSM.Run(state_);
            });
}
