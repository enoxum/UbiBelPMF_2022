#include "timer.h"
#include <core/graphics/text.h>

void team_game::TimerSystem::Run()
{
	seconds += Engine::DeltaTime();

    auto& reg = Engine::Registry();
    auto ents = reg.view<const Time, Text>();

    ents.each([this](const Time, Text& text) {
        String msg = std::to_string((int)seconds) + ":" + std::to_string((int)(seconds * 100) % 100); 
        text.Set("pixel-font", msg, {350, 250 ,0});
    });

}

void team_game::TimerSystem::SpinUp()
{
	seconds = 0.0;
}

void team_game::TimerSystem::WindDown()
{
}
