#pragma once

#include "core/core.h"
#include "core/system.h"

using namespace dagger;

struct Body
{
    Vector2 velocity{ 0.0f, 0.0f };
    Vector2 force{ 0.0f, 0.0f };
    Float32 mass{ 1.0f };

    void applyForce(Vector2);
    void setVelocity(Vector2);
};

class SimplePhysicsSystem : public System
{
private:
    Float32 friction{ 0.99f };
    Float32 drag{ 0.9f };

public:
    inline String SystemName() override { 
        return "Physics System"; 
    }

    void Run() override;
}; 
