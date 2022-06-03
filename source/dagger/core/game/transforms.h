#pragma once

#include "core/system.h"
#include "core/core.h"

using namespace dagger;

// TODO: create separate components for position and velocity
struct Transform 
{
    Vector3 position{0, 0, 0};    
    Vector2 velocity{0, 0};    
};

class TransformSystem
    : public System
{
    inline String SystemName() { return "Transform System"; }

    void Run() override;
};

