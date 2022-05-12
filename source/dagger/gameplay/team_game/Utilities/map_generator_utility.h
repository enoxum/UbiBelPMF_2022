#pragma once

#include "core/core.h"
#include "core/engine.h"
#include "core/audio.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"
#include "core/game/transforms.h"

#include "gameplay/common/simple_collisions.h"
#include "gameplay/team_game/player_controller.h"
#include "gameplay/team_game/item_collection.h"
#include "gameplay/team_game/solid_object_interaction.h"
#include "gameplay/team_game/gravity.h"
#include "gameplay/team_game/Utilities/string_utility.h"
#include "gameplay/team_game/Utilities/map_generator_utility.h"

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"


using namespace dagger;

namespace team_game
{

    void assignSprite(Sprite &sprite, const std::string type, const int width, const int height);
    void assignEntity(Entity entity, entt::registry& reg, std::string type, std::string id);
    void initMap(double zPos, std::string filename); 
    void initPlayer(double zPos);

}