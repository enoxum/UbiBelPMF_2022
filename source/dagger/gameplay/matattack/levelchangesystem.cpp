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
    Engine::Dispatcher().sink<KeyboardEvent>().connect<&LevelChangeSystem::LevelSelect>(this);
    Engine::Dispatcher().sink<KeyboardEvent>().connect<&LevelChangeSystem::CharacterSelect>(this);
}

void LevelChangeSystem::WindDown()
{
    Engine::Dispatcher().sink<LevelChangeEvent>().disconnect<&LevelChangeSystem::LevelChooser>(this);
    Engine::Dispatcher().sink<KeyboardEvent>().disconnect<&LevelChangeSystem::LevelSelect>(this);
    Engine::Dispatcher().sink<KeyboardEvent>().disconnect<&LevelChangeSystem::CharacterSelect>(this);
}

void LevelChangeSystem::LevelChooser(LevelChangeEvent lce)
{
    int lvl = std::rand() % 3 + 1;
    matattack::SetupWorld(lvl, "matattack:characters:fox:idle:idle1", "matattack:characters:fox:idle:idle1", "matattack:idle:fox", "matattack:idle:fox");
}

void LevelChangeSystem::LevelSelect(KeyboardEvent ke) 
{
    if (isOnMouse && !LevelChangeSystem::isStarted)
    {
        auto view = Engine::Registry().view<ArrowInfo, Transform, Sprite>();
        auto it = view.front();
        auto& arrow_transform = view.get<Transform>(it);
        auto& arrow_sprite = view.get<Sprite>(it);

        if (ke.action == EDaggerInputState::Pressed && ke.key == EDaggerKeyboard::KeyLeft)
        {
            index2--;
            arrow_transform.position.x = arrow_transform.position.x - 200;
            if (index2 < 0)
            {
                index2 = 2;
                arrow_transform.position.x = 200;
            }
        }
        if (ke.action == EDaggerInputState::Pressed && ke.key == EDaggerKeyboard::KeyRight)
        {
            if (index2 == 2)
            {
                arrow_transform.position.x = -200;
            }
            else
            {
                arrow_transform.position.x = arrow_transform.position.x + 200;
            }
            index2 = (index2 + 1) % 3;
        }
        if (ke.action == EDaggerInputState::Pressed && ke.key == EDaggerKeyboard::KeyEnter)
        {
           
                switch (index2)
                {
                case 0:
                    LevelChangeSystem::isStarted = true;
                    matattack::SetupWorld(1, fstCharSprite, sndCharSprite, fstCharAnimation, sndCharAnimation);
                    break;
                case 1:
                    LevelChangeSystem::isStarted = true;
                    matattack::SetupWorld(2, fstCharSprite, sndCharSprite, fstCharAnimation, sndCharAnimation);
                    break;
                case 2:
                    LevelChangeSystem::isStarted = true;
                    matattack::SetupWorld(3, fstCharSprite, sndCharSprite, fstCharAnimation, sndCharAnimation);
                    break;
                default:
                    break;
                }

        }
    }
}

void LevelChangeSystem::CharacterSelect(KeyboardEvent ke)
{
    if (!isOnMouse)
    {
        auto view = Engine::Registry().view<ArrowInfo, Transform, Sprite>();
        auto it = view.front();
        auto& arrow_transform = view.get<Transform>(it);
        auto& arrow_sprite = view.get<Sprite>(it);

        if (ke.action == EDaggerInputState::Pressed && ke.key == EDaggerKeyboard::KeyLeft)
        {
            index--;
            arrow_transform.position.x = arrow_transform.position.x - 100;
            if (index < 0) 
            {
                index = 3;
                arrow_transform.position.x = 150;
            }
            
        }

        if (ke.action == EDaggerInputState::Pressed && ke.key == EDaggerKeyboard::KeyRight)
        {
            if (index == 3)
            {
                arrow_transform.position.x = -150;
            }
            else
            {
                arrow_transform.position.x = arrow_transform.position.x + 100;
            }
            index = (index + 1) % 4;
            
            
        }

        if (ke.action == EDaggerInputState::Pressed && ke.key == EDaggerKeyboard::KeyEnter)
        {
            if (countEnter == 0)
            {
                AssignSprite(arrow_sprite, "matattack:items:arrow2");
                countEnter++;
                switch (index)
                {
                case 0:
                    fstCharSprite = "matattack:characters:fox:idle:idle1"; 
                    fstCharAnimation = "fox";
                    break;
                case 1:
                    fstCharSprite = "matattack:characters:dude_monster:idle:idle1"; 
                    fstCharAnimation = "dude_monster";
                    break;
                case 2:
                    fstCharSprite = "matattack:characters:chickboy:idle:idle1"; 
                    fstCharAnimation = "chickboy";
                    break;
                case 3:
                    fstCharSprite = "matattack:characters:otter:idle:idle1"; 
                    fstCharAnimation = "otter";
                    break;
                default:
                    break;
                }
            }
            else if (countEnter == 1)
            {
                countEnter++;
                switch (index)
                {
                case 0:
                    sndCharSprite = "matattack:characters:fox:idle:idle1"; 
                    sndCharAnimation = "fox";
                    break;
                case 1:
                    sndCharSprite = "matattack:characters:dude_monster:idle:idle1"; 
                    sndCharAnimation = "dude_monster";
                    break;
                case 2:
                    sndCharSprite = "matattack:characters:chickboy:idle:idle1"; 
                    sndCharAnimation = "chickboy";
                    break;
                case 3:
                    sndCharSprite = "matattack:characters:otter:idle:idle1"; 
                    sndCharAnimation = "otter";
                    break;
                default:
                    break;
                }

                isOnMouse = true;
                matattack::SetLevelChooser();
            }
        }
    }


}
