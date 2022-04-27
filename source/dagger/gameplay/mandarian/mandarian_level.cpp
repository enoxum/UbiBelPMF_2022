#include "mandarian_level.h"

#include <imgui/imgui.h>

#include "core/game/transforms.h"
#include "mandarian_enemy.h"

using namespace mandarian;

void LevelSystem::RenderGUI()
{
    ImGui::SetNextWindowSize(ImVec2(200, 60), ImGuiCond_FirstUseEver);
    ImGui::Begin("Status");
    ImGui::Separator();
    ImGui::Text("Timer: %02d:%02d", timer.minutes, timer.seconds);
    ImGui::End();
}

void LevelSystem::UpdateTimer()
{
    auto diff = TimeSnapshot() - startTime;
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(diff).count();
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(diff).count();

    timer.minutes = (UInt8) minutes;
    timer.seconds = (UInt8) (seconds % 60);
}

void LevelSystem::SpawnEnemies()
{
    if (flag) 
    {
        auto transform = Engine::Registry().get<Transform>(mandarian);

        Enemy::Create({ transform.position.x - 100.0f, transform.position.y - 100.0f });
        Enemy::Create({ transform.position.x + 100.0f, transform.position.y - 100.0f });
        Enemy::Create({ transform.position.x - 100.0f, transform.position.y + 100.0f });
        Enemy::Create({ transform.position.x + 100.0f, transform.position.y + 100.0f });
        
        flag = false;
    }
}

void LevelSystem::SpinUp()
{
    Engine::Dispatcher().sink<GUIRender>().connect<&LevelSystem::RenderGUI>(this);
}

void LevelSystem::WindDown()
{
    Engine::Dispatcher().sink<GUIRender>().disconnect<&LevelSystem::RenderGUI>(this);
}

void LevelSystem::Run()
{
    UpdateTimer();

    if (timer.seconds % 5u == 0u)
    {
        SpawnEnemies();
    }  
    else 
    {
        flag = true;
    }
}