#include "jumpsystem.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"

using namespace matattack;

void JumpSystem::Run()
{
    Engine::Registry().view<FSMCharacterJump::StateComponent>()
        .each([&](FSMCharacterJump::StateComponent& state_)
            {
                jumpFSM.Run(state_);
            });
}