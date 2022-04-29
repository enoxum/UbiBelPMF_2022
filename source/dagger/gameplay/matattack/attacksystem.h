#pragma once

#include "core/core.h"
#include "core/system.h"
#include "characterattackfsm.h"

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

        void Run() override;

    };
}