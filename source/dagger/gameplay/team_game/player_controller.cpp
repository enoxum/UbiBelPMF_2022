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
    if (kEvent_.key == EDaggerKeyboard::KeyLeft && (kEvent_.action == EDaggerInputState::Pressed || kEvent_.action == EDaggerInputState::Held)) {
        step = -0.2;
    }
    else if (kEvent_.key == EDaggerKeyboard::KeyLeft && kEvent_.action == EDaggerInputState::Released) {
        step = 0.0;
    }
    else if (kEvent_.key == EDaggerKeyboard::KeyRight && (kEvent_.action == EDaggerInputState::Pressed || kEvent_.action == EDaggerInputState::Held)) {
        step = 0.2;
    }
    else if (kEvent_.key == EDaggerKeyboard::KeyRight && kEvent_.action == EDaggerInputState::Released) {
        step = 0.0;
    }
    else if (!jumping && kEvent_.key == EDaggerKeyboard::KeyUp && (kEvent_.action == EDaggerInputState::Pressed || kEvent_.action == EDaggerInputState::Held)) {
        jumping = true;
        jumpVelocity = 1.5f;
    }
}


void PlayerControlSystem::Run() {

    auto& reg = Engine::Registry();
    auto ents = reg.view<Transform, const Player>();

    ents.each([this](Transform& ent, const Player) {

        ent.position.x += step;

        if (jumping) {
            jumpVelocity -= 0.008f;
            ent.position.y += jumpVelocity;
            if (ent.position.y <= 0) {   // if(standing_on_ground) ...
                jumpVelocity = 0.0;
                jumping = false;
            }
        }
    });

}
