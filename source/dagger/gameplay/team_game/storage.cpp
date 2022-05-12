#include "storage.h"
#include <core/graphics/sprite.h>
#include "item_collection.h"
#include <core/graphics/window.h>


void team_game::StorageSystem::Run()
{

    auto& reg = Engine::Registry();
    auto ents = reg.view<Sprite, const CollectedItem>();

    int offset = 0;

    for (const auto ent : ents)
    {
        Sprite& sprite = ents.get<Sprite>(ent);
        sprite.UseAsUI();
        sprite.position = { - screenSize.x / 2 * 0.9 + offset * 0.1 * screenSize.x, - screenSize.y / 2 * 0.9, 0 };
        float ratio = sprite.size.y / sprite.size.x;
        sprite.size = { 25 / ratio, 25};
        offset++;
    }
}

void team_game::StorageSystem::SpinUp()
{
    auto* camera = Engine::GetDefaultResource<Camera>();
    screenSize = camera->size;
}

void team_game::StorageSystem::WindDown()
{
}
