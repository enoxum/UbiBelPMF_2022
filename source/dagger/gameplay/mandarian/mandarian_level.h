#pragma once

#include "core/core.h"
#include "core/system.h"
#include "core/game.h"
#include "core/engine.h"

#include "core/graphics/window.h"

using namespace dagger;

namespace mandarian 
{
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
        void RenderGUI();
        void UpdateTimer();

        void SpawnTier1Enemies();
        void SpawnTier2Enemies();
        void SpawnTier3Enemies();
    };

};