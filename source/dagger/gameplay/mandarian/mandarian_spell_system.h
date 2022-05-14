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
        virtual void Apply(Entity source, Entity spell) = 0;
    };

    class Aura
        : public IEffect
    {
        public:

        void Apply(Entity source, Entity spell) override;
        Aura(UInt16 damage_, Float32 radius_);

        UInt16 damage;
        Float32 radius;
    };

    struct SpellTag
    {
        Bool tag;
    };

    struct CommonSpell
    {
        String name;
        Float32 cooldown;
        Float32 timer;
        Bool ready;
        Bool active;
        Float32 duration;
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
                            , Bool ready
                            , Bool active
                            /*, std::vector<IEffect*> &effects*/ );

        static Spell Get (Entity entity);
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
        Entity GetMandarian() { return mandarian; }
        void UpdateCooldowns();
        void UpdateSpellPositions();
        void UpdateAnimations();
        void CastSpells();

        void Run() override;
    };
};


