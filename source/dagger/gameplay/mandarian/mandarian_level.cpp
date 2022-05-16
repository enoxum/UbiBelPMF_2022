#include "mandarian_level.h"

#include <imgui/imgui.h>

#include "core/game/transforms.h"
#include "mandarian_enemy.h"
#include "mandarian_controller.h"

using namespace mandarian;

Mandarin Mandarin::Get(Entity entity)
{
    auto &reg = Engine::Registry();
    
    auto &sprite = reg.get_or_emplace<Sprite>(entity);
    auto &transform = reg.get_or_emplace<Transform>(entity);
    auto &experience = reg.get_or_emplace<Experience>(entity);

    return Mandarin { entity, sprite, transform, experience };
}

Mandarin Mandarin::Create(UInt16 points_, Vector2 position_, Vector2 scale_)
{
    auto entity = Engine::Registry().create();
    auto mandarin = Mandarin::Get(entity);

    AssignSprite(mandarin.sprite, "mandarian:tangerin");
    mandarin.sprite.scale = { scale_ };

    mandarin.transform.position = { position_, 0.0f };

    mandarin.experience.points = points_;

    return mandarin;
}

UInt16 LevelSystem::CalculateMaxExp(UInt16 level)
{
    return level * 10u + 50u;
}

void LevelSystem::Mutate(CharacterStats &mandarianStats)
{
    Float32 randomFactor = rand() / static_cast<Float32>(RAND_MAX);

    if (randomFactor < 0.1)
    {
        mandarianStats.recovery += 5.0f;
    }
    else if (randomFactor < 0.2)
    {
        mandarianStats.armor += 5.0f;
    }
    else if (randomFactor < 0.3)
    {
        mandarianStats.might *= 1.2;
    }
    else if (randomFactor < 0.4)
    {
        mandarianStats.area *= 1.2;
    }
    else if (randomFactor < 0.5)
    {
        mandarianStats.speed *= 1.3;
    }
    else if (randomFactor < 0.6)
    {
        mandarianStats.duration *= 1.3;
    }
    else if (randomFactor < 0.7)
    {
        mandarianStats.cooldown *= 1.2;
    }
    else if (randomFactor < 0.8)
    {
        mandarianStats.growth *= 1.2;
    }
    else if (randomFactor < 0.9)
    {
        mandarianStats.danger -= 0.1f;    
    } 
    else
    {
        mandarianStats.magnet += 10.0f;
    }
}

void LevelSystem::RenderGUI()
{
    const auto mandarianStats = Engine::Registry().get<CharacterStats>(mandarian);
    const auto mandarianExperience = Engine::Registry().get<CharacterExperience>(mandarian);
    const auto mandarianHealth = Engine::Registry().get<CharacterHealth>(mandarian);

    ImGui::SetNextWindowSize(ImVec2(200, 60), ImGuiCond_FirstUseEver);
    ImGui::Begin("Status");
    ImGui::Separator();

    ImGui::Text("Timer: %02d:%02d", timer.minutes, timer.seconds);

    ImGui::Separator();

    ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "Mandarian Experience:");
    ImGui::Text("Level%d: %dEXP", mandarianExperience.level, mandarianExperience.points);
    ImGui::ProgressBar(mandarianExperience.points / (Float32) CalculateMaxExp(mandarianExperience.level));
    ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "Mandarian Health:");
    ImGui::Text("Health: %.2fHP", mandarianHealth.points);
    ImGui::ProgressBar(mandarianHealth.points / mandarianStats.maxHealth);

    ImGui::Separator();

    ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "Mandarian Stats:");
    ImGui::Text("Max Health: %.2fHP",       mandarianStats.maxHealth);
    ImGui::Text("Recovery:   %.2fHP/Level", mandarianStats.recovery);
    ImGui::Text("Armor:      %.2f",         mandarianStats.armor);
    ImGui::Text("Might:      %.0f%%", 100 * mandarianStats.might);
    ImGui::Text("Area:       %.0f%%", 100 * mandarianStats.area);
    ImGui::Text("Speed:      %.0f%%", 100 * mandarianStats.speed);
    ImGui::Text("Duration:   %.0f%%", 100 * mandarianStats.duration);
    ImGui::Text("Cooldown:   %.0f%%", 100 * mandarianStats.cooldown);
    ImGui::Text("Growth:     %.0f%%", 100 * mandarianStats.growth);
    ImGui::Text("Danger:     %.2f",         mandarianStats.danger);
    ImGui::Text("Magnet:     %.2f",         mandarianStats.magnet);

    ImGui::Separator();
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

