#include "mandarian_spell_system.h"

#include "core/engine.h"
#include "mandarian_enemy.h"

using namespace dagger;
using namespace mandarian;

Spell Spell::Get( Entity entity )
{
    auto &reg = Engine::Registry();

    auto &common = reg.get_or_emplace<CommonSpell>(entity);
    auto &transform = reg.get_or_emplace<Transform>(entity);
    auto &sprite = reg.get_or_emplace<Sprite>(entity);
    auto &animator = reg.get_or_emplace<Animator>(entity);
    
    return Spell { entity, common, transform, sprite, animator };
}

Spell Spell::Create( const String &name
                   , Float32 cooldown
                   , Bool ready
                   , Bool active
                   /*, std::vector<IEffect*> &effects*/ )
{
    auto &reg = Engine::Registry();
    auto entity = reg.create();
    reg.emplace<SpellTag>(entity);
    auto spell = Spell::Get(entity);

    spell.sprite.color = {1.0f, 1.0f, 1.0f, 0.8f};

    AssignSprite(spell.sprite, "aura:CAST:aura1");
    AnimatorPlay(spell.animator, "aura:CAST");
    spell.sprite.scale = {1.0f, 1.0f };

    spell.common.name = name;
    spell.common.ready = ready;
    spell.common.active = active;
    spell.common.cooldown = cooldown;
    spell.common.timer = cooldown;
    spell.common.effects.push_back(new Aura(50, 100.0f));

    return spell;
}


void MandarianSpellSystem::UpdateCooldowns()
{
    Engine::Registry().view<CommonSpell>().each(
        [&](auto &commonSpell)
        {
            commonSpell.timer -= Engine::DeltaTime();

            if (commonSpell.timer <= 0.0f)
            {
                commonSpell.timer = commonSpell.cooldown;
                commonSpell.ready = true;
                
            }
        }
    );
}

void MandarianSpellSystem::UpdateSpellPositions()
{
    auto &reg = Engine::Registry();
    reg.view<SpellTag, Transform>().each(
        [&](auto &spellTag, auto &transform)
        {
            auto mandarian = GetMandarian();
            auto &mandarianTransform = reg.get<Transform>(mandarian);
            transform.position = mandarianTransform.position;
        }
    );
}

void MandarianSpellSystem::CastSpells()
{
    Engine::Registry().view<CommonSpell>().each(
        [&](auto spellEntity, auto &commonSpell)
        {
            for(auto *effect : commonSpell.effects)
                {
                    effect->Apply(GetMandarian(), spellEntity);
                }
        }
    );
}

Aura::Aura(UInt16 damage_, Float32 radius_)
    : damage(damage_), radius(radius_)
    {};

void Aura::Apply(Entity mandarian, Entity spell)
{
    auto &reg = Engine::Registry();
    
    auto &transform = reg.get<Transform>(mandarian);

    auto &transformSpell = reg.get<Transform>(spell);
    auto &commonSpell = reg.get<CommonSpell>(spell);

    if(commonSpell.active && commonSpell.ready)
    {
        commonSpell.ready = false;

        reg.view<Transform, Health, EnemyTag>().each(
        [&](auto enemyEntity, auto &enemyTransform, auto &enemyHealth, auto &enemyTag)
        {
            auto x0 = transform.position.x;
            auto y0 = transform.position.y;
            auto x = enemyTransform.position.x;
            auto y = enemyTransform.position.y;
            auto r = radius;

            if((x-x0)*(x-x0)+(y-y0)*(y-y0) <= r*r)
            {
                enemyHealth.current -= damage;
                // Logger::trace("{0:d}", enemyHealth.current);
                if(enemyHealth.current <= enemyHealth.min)
                {
                    reg.destroy(enemyEntity);
                }
            }
        });
    }
}

void MandarianSpellSystem::Run()
{
    UpdateCooldowns();
    UpdateSpellPositions();
    CastSpells();
}
