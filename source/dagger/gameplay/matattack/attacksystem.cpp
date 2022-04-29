#include "attacksystem.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"


using namespace matattack;

void AttackSystem::Run()
{
    Engine::Registry().view<FSMCharacterAttack::StateComponent>()
        .each([&](FSMCharacterAttack::StateComponent& state_)
            {
                attackFSM.Run(state_);
            });
}
