#include "movementsystem.h"

#include "core/engine.h"
#include "core/game/transforms.h"
#include "core/graphics/sprite.h"
#include "core/input/inputs.h"

#include "matattack.h"

void MovementSystem::Run() 
{
    auto view = Engine::Registry().view<InputReceiver, Transform, matattack::CharacterInfo, Sprite>();

    auto it = view.begin();
    while (it != view.end()) {

        auto& input = view.get<InputReceiver>(*it);
        auto& transform = view.get<Transform>(*it);
        auto& char_info = view.get<matattack::CharacterInfo>(*it);
        auto& sprite = view.get<Sprite>(*it);

        Float32 run = input.Get("run");
        // probably will have a special system for jumping, we will see
        // Float32 jump = input.Get("jump");

        if (EPSILON_NOT_ZERO(run)) {
            transform.position.x += char_info.speed * run * Engine::DeltaTime();
            //sprite.position.x = transform.position.x;
        }

        it++;
    }

}


