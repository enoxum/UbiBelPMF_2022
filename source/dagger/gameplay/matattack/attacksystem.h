#pragma once

#include "core/core.h"
#include "core/system.h"
#include "events.h"
#include "knockbacksystem.h"

using namespace dagger;

namespace matattack
{
    struct AttackInfo {
        bool is_attacking = false;
        SInt32 base_imunity_duration = 100;
        SInt32 imunity_duration = 0;
        SInt32 attack_damage = 10;
        SInt32 max_attack_damage = 10;
        SInt32 hp = 100;
        SInt32 max_hp = 100;
    };

    struct HealthInfo {
        SInt32 num_of_hearts = 3;
    };

    struct HeartInfo {
        bool active = true;
    };

    class AttackSystem : public System
    {
    public:
        String SystemName() override {
            return "Character Attack System";
        }

        void DetectPlayerCollision();
        void DealDamage(AttackInfo& attacker_info, AttackInfo& victim_info, SInt32 num);
        void KnockPlayer(KnockbackInfo& knockback_info,SInt16& direction);

        void SpinUp() override;
        void Run() override;
        void WindDown() override;

    };
}