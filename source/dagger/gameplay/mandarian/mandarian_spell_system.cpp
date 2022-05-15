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
                   , String spritePath
                   , String animatorPath)
{   
    auto &reg = Engine::Registry();
    auto entity = reg.create();
    auto spell = Spell::Get(entity);

    spell.sprite.color = {1.0f, 1.0f, 1.0f, 0.0f};
    AssignSprite(spell.sprite, spritePath);
    spell.sprite.scale = {1.0f, 1.0f };
    
    spell.common.name = name;
    spell.common.ready = true;
    spell.common.active = false;
    spell.common.cooldown = cooldown;
    spell.common.timer = cooldown;
    spell.common.spritePath = spritePath;
    spell.common.animatorPath = animatorPath;
    //spell.common.effects.push_back(new Aura(50.0f, 100.0f));

    auto *animation = Engine::Res<Animation>()[animatorPath];
    spell.common.duration = animation->absoluteLength;

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

void MandarianSpellSystem::UpdateSpellActiveness()
{
    Engine::Registry().view<CommonSpell, Sprite, Animator>().each(
        [&](CommonSpell &commonSpell, Sprite &sprite, Animator &animator)
        {
            if (commonSpell.ready)
            {
                commonSpell.ready = false;
                sprite.color = {1.0f, 1.0f, 1.0f, 0.8f};
                AnimatorPlay(animator, commonSpell.animatorPath);
                commonSpell.active = true;
                Logger::trace("Start animation!");
            }

            if ( commonSpell.active 
              && commonSpell.cooldown - commonSpell.duration > commonSpell.timer)
            {
                sprite.color = {1.0f, 1.0f, 1.0f, 0.0f};
                AnimatorStop(animator);
                commonSpell.active = false;
                Logger::trace("Stop animation!");
            }
        }
    );
}

void MandarianSpellSystem::CastSpells()
{
    Engine::Registry().view<CommonSpell>().each(
        [&](auto spellEntity, auto &commonSpell)
        {
            if (commonSpell.active)
            {
                for(auto *effect : commonSpell.effects)
                {
                    effect->Apply(spellEntity);
                }
            }
        }
    );
}

void Aura::Apply(Entity spell)
{
    auto &reg = Engine::Registry();
    auto &transformSpell = reg.get<Transform>(spell);
    auto &commonSpell = reg.get<CommonSpell>(spell);

    reg.view<Transform, Health, EnemyTag>().each(
    [&](auto enemyEntity, auto &enemyTransform, auto &enemyHealth, auto &enemyTag)
    {
        auto x0 = transformSpell.position.x;
        auto y0 = transformSpell.position.y;
        auto x = enemyTransform.position.x;
        auto y = enemyTransform.position.y;
        auto r = radius;

        if((x-x0)*(x-x0)+(y-y0)*(y-y0) <= r*r)
        {
            enemyHealth.current -= damage * Engine::DeltaTime();
            // Logger::trace("{0:d}", enemyHealth.current);
            if(enemyHealth.current <= enemyHealth.min)
            {
                reg.destroy(enemyEntity);
            }
        }
    });
}

void FixTo::Apply(Entity spell)
{
    auto &targetTransform = Engine::Registry().get<Transform>(target);
    auto &spellTransform = Engine::Registry().get<Transform>(spell);

    spellTransform.position = targetTransform.position;
}

void MandarianSpellSystem::Run()
{
    UpdateCooldowns();
    UpdateSpellActiveness();
    CastSpells();
}
