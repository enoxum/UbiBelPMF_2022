#include "player_controller.h"

#include "core/game/transforms.h"


using namespace dagger;
using namespace team_game;


void PlayerControlSystem::SpinUp()
{
    Engine::Dispatcher().sink<KeyboardEvent>().connect<&PlayerControlSystem::OnKeyboardEvent>(this);
}

void PlayerControlSystem::WindDown()
{
    Engine::Dispatcher().sink<KeyboardEvent>().disconnect<&PlayerControlSystem::OnKeyboardEvent>(this);
}

void PlayerControlSystem::OnKeyboardEvent(KeyboardEvent kEvent_)
{
    auto& reg = Engine::Registry();
    auto ents = reg.view<Player, Transform>();


    for (const auto ent : ents)
    {
        auto& player = ents.get<Player>(ent);
        auto& pos = ents.get<Transform>(ent);

        if (kEvent_.key == EDaggerKeyboard::KeyLeft && (kEvent_.action == EDaggerInputState::Pressed || kEvent_.action == EDaggerInputState::Held)) {
            step = -0.7;
        }
        else if (kEvent_.key == EDaggerKeyboard::KeyLeft && kEvent_.action == EDaggerInputState::Released) {
            step = 0.0;
        }
        else if (kEvent_.key == EDaggerKeyboard::KeyRight && (kEvent_.action == EDaggerInputState::Pressed || kEvent_.action == EDaggerInputState::Held)) {
            step = 0.7;
        }
        else if (kEvent_.key == EDaggerKeyboard::KeyRight && kEvent_.action == EDaggerInputState::Released) {
            step = 0.0;
        }
        else if (!player.jumping && kEvent_.key == EDaggerKeyboard::KeyUp && (kEvent_.action == EDaggerInputState::Pressed || kEvent_.action == EDaggerInputState::Held)) {
            player.jumping = true;
            jumpVelocity = 3.5f;
            pos.position.y += jumpVelocity;
        }

    }
}


void PlayerControlSystem::Run() {

    auto& reg = Engine::Registry();
    auto ents = reg.view<Transform, Player>();

    ents.each([this](Transform& ent, Player player) {

        ent.position.x += step;

        if (player.jumping) {
            ent.position.y += jumpVelocity;
            jumpVelocity -= 0.05f;
            if (jumpVelocity <= 0.1)
            {
                player.jumping = false;
                jumpVelocity = 0;           
            }
            
        }
    });

}
