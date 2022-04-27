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

void LevelSystem::SpawnTier1Enemies()
{
    if (flag)
    {
        auto transform = Engine::Registry().get<Transform>(mandarian);
        
        for (UInt8 i = 0; i < 10u; i++) 
        {
            Float32 xDirection = rand() / static_cast<Float32>(RAND_MAX);
            Float32 yDirection = rand() / static_cast<Float32>(RAND_MAX);

            Vector2 direction { xDirection, yDirection };
            direction = NORMALIZE(direction);

            int xsign = rand() % 2 == 0 ? 1 : -1;
            int ysign = rand() % 2 == 0 ? 1 : -1;

            direction.x *= xsign;
            direction.y *= ysign;

            Float32 distance = rand() % 100 + 300.0f;
            direction *= distance;

            Enemy::Create(
                1u, 
                { transform.position.x + direction.x, transform.position.y + direction.y },
                { 1.5f, 1.5f }
            );
        }

        flag = false;
    }
}

void LevelSystem::SpawnTier2Enemies()
{
    if (flag)
    {
        auto transform = Engine::Registry().get<Transform>(mandarian);

        auto n = 30;
        Float32 distance = 200.0f;
        Float32 twoPI = 2 * M_PIf32;
        Float32 step = twoPI / n;

        for (Float32 angle = 0.0f; angle < twoPI; angle += step)
        {
            Vector2 offset { distance * cos(angle), distance * sin(angle) };

            Enemy::Create(
                2u, 
                { transform.position.x + offset.x, transform.position.y + offset.y },
                { 2.0f, 2.0f }
            );         
        }

        flag = false;
    }
}

void LevelSystem::SpawnTier3Enemies()
{
    if (flag)
    {
        auto transform = Engine::Registry().get<Transform>(mandarian);

        Float32 xDirection = rand() / static_cast<Float32>(RAND_MAX);
        Float32 yDirection = rand() / static_cast<Float32>(RAND_MAX);

        Vector2 direction{xDirection, yDirection};
        direction = NORMALIZE(direction);

        int xsign = rand() % 2 == 0 ? 1 : -1;
        int ysign = rand() % 2 == 0 ? 1 : -1;

        direction.x *= xsign;
        direction.y *= ysign;

        Float32 distance = rand() % 100 + 300.0f;
        direction *= distance;

        Vector2 position { transform.position.x + direction.x, transform.position.y + direction.y };

        for (UInt8 i = 0u; i < 20u; i++) 
        {
            Float32 xOffset = rand() / static_cast<Float32>(RAND_MAX);
            Float32 yOffset = rand() / static_cast<Float32>(RAND_MAX);

            xOffset *= 10.0f;
            yOffset *= 10.0f;

            Enemy::Create(
                3u,
                { position.x + xOffset, position.y + yOffset },
                { 1.5f, 1.5f }
            );         
        }

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

    if (timer.minutes == 0u && timer.seconds % 5u == 0u)
    {
        SpawnTier1Enemies();
    }  
    else if (timer.minutes == 0u && timer.seconds > 20 && timer.seconds % 7u == 0u)
    {
        SpawnTier2Enemies();
    }
    else if (timer.minutes == 0u && timer.seconds > 50 && timer.seconds % 13u == 0u)
    {
        SpawnTier3Enemies();   
    }
    else
    {
        flag = true;
    }
}