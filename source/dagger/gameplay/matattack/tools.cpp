#include "tools.h"
#if defined(DAGGER_DEBUG)

#include "core/engine.h"
#include "gameplay/matattack/matattack.h"
#include "core/graphics/sprite.h"
#include "levelchangesystem.h"

using namespace dagger;
using namespace matattack;

void Tools::SpinUp()
{
    Engine::Dispatcher().sink<ToolMenuRender>().connect<&Tools::RenderToolMenu>(this);
}

void Tools::WindDown()
{
    Engine::Dispatcher().sink<ToolMenuRender>().disconnect<&Tools::RenderToolMenu>(this);
}

void Tools::RenderToolMenu()
{
    if (ImGui::BeginMenu("Choose level"))
    {
        if (ImGui::MenuItem("Level 1"))
        {
            LevelChangeEvent lce{ 1 };
            dagger::Engine::Dispatcher().trigger<LevelChangeEvent>(lce);
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Level 2"))
        {
            LevelChangeEvent lce{ 2 };
            dagger::Engine::Dispatcher().trigger<LevelChangeEvent>(lce);
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Level 3"))
        {
            LevelChangeEvent lce{ 3 };
            dagger::Engine::Dispatcher().trigger<LevelChangeEvent>(lce);
        }

        ImGui::EndMenu();
    }
}


#endif //defined(DAGGER_DEBUG)