void LevelSystem::SpawnTier1Enemies(unsigned numberOfEnemies)
{
    if (flag)
    {
        auto transform = Engine::Registry().get<Transform>(mandarian);
        
        for (UInt8 i = 0; i < numberOfEnemies; i++) 
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

        for (Float32 angle = 0.0f; angle < twoPI - step; angle += step)
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

void LevelSystem::SpawnTier3Enemies(unsigned numberOfEnemies)
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

        for (UInt8 i = 0u; i < numberOfEnemies; i++) 
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

void LevelSystem::UpdateExperience()
{
    auto &registry = Engine::Registry();

    const auto mandarianTransform = registry.get<Transform>(mandarian);
    auto &mandarianStats = registry.get<CharacterStats>(mandarian);
    auto &mandarianExperience = registry.get<CharacterExperience>(mandarian);
    auto &mandarianHealth = registry.get<CharacterHealth>(mandarian);

    registry.view<Transform, Experience>().each(
        [&](auto entity, auto &transform, auto &experience) 
        {
            const auto distance = glm::distance(transform.position, mandarianTransform.position);
            
            if (distance < mandarianStats.magnet) 
            {
                mandarianExperience.points += mandarianStats.growth * experience.points;            
                if (CalculateMaxExp(mandarianExperience.level) <= mandarianExperience.points)
                {
                    mandarianExperience.points = 0u;
                    mandarianExperience.level++;
                    
                    mandarianStats.maxHealth += 2u;
                   
                    mandarianHealth.points += mandarianStats.recovery;
                    if (mandarianHealth.points > mandarianStats.maxHealth) {
                        mandarianHealth.points = mandarianStats.maxHealth;
                    }

                    Mutate(mandarianStats);
                }
            
                registry.destroy(entity);
            }
        }
    );
}

void LevelSystem::SpawnEnemies()
{
    const auto mandarianStats = Engine::Registry().get<CharacterStats>(mandarian);
    const auto mandarianExperience = Engine::Registry().get<CharacterExperience>(mandarian);
    const auto mandarianHealth = Engine::Registry().get<CharacterHealth>(mandarian);
    if (timer.seconds % 5u == 0u)
    {
        unsigned numOfEnemies = timer.minutes == 0u ? 10u : 20u;
        SpawnTier1Enemies(numOfEnemies);
    }
    else if (timer.seconds > 20 && timer.seconds % 7u == 0u)
    {
        SpawnTier2Enemies();
    }
    else if (timer.seconds > 50 && timer.seconds % 13u == 0u)
    {
        unsigned numOfEnemies = timer.minutes == 0u ? 20u : 50u;
        SpawnTier3Enemies(numOfEnemies);
    } 
    else if (timer.seconds > 80 && timer.seconds % 17u == 0u) 
    { 
        SpawnTier1Enemies(50u);
        // SpawnTier4Enemies();
    } 
    else if (timer.seconds > 90 && timer.seconds % 19u == 0u) 
    {
        SpawnTier3Enemies(100u); 
        // SpawnTier5Enemies();
    }
    else
    {
        flag = true;
    }
}

void LevelSystem::Run()
{
    UpdateTimer();
    UpdateExperience();
    SpawnEnemies();
}