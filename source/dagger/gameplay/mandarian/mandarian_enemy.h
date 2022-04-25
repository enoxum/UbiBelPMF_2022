#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"

#include "core/graphics/sprite.h"
#include "core/game/transforms.h"
#include "gameplay/common/simple_physics.h"
#include "mandarian_damage_system.h"

using namespace dagger;

namespace mandarian 
{
    struct Health;

    struct EnemyTag {
        Bool tag;
    };

    struct Enemy
    {
        Entity entity;
        Sprite &sprite;
        Transform &transform;
        Body &body;
        Health &health;

        static Enemy Get(Entity entity);
        static Enemy Create(
            Vector2 position_ = {0.0f, 0.0f},
            ColorRGB color_ = {1.0f, 0.0f, 0.0f},
            Vector2 scale_ = {10.0f, 10.0f});
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

};