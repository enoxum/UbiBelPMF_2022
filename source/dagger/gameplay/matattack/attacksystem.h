#pragma once

#include "core/core.h"
#include "core/system.h"
#include "characterattackfsm.h"
#include "events.h"

using namespace dagger;


namespace matattack
{
    class AttackSystem : public System
    {
    public:
        FSMCharacterAttack attackFSM;
        String SystemName() override {
            return "Character Attack System";
        }

        void SpinUp() override;
        void Run() override;
        void WindDown() override;

    };
}