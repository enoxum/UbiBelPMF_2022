#pragma once

#include "core/core.h"
#include "core/system.h"

using namespace dagger; 

class MovementSystem : public System 
{
public:
    inline String SystemName() { return "Movement system"; }

    void Run() override;

};
