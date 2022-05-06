#include "mandarian_spell_system.h"

#include "core/core.h"
#include "core/engine.h"

#include "mandarian_controller.h"

using namespace dagger;
using namespace mandarian;

void MandarianSpellSystem::Run()
{

    auto spells = Engine::Registry().view<SpellTag>();
	for (auto &spell_entity : spells) 
    {
        ...;
	}   
}