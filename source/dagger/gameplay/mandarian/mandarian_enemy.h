#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"

#include "core/graphics/sprite.h"
#include "core/game/transforms.h"

#include "gameplay/common/simple_collisions.h"
#include "gameplay/common/simple_physics.h"

using namespace dagger;

namespace mandarian 
{
    struct EnemyTag 
    {
        Bool tag;
    };

    struct Health
    {
        Float32 current;
        Float32 max;
    };

    struct Demage
    {
        Float32 points { 100.0f };
    };

    struct Enemy
    {
        Entity entity;
        Sprite &sprite;
        Transform &transform;
        Body &body;
        CircleCollision &collision;
        Health &health;
        Demage &demage;

        static Enemy Get(Entity entity);
        static Enemy Create(
            UInt8 tier_ = 1u,
            Vector2 position_ = {0.0f, 0.0f},
            Vector2 scale_ = {1.0f, 1.0f},
            ColorRGB color_ = {1.0f, 1.0f, 1.0f},
            Float32 radius_ = 10.0f,
            Float32 demage_ = 50.0f);
    };

    class EnemyMovementSystem
		: public System
	{
        Entity mandarian;

	public:
		String SystemName() override {
			return "Enemy Movement System";
		}

        void SetMandarian(Entity mandarian_) { mandarian = mandarian_; };

		void Run() override;
	};

    class EnemyDemageSystem
        : public System
    {
        Entity mandarian;

    public:
        String SystemName() override {
            return "EnemyDemageSystem";
        }

        void SetMandarian(Entity mandarian_) { mandarian = mandarian_; };

        void Run() override;
    };

    class EnemyDeathSystem
        : public System
    {
    
    public:
        String SystemName() override {
            return "Mandarian Spell System";
        }

        void Run() override;
    };
};
