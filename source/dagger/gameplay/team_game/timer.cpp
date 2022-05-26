#include "timer.h"
#include <core/graphics/text.h>

void team_game::TimerSystem::Run()
{
	

    auto& reg = Engine::Registry();
    auto ents = reg.view<Time, Text>();

    for (const auto ent : ents) {
        
        auto& text = ents.get<Text>(ent);
        auto& time = ents.get<Time>(ent);
        time.seconds += Engine::DeltaTime();
        String msg = std::to_string((int)time.seconds) + ":" + std::to_string((int)(time.seconds * 100) % 100);
        text.Set("pixel-font", msg, { 350, 250 ,0 });
    }

    ents.each([this](const Time, Text& text) {
        
    });

}

void team_game::TimerSystem::SpinUp()
{
}

void team_game::TimerSystem::WindDown()
{
}
