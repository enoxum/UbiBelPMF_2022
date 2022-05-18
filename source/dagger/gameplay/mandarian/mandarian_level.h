#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"

#include "core/graphics/window.h"
#include "core/graphics/sprite.h"
#include "core/game/transforms.h"

#include "gameplay/common/simple_collisions.h"

using namespace dagger;

namespace mandarian 
{
    struct CharacterStats;

    struct Experience
    {
        UInt16 points { 10u };
    };

    struct Mandarin
    {
        Entity entity;
        Sprite &sprite;
        Transform &transform;
        Experience &experience;

        static Mandarin Get(Entity entity);
        static Mandarin Create(
            UInt16 points = 10u,
            Vector2 position_ = { 0.0f, 0.0f },
            Vector2 scale_ = { 0.5f, 0.5f }
        );
    };

    struct Timer
    {
        UInt8 minutes;
        UInt8 seconds;
    };
    
    class LevelSystem
        : public System
        , public Subscriber<GUIRender>
    {
        TimePoint startTime { TimeSnapshot() };
        Timer timer;

        Entity mandarian;
        Bool flag { true };

    public:
		String SystemName() override {
			return "Level System";
		};

        void SpinUp() override;
		void Run() override;
        void WindDown() override;

        inline void SetMandarian(Entity mandarian_) { mandarian = mandarian_; }
    
    private:
        UInt16 CalculateMaxExp(UInt16 level);
        
        void Mutate(CharacterStats &mandarianStats);

        void RenderGUI();
        void UpdateTimer();
        void UpdateExperience();
        void SpawnEnemies();

        void SpawnTier1Enemies(unsigned numberOfEnemies);
        void SpawnTier2Enemies();
        void SpawnTier3Enemies(unsigned numberOfEnemies);
    };

};