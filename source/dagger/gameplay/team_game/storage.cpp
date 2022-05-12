#include "storage.h"
#include <core/graphics/sprite.h>
#include "item_collection.h"
#include <core/graphics/window.h>


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
        float ratio = sprite.size.y / sprite.size.x;
        sprite.size = { 25 / ratio, 25};

        if (offset == selectedItem - 1) {
            Item i = ents.get<Item>(ent);
            Logger::critical(i.id);
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
