#include "LevelChangeSystem.h"
#include "core/engine.h"
#include "gameplay/matattack/matattack.h"
#include "core/graphics/sprite.h"

using namespace dagger;

void LevelChangeSystem::SpinUp()
{
    Engine::Dispatcher().sink<LevelChangeEvent>().connect<&LevelChangeSystem::LevelChooser>(this);
    Engine::Dispatcher().sink<KeyboardEvent>().connect<&LevelChangeSystem::OnKey>(this);
}

void LevelChangeSystem::WindDown()
{
    Engine::Dispatcher().sink<LevelChangeEvent>().disconnect<&LevelChangeSystem::LevelChooser>(this);
}

void LevelChangeSystem::LevelChooser(LevelChangeEvent lce)
{
    auto& reg = Engine::Registry();
    reg.clear();
    matattack::SetupWorld();
}

void LevelChangeSystem::OnKey(KeyboardEvent ke) 
{
    if (ke.key == EDaggerKeyboard::KeyEnter && ke.action == EDaggerInputState::Pressed && !LevelChangeSystem::isStarted)
    {
        auto& reg = Engine::Registry();
        reg.clear();
        LevelChangeSystem::isStarted = true;
        matattack::SetupWorld();
    }
    Logger::critical(ke.key);
}



