#include "mandarian_spell_system.h"
#include "mandarian_controller.h"
#include "mandarian_damage_system.h"

#include "core/engine.h"

using namespace dagger;
using namespace mandarian;

AuraOfMandarian AuraOfMandarian::Get(Entity entity)
{
    auto &reg = Engine::Registry();
    auto &aura = reg.get_or_emplace<Aura>(entity);
    auto &sprite = reg.get_or_emplace<Sprite>(entity);
    auto &transform = reg.get_or_emplace<Transform>(entity);

    return AuraOfMandarian{ entity, aura, sprite, transform };
};

AuraOfMandarian AuraOfMandarian::Create(Float32 cooldown_, Float32 damage_, Float32 radius_, Bool global_)
{
    auto &reg = Engine::Registry();
    auto entity = reg.create();
    reg.emplace<SpellTag>(entity);
    auto auraOfMandarian = AuraOfMandarian::Get(entity);

    auraOfMandarian.aura.cooldown = cooldown_;
    auraOfMandarian.aura.damage = damage_;
    auraOfMandarian.aura.global = global_;
    auraOfMandarian.aura.radius = radius_;
    
    auto player_ent = reg.view<Player>()[0];
    auto player = Character::Get(player_ent);
    
    auraOfMandarian.transform.position = player.transform.position;

    return auraOfMandarian;
};

void MandarianSpellSystem::CastAuraOfMandarian()
{
    auto spell = AuraOfMandarian::Create();
    Damaging::Create(spell.aura.damage, spell.aura.radius, spell.transform.position, false);
    Engine::Registry().destroy(spell.entity);
}

void MandarianSpellSystem::Run()
{
    CastAuraOfMandarian();
}