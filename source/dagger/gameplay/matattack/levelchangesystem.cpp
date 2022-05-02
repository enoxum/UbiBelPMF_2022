#include "LevelChangeSystem.h"
#include "core/engine.h"
#include "gameplay/matattack/matattack.h"
#include "core/graphics/sprite.h"
#include "core/input/inputs.h"
#include "imgui.h"

using namespace dagger;

void LevelChangeSystem::SpinUp()
{
    Engine::Dispatcher().sink<LevelChangeEvent>().connect<&LevelChangeSystem::LevelChooser>(this);
    Engine::Dispatcher().sink<KeyboardEvent>().connect<&LevelChangeSystem::OnKey>(this);
    Engine::Dispatcher().sink<MouseEvent>().connect<&LevelChangeSystem::OnMouse>(this);
}

void LevelChangeSystem::WindDown()
{
    Engine::Dispatcher().sink<LevelChangeEvent>().disconnect<&LevelChangeSystem::LevelChooser>(this);
}

void LevelChangeSystem::LevelChooser(LevelChangeEvent lce)
{
    int lvl = std::rand() % 3 + 1;
    matattack::SetupWorld(lvl);
}

void LevelChangeSystem::OnKey(KeyboardEvent ke) 
{
    if (ke.key == EDaggerKeyboard::KeyEnter && ke.action == EDaggerInputState::Pressed && !LevelChangeSystem::isStarted)
    {
        LevelChangeSystem::isStarted = true;
        int lvl = std::rand() % 3 + 1;
        matattack::SetupWorld(lvl);
    }
    Logger::critical(ke.key);
}

void LevelChangeSystem::OnMouse(MouseEvent me)
{
    ImVec2 ce = ImGui::GetMousePos();
    if (me.action == EDaggerInputState::Pressed && me.button == EDaggerMouse::MouseButton1 && !LevelChangeSystem::isStarted)
    {
        if (ce.x >= 269 && ce.x <= 690 && ce.y <= 547 && ce.y >= 328)
        {
            LevelChangeSystem::isStarted = true;
            matattack::SetupWorld(1);
        }
        if (ce.x >= 751 && ce.x <= 1169 && ce.y <= 547 && ce.y >= 328)
        {
            LevelChangeSystem::isStarted = true;
            matattack::SetupWorld(2);
        }
        if (ce.x >= 1230 && ce.x <= 1649 && ce.y <= 547 && ce.y >= 328)
        {
            LevelChangeSystem::isStarted = true;
            matattack::SetupWorld(3);
        }
    }
    Logger::critical(ce.x);
    Logger::critical(ce.y);

}