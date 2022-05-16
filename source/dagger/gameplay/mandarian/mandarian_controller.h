#pragma once

#include "core/core.h"
#include "core/system.h"

#include "core/graphics/sprite.h"
#include "core/game/transforms.h"
#include "core/input/inputs.h"

#include "gameplay/common/simple_collisions.h"
#include "gameplay/common/simple_physics.h"
#include "gameplay/mandarian/mandarian_controller_fsm.h"

using namespace dagger;

namespace mandarian 
{
    struct CharacterStats
    {
        Float32 maxHealth { 100.0f };   // Maximum amount of HP
        Float32 recovery { 0.0f };      // HP generated for new Lvl
        Float32 armor { 0.0f };         // Amount of reduced incoming damage
        Float32 might { 1.0f };         // Multiplicator for demage
        Float32 area { 1.0f };          // Multiplicator for area of attacks
        Float32 speed { 1.0f };         // Movement speed of all projectiles
        Float32 duration { 1.0f };      // Multiplicator for duration of spells
        Float32 cooldown { 1.0f };      // Multiplicator for cooldown of spells 
        Float32 growth { 1.0f };        // Multiplicator for experiance gained
        Float32 danger { 20.0f };       // Radius of enemy demage deal
        Float32 magnet { 20.0f };         // Radius of mandarin pickup
    };

    struct CharacterHealth
    {
        Float32 points { 100u };
    };

    struct CharacterExperience
    {
        UInt16 level { 0u };
        UInt16 points { 0u };
    };

    struct Character
    {
        Entity entity;
        Sprite &sprite;
        Transform &transform;
        Body &body;
        CircleCollision &collision;
        InputReceiver &input;
        CharacterStats &stats;
        CharacterExperience &experience;
        CharacterHealth &health;

        static Character Get(Entity);

        static Character Create(
                ColorRGB color_ = { 0.0f, 0.0f, 0.0f }, 
                Vector2 position_ = { 0.0f, 0.0f },
                Vector2 scale_ = { 10.0f, 10.0f },
                Float32 radius_ = 2.0f,
                String input_ = String{ "mandarian" });
    };

    struct Player {
        bool b;
    };

	class MandarianControllerSystem
		: public System
	{
		MandarianControllerFSM mandarianFSM;

	public:
		String SystemName() override {
			return "Mandarian Controller System";
		}

		void Run() override;
	};

}