#include "map_generator_utility.h"

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
#include "gameplay/team_game/obstacle.h"

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"

using namespace dagger;

void team_game::assignSprite(Sprite &sprite, const std::string type, const int width, const int height) {
    if (type == "SimpleRockPlatform"){
        AssignSprite(sprite, "platformerRocks:SimpleRockPlatform");
    }
    else if (type == "background") {
        AssignSprite(sprite, "Background:background");
    }
    else {
        AssignSprite(sprite, "EscapeRoom:" + type);
    }
    
    float ratio = sprite.size.y / sprite.size.x;
    sprite.size = { width / ratio, height  };
}


void team_game::assignEntity(Entity entity, entt::registry& reg, std::string type, std::string id) {
    if (type == "CollectedItem"){
        CollectedItem& i = reg.emplace<CollectedItem>(entity);
        i.id = id;
    }

    if (type == "Gravity"){
        reg.emplace<Gravity>(entity);
    }
    
    if (type == "Platform") {
        Platform& i = reg.emplace<Platform>(entity);
        i.id = id;
    }

    if (type == "Item") {
        Item& i = reg.emplace<Item>(entity);
        i.id = id;
    }  

    if (type == "Obstacle") {
        Obstacle& i = reg.emplace<Obstacle>(entity);
        i.id = id;
    }
}

void team_game::initMap(double zPos, std::string file) {
    auto& engine = Engine::Instance();
    auto& reg = engine.Registry();

    std::ifstream fin;
    fin.open(file);

    if (fin.is_open()) {
        
        std::string line;
        while (std::getline (fin, line)) {  

            std::vector<std::string> parameters = splitLine(line);

            // if the line is comment line skip it
            if (parameters[0] == "#")
            {
                continue;
            }
            
            unsigned numberOfParameters = parameters.size();

            const std::string id = parameters[0];
            const std::string type = parameters[1];
            const auto xCoordinate = std::stoi(parameters[2]);
            const auto yCoordinate = std::stoi(parameters[3]);
            const auto width = std::stoi(parameters[4]);
            const auto height = std::stoi(parameters[5]);

            auto entity = reg.create();
            auto& sprite = reg.emplace<Sprite>(entity);
            team_game::assignSprite(sprite, type, width, height);
        
            auto& transform = reg.emplace<Transform>(entity);
            transform.position = { xCoordinate , yCoordinate, zPos };

            auto& col = reg.emplace<SimpleCollision>(entity);
            col.size = sprite.size;
            
            // skip first 6 parameters because we parse them before
            for (unsigned i = 6; i < numberOfParameters; i++)
            {
                team_game::assignEntity(entity, reg, parameters[i], id); 
            }
        }
    }
    
    fin.close();

}

void team_game::initPlayer(double zPos) {
    auto& engine = Engine::Instance();
    auto& reg = engine.Registry();

    auto entity = reg.create();
    auto& sprite = reg.emplace<Sprite>(entity);
    AssignSprite(sprite, "logos:character");
    float ratio = sprite.size.y / sprite.size.x;
    sprite.size = { 150 / ratio, 150  };

    auto& transform = reg.emplace<Transform>(entity);
    transform.position = { 30, 30, zPos };

    auto& col = reg.emplace<SimpleCollision>(entity);
    col.size = sprite.size;

    reg.emplace<Player>(entity);
    reg.emplace<Gravity>(entity);
}
