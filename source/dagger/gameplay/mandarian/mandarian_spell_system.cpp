#include "mandarian_spell_system.h"

#include "core/engine.h"
#include "mandarian_enemy.h"

#include "mandarian_controller.h"

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
                   , String animatorPath
                   , Float32 scale)
{   
    auto &reg = Engine::Registry();
    auto entity = reg.create();
    auto spell = Spell::Get(entity);

    spell.sprite.color = {1.0f, 1.0f, 1.0f, 0.0f};
    AssignSprite(spell.sprite, spritePath);
    spell.sprite.scale = {scale, scale};
    
    spell.common.name = name;
    spell.common.ready = true;
    spell.common.active = false;
    spell.common.cooldown = cooldown;
    spell.common.timer = cooldown;
    spell.common.spritePath = spritePath;
    spell.common.animatorPath = animatorPath;

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
        [&](Entity spellEntity, CommonSpell &commonSpell, Sprite &sprite, Animator &animator)
        {
            if (commonSpell.ready)
            {
                for(auto *effect : commonSpell.effects)
                {
                    effect->Init(spellEntity);
                }

                commonSpell.ready = false;
                sprite.color = {1.0f, 1.0f, 1.0f, 0.8f};
                AnimatorPlay(animator, commonSpell.animatorPath);
                commonSpell.active = true;
                
            }

            if ( commonSpell.active 
              && commonSpell.cooldown - commonSpell.duration >= commonSpell.timer)
            {
                sprite.color = {1.0f, 1.0f, 1.0f, 0.0f};
                AnimatorStop(animator);
                commonSpell.active = false;
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

void Aura::Init(Entity spell)
{}

void Aura::Apply(Entity spell)
{
    auto &reg = Engine::Registry();
    auto &transformSpell = reg.get<Transform>(spell);
    auto &commonSpell = reg.get<CommonSpell>(spell);

    auto &mandarianStats = reg.get<CharacterStats>(mandarian);

    reg.view<Transform, Health, EnemyTag>().each(
    [&](auto enemyEntity, auto &enemyTransform, auto &enemyHealth, auto &enemyTag)
    {
        if(glm::distance(transformSpell.position, enemyTransform.position) <= radius)
        {
            enemyHealth.current -= damage * mandarianStats.might  * Engine::DeltaTime();
        }
    });
}

void Thunder::Init(Entity spell)
{
    auto &reg = Engine::Registry();
    
    auto &mandarianTransform = reg.get<Transform>(mandarian);
    auto &spellTransform = reg.get<Transform>(spell);

    dx = (rand() % 400) - 200;
    dy = (rand() % 400) - 200;

    spellTransform.position.x = mandarianTransform.position.x + dx;
    spellTransform.position.y = mandarianTransform.position.y + dy + 60.0f;
}

void Thunder::Apply(Entity spell)
{
    auto &reg = Engine::Registry();
    auto &commonSpell = reg.get<CommonSpell>(spell);

    auto &mandarianStats = reg.get<CharacterStats>(mandarian);
    auto &spellTransform = reg.get<Transform>(spell);    

    reg.view<Transform, Health, EnemyTag>().each(
    [&](auto enemyEntity, auto &enemyTransform, auto &enemyHealth, auto &enemyTag)
    {
        if(glm::distance(spellTransform.position, enemyTransform.position + Vector3 { 0.0f, 80.0f, 0.0f}) <= radius)
        {
            enemyHealth.current -= damage * mandarianStats.might * Engine::DeltaTime();
        }
    });

}

void FixTo::Init(Entity spell)
{}

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
