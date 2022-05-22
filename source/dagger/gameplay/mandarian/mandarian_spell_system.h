#pragma once

#include "core/core.h"
#include "core/system.h"

#include "core/graphics/sprite.h"
#include "core/game/transforms.h"
#include "core/graphics/animation.h"

#include <vector>

using namespace dagger;

namespace mandarian
{   
    class IEffect
    {
    public:
        virtual void Apply(Entity spell) = 0;
        virtual void Init(Entity spell) = 0;
    };

    class Aura
        : public IEffect
    {
    public:
        void Apply(Entity spell) override;
        void Init(Entity spell) override;

        Aura(Float32 damage_, Float32 radius_, Entity mandarian_)
            : damage(damage_), radius(radius_), mandarian(mandarian_) {};

    private:
        Float32 damage;
        Float32 radius;

        Entity mandarian;
    };

    class Thunder
        : public IEffect
    {
    public:
        void Apply(Entity spell) override;
        void Init(Entity spell) override;

        Thunder(Float32 damage_, Float32 radius_, Entity mandarian_)
            : damage(damage_), radius(radius_), mandarian(mandarian_) 
        {};

    private:
        Float32 damage;
        Float32 radius;

        Float32 dx;
        Float32 dy;

        Entity mandarian;
    };

    class FixTo
        : public IEffect
    {
    public:
        void Apply(Entity spell) override;
        void Init(Entity spell);

        FixTo(Entity target_) 
            : target(target_){};

    private:
        Entity target;
    };

    class Shuriken
        : public IEffect
    {
    public:
        void Apply(Entity spell) override;
        void Init(Entity spell) override;

        Shuriken(Entity mandarian_, Float32 speed_) 
            : mandarian(mandarian_)
            , speed(speed_) {};

    private:
        Entity mandarian;
        Float32 speed;
        Float32 timer;
        Vector2 direction;
    };

    struct CommonSpell
    {
        String name;
        Float32 cooldown;
        Float32 timer;
        Bool ready;
        Bool active;
        Float32 duration;
        String spritePath;
        String animatorPath;
        std::vector<IEffect*> effects;
    };

    struct Spell
    {
        Entity entity;
        CommonSpell &common;
        Transform &transform;
        Sprite &sprite;
        Animator &animator;

        static Spell Create ( const String &name
                            , Float32 cooldown
                            , Float32 duration
                            , String spritePath
                            , String animatorPath
                            , Float32 scale = 1.0f
                            );
        static Spell Get (Entity entity);

        void AddEffects(){}

        template<typename Effect, typename... Effects> 
        void AddEffects(Effect effect_, Effects... effects_)
        {   
            common.effects.push_back(dynamic_cast<IEffect*>(effect_));
            AddEffects(effects_...);
        }

    };

    class MandarianSpellSystem
    : public System
    {
        private:
        Entity mandarian;

        public:
		String SystemName() override {
			return "Mandarian Spell System";
		}

        void SetMandarian(Entity mandarian_) { mandarian = mandarian_; };
        void UpdateCooldowns();
        void UpdateSpellActiveness();
        void CastSpells();

        void Run() override;
    };
};


