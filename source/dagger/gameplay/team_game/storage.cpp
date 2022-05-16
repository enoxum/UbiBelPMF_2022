#include "storage.h"
#include <core/graphics/sprite.h>
#include "item_collection.h"
#include <core/graphics/window.h>
#include "player_controller.h"
#include "gameplay/common/simple_collisions.h"
#include "core/game/transforms.h"
#include "obstacle.h"

#include<iostream>
#include <gameplay/team_game/Utilities/string_utility.h>


using namespace team_game;

void StorageSystem::Run()
{
    auto& reg = Engine::Registry();
    auto ents = reg.view<Sprite, const CollectedItem, Item>();

    int offset = 0;

    for (const auto ent : ents)
    {
        Sprite& sprite = ents.get<Sprite>(ent);
        sprite.UseAsUI();
        sprite.position = { - screenSize.x / 2 * 0.9 + offset * 0.1 * screenSize.x, - screenSize.y / 2 * 0.9, 0 };
        //float ratio = sprite.size.y / sprite.size.x;
        //sprite.size = { 40 / ratio, 40};
        sprite.size = { 40 , 40};

       
        if (offset == selectedItem - 1) {
            Item i = ents.get<Item>(ent);
            Logger::critical(i.id);

            auto view = reg.view<Player, Transform, SimpleCollision>();
            auto viewCollisions = reg.view<Obstacle, Transform, SimpleCollision>();

            for (const auto player : view) {

                auto& col = view.get<SimpleCollision>(player);
                if (col.colided && Engine::Registry().valid(col.colidedWith) && viewCollisions.contains(col.colidedWith))
                {
                    auto& obstacle = viewCollisions.get<Obstacle>(col.colidedWith);

                    if (i.id == obstacle.id) {
                       Logger::critical("istiiiii ");

                       Transform& transform = viewCollisions.get<Transform>(col.colidedWith);
                       transform.position = { INFINITY, INFINITY, INFINITY };

                       reg.remove<CollectedItem>(ent);

                       float zPos = 1.f;
                       std::string file = "level_loader_with_obstacles.txt";
                       std::ifstream fin;
                       fin.open(file);

                       if (fin.is_open()) {
                           std::string line;
                           while (std::getline(fin, line)) {
                                std::vector<std::string> parameters = splitLine(line);

                                // if the line is comment line skip it
                                if (parameters[0] == "#" || parameters[0] != i.id)
                                {
                                    continue;
                                }

                                const std::string id = parameters[0];
                                const std::string type = parameters[1];
                                const auto xCoordinate = std::stoi(parameters[2]);
                                const auto yCoordinate = std::stoi(parameters[3]);
                                const auto width = std::stoi(parameters[4]);
                                const auto height = std::stoi(parameters[5]);

                                auto entity = reg.create();
                                auto& sprite = reg.emplace<Sprite>(entity);
                                AssignSprite(sprite, "EscapeRoom:" + type);
                                sprite.size = { width, height };

                                auto& transform = reg.emplace<Transform>(entity);
                                transform.position = { xCoordinate , yCoordinate, zPos };
                            }
                       }
                       fin.close();
                    }
                }
            }

            selectedItem = 0;
        }

        offset++;
    } 

}


void StorageSystem::OnKeyboardEvent(KeyboardEvent kEvent_) {

    if (kEvent_.key >= EDaggerKeyboard::Key1 && kEvent_.key <= EDaggerKeyboard::Key9 && (kEvent_.action == EDaggerInputState::Pressed || kEvent_.action == EDaggerInputState::Held))
    {
        selectedItem = (int)kEvent_.key - 48; // Key code for Key1 is 49
    }

}

void StorageSystem::SpinUp()
{
    Engine::Dispatcher().sink<KeyboardEvent>().connect<&StorageSystem::OnKeyboardEvent>(this);

    auto* camera = Engine::GetDefaultResource<Camera>();
    screenSize = camera->size;
}

void team_game::StorageSystem::WindDown()
{
    Engine::Dispatcher().sink<KeyboardEvent>().disconnect<&StorageSystem::OnKeyboardEvent>(this);

}
