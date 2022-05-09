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
    //Engine::Dispatcher().sink<KeyboardEvent>().connect<&LevelChangeSystem::OnKey>(this);
    Engine::Dispatcher().sink<KeyboardEvent>().connect<&LevelChangeSystem::CharacterSelect>(this);
    Engine::Dispatcher().sink<MouseEvent>().connect<&LevelChangeSystem::LevelSelect>(this);
}

void LevelChangeSystem::WindDown()
{
    Engine::Dispatcher().sink<LevelChangeEvent>().disconnect<&LevelChangeSystem::LevelChooser>(this);
}

void LevelChangeSystem::LevelChooser(LevelChangeEvent lce)
{
    int lvl = std::rand() % 3 + 1;
    matattack::SetupWorld(lvl, "matattack:characters:fox:idle:idle1", "matattack:characters:fox:idle:idle1", "matattack:idle:fox", "matattack:idle:fox");
}

void LevelChangeSystem::OnKey(KeyboardEvent ke) 
{
    if (ke.key == EDaggerKeyboard::KeyEnter && ke.action == EDaggerInputState::Pressed && !LevelChangeSystem::isStarted)
    {
        LevelChangeSystem::isStarted = true;
        int lvl = std::rand() % 3 + 1;
        matattack::SetupWorld(lvl, "matattack:characters:fox:idle:idle1", "matattack:characters:fox:idle:idle1", "matattack:idle:fox", "matattack:idle:fox");
    }
    Logger::critical(ke.key);
}

//void LevelChangeSystem::CharacterSelect(MouseEvent me)
//{
//    ImVec2 ce = ImGui::GetMousePos();
//
//    if (me.action == EDaggerInputState::Pressed && me.button == EDaggerMouse::MouseButton1)
//    {
//        if (ce.x >= 504 && ce.x <= 695 && ce.y <= 609 && ce.y >= 442)
//        {
//            fstCharSprite = "matattack:characters:fox:idle:idle1";
//        }
//        if (ce.x >= 744 && ce.x <= 935 && ce.y <= 609 && ce.y >= 442)
//        {
//            fstCharSprite = "matattack:characters:fox:idle:idle1";
//        }
//        if (ce.x >= 982 && ce.x <= 1173 && ce.y <= 609 && ce.y >= 442)
//        {
//            fstCharSprite = "matattack:characters:fox:idle:idle1";
//        }
//        if (ce.x >= 1223 && ce.x <= 1414 && ce.y <= 609 && ce.y >= 442)
//        {
//            fstCharSprite = "matattack:characters:fox:idle:idle1";
//        }
//    }
//    else if (me.action == EDaggerInputState::Pressed && me.button == EDaggerMouse::MouseButton2)
//    {
//        if (ce.x >= 504 && ce.x <= 695 && ce.y <= 609 && ce.y >= 442)
//        {
//            sndCharSprite = "matattack:characters:fox:idle:idle1";
//        }
//        if (ce.x >= 744 && ce.x <= 935 && ce.y <= 609 && ce.y >= 442)
//        {
//            sndCharSprite = "matattack:characters:fox:idle:idle1";
//        }
//        if (ce.x >= 982 && ce.x <= 1173 && ce.y <= 609 && ce.y >= 442)
//        {
//            sndCharSprite = "matattack:characters:fox:idle:idle1";
//        }
//        if (ce.x >= 1223 && ce.x <= 1414 && ce.y <= 609 && ce.y >= 442)
//        {
//            sndCharSprite = "matattack:characters:fox:idle:idle1";
//        }
//    }
//
//    Logger::critical(ce.x);
//    Logger::critical(ce.y);
//}

void LevelChangeSystem::CharacterSelect(KeyboardEvent ke)
{
    auto& engine = Engine::Instance();
    auto& reg = engine.Registry();

    if (!isOnMouse)
    {

        if (ke.action == EDaggerInputState::Pressed && ke.key == EDaggerKeyboard::KeyLeft)
        {
            index--;
            if (index < 0)
                index = 3;

            //auto view = Engine::Registry().view<matattack::ArrowInfo>();

            //auto it = view.begin();
            //while (it != view.end())
            //{
            //    // data of the first entity
            //    auto& arrow = view.get<matattack::ArrowInfo>(*it);
            //    arrow.arrowSprite.position = { arrow.arrowSprite.position.x - 50, -75, 0 };
            //    arrow.arrowTransform.position = arrow.arrowSprite.position;
            //    it++;
            //}

        }

        if (ke.action == EDaggerInputState::Pressed && ke.key == EDaggerKeyboard::KeyRight)
        {
            index = (index + 1) % 4;

            //auto view = Engine::Registry().view<matattack::ArrowInfo>();

            //auto it = view.begin();
            //while (it != view.end())
            //{
            //    // data of the first entity
            //    auto& arrow = view.get<matattack::ArrowInfo>(*it);
            //    arrow.arrowSprite.position = { arrow.arrowSprite.position.x + 50, -75, 0 };
            //    arrow.arrowTransform.position = arrow.arrowSprite.position;
            //    it++;
            //}
        }

        if (ke.action == EDaggerInputState::Pressed && ke.key == EDaggerKeyboard::KeyEnter)
        {
            if (countEnter == 0)
            {
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

void LevelChangeSystem::LevelSelect(MouseEvent me)
{
    //auto& reg = Engine::Registry();
    //reg.clear();

    if (isOnMouse) 
    {
        ImVec2 ce = ImGui::GetMousePos();
        if (me.action == EDaggerInputState::Pressed && me.button == EDaggerMouse::MouseButton1 && !LevelChangeSystem::isStarted)
        {
            if (ce.x >= 269 && ce.x <= 690 && ce.y <= 547 && ce.y >= 328)
            {
                LevelChangeSystem::isStarted = true;
                matattack::SetupWorld(1, fstCharSprite, sndCharSprite, fstCharAnimation, sndCharAnimation);
            }
            if (ce.x >= 751 && ce.x <= 1169 && ce.y <= 547 && ce.y >= 328)
            {
                LevelChangeSystem::isStarted = true;
                matattack::SetupWorld(2, fstCharSprite, sndCharSprite, fstCharAnimation, sndCharAnimation);
            }
            if (ce.x >= 1230 && ce.x <= 1649 && ce.y <= 547 && ce.y >= 328)
            {
                LevelChangeSystem::isStarted = true;
                matattack::SetupWorld(3, fstCharSprite, sndCharSprite, fstCharAnimation, sndCharAnimation);
            }
        }
        Logger::critical(ce.x);
        Logger::critical(ce.y);
    }
}