#include "movementsystem.h"

#include "core/engine.h"
#include "core/game/transforms.h"
#include "core/input/inputs.h"
#include "gameplay/common/simple_collisions.h"

#include "matattack.h"

void MovementSystem::Run() 
{
    auto view = Engine::Registry().view<InputReceiver, Transform, matattack::CharacterInfo, SimpleCollision>();

    auto it = view.begin();
    while (it != view.end()) {

        auto& input = view.get<InputReceiver>(*it);
        auto& transform = view.get<Transform>(*it);
        auto& char_info = view.get<matattack::CharacterInfo>(*it);
        auto& simple_colision = view.get<SimpleCollision>(*it);

        Float32 run = input.Get("run");

        if (EPSILON_NOT_ZERO(run)) {
            simple_colision.pos = transform.position;
            transform.position.x += char_info.speed * run * Engine::DeltaTime();
        }

        it++;
    }

}


