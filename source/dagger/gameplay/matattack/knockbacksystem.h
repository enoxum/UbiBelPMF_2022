#pragma once

#include "core/core.h"
#include "core/system.h"

using namespace dagger;

struct KnockbackInfo
{
	bool is_knocked = false;
	SInt16 direction = 0;
	Float32 base_vertical_speed = 300.0F;
	Float32 horizontal_speed = 0.0f;
	Float32 base_horizontal_speed = 500.0f;
	Float32 horizontal_decrease = 3.0F;
};

class KnockbackSystem : public System
{
public:

	inline String SystemName() { return "Knockback System"; }

	void Run() override;

};
#pragma once
