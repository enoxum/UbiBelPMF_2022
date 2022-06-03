#include "player_controller.h"

#include "core/game/transforms.h"
#include "gameplay/team_game/team_game_main.h"
#include "gameplay/team_game/timer.h"
#include <core/graphics/animation.h>


using namespace dagger;
using namespace team_game;


void PlayerControlSystem::SpinUp()
{
    Engine::Dispatcher().sink<KeyboardEvent>().connect<&PlayerControlSystem::OnKeyboardEvent>(this);
    Engine::Dispatcher().sink<NextFrame>().connect<&PlayerControlSystem::OnEndOfFrame>(this);
}

void PlayerControlSystem::WindDown()
{
    Engine::Dispatcher().sink<KeyboardEvent>().disconnect<&PlayerControlSystem::OnKeyboardEvent>(this);
    Engine::Dispatcher().sink<NextFrame>().disconnect<&PlayerControlSystem::OnEndOfFrame>(this);
}

void PlayerControlSystem::OnKeyboardEvent(KeyboardEvent kEvent_)
{
    auto& reg = Engine::Registry();
    auto ents = reg.view<Player, Transform, Sprite, Animator>();


    for (const auto ent : ents)
    {
        auto& player = ents.get<Player>(ent);
        auto& pos = ents.get<Transform>(ent);
        auto& sprite = ents.get<Sprite>(ent);
        auto& anim = ents.get<Animator>(ent);

        if (kEvent_.key == EDaggerKeyboard::KeyLeft && (kEvent_.action == EDaggerInputState::Pressed || kEvent_.action == EDaggerInputState::Held)) {
            step = -0.7;
            sprite.scale.x = -1;

        }
        else if (kEvent_.key == EDaggerKeyboard::KeyLeft && kEvent_.action == EDaggerInputState::Released) {
            step = 0.0;
            
        }
        else if (kEvent_.key == EDaggerKeyboard::KeyRight && (kEvent_.action == EDaggerInputState::Pressed || kEvent_.action == EDaggerInputState::Held)) {
            step = 0.7;
            sprite.scale.x = 1;

        }
        else if (kEvent_.key == EDaggerKeyboard::KeyRight && kEvent_.action == EDaggerInputState::Released) {
            step = 0.0;
        }
        else if (!player.jumping && kEvent_.key == EDaggerKeyboard::KeyUp && (kEvent_.action == EDaggerInputState::Pressed || kEvent_.action == EDaggerInputState::Held)) {
            player.jumping = true;
            jumpVelocity = 5.5f;
            pos.position.y += jumpVelocity;
        }

    }
}


void PlayerControlSystem::Run() {

    auto& engine = Engine::Instance();
    auto& reg = Engine::Registry();
    auto ents = reg.view<Transform, Player>();

    ents.each([this](Transform& ent, Player player) {
        if (ent.position.x > 1600 || ent.position.x < -1600 || ent.position.y > 1200 || ent.position.y < -1200) {
            m_restart = true;
         }

        ent.position.x += step * Engine::DeltaTime() * 300;

        if (player.jumping) {
            ent.position.y += jumpVelocity * Engine::DeltaTime() * 300;
            
            jumpVelocity -= 0.04 * Engine::DeltaTime() * 300;

            if (jumpVelocity <= 0.0)
            {
                player.jumping = false;
                jumpVelocity = 0;           
            }
            
        }
    });

}

void PlayerControlSystem::OnEndOfFrame()
{
    if (m_restart)
    {
        auto& engine = Engine::Instance();
        auto& reg = Engine::Registry();
        auto ents = reg.view<Sprite, MainMenu_, Text>();

        
        m_restart = false;
        

        for (const auto ent : ents) {
            auto& mm = ents.get<MainMenu_>(ent);
            mm.died = true;
        }
    }
}
