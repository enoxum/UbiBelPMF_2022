#pragma once

#include "core/core.h"
#include "core/system.h"

using namespace dagger;

struct Gravity
{
	Float32 speed;
	Float32 increase;
};

class GravitySystem : public System 
{
public:

	inline String SystemName() { return "Gravity System"; }

	void Run() override;

};
