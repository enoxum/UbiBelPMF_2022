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
    //auto& reg = Engine::Registry();
    //auto entities = reg.view<Sprite>();
    //reg.destroy(entities.begin(), entities.end());
    //reg.clear();
    matattack::SetupWorld();
}

void LevelChangeSystem::OnKey(KeyboardEvent ke) 
{
    Logger::critical(ke.key);
}



