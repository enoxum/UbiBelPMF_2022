#include "tools.h"
#if defined(DAGGER_DEBUG)

#include "core/engine.h"
#include "gameplay/matattack/matattack.h"

using namespace dagger;
using namespace matattack;

void Tools::SpinUp()
{
    Engine::Dispatcher().sink<GUIRender>().connect<&Tools::LevelChooser>(this);
    Engine::Dispatcher().sink<ToolMenuRender>().connect<&Tools::RenderToolMenu>(this);
}

void Tools::WindDown()
{
    Engine::Dispatcher().sink<GUIRender>().disconnect<&Tools::LevelChooser>(this);
    Engine::Dispatcher().sink<ToolMenuRender>().disconnect<&Tools::RenderToolMenu>(this);
}

void Tools::RenderToolMenu()
{
    if (ImGui::BeginMenu("Choose level"))
    {
        if (ImGui::MenuItem("Level 1"))
        {
            dagger::Engine::ToggleSystemsPause(false);
            m_lvl1 = true;
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Level 2"))
        {
            dagger::Engine::ToggleSystemsPause(false);
            m_lvl2 = true;
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Level 3"))
        {
            dagger::Engine::ToggleSystemsPause(false);
            m_lvl3 = true;
        }

        ImGui::EndMenu();
    }
}


void Tools::LevelChooser()
{
    if (m_lvl1)
    {
        m_lvl1 = false;
        
        Engine::Registry().clear();
        matattack::SetupWorld();
      //  matattack::SetMap1(); 
    }
    if (m_lvl2)
    {
        m_lvl2 = false;
        matattack::SetMap2();
    }
    if (m_lvl3)
    {
        m_lvl3 = false;
        matattack::SetMap3();
    }
}

#endif //defined(DAGGER_DEBUG)