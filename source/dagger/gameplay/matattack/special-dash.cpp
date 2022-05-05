#include "special-dash.h"
#include "specialabilitysystem.h"
#include "matattack.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"
#include "core/game/transforms.h"

using namespace matattack;

void Dash::Run(const Entity& character)
{
	auto&& [character_info, special_info] = Engine::Registry().get<CharacterInfo,SpecialInfo>(character);
	Logger::critical(character_info.speed);
	Logger::critical("Dash");
}
