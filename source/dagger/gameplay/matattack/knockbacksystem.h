#pragma once

#include "core/core.h"
#include "core/system.h"

using namespace dagger;

struct KnockbackInfo
{
	// how fast its falling
	Float32 speed;
	Float32 increase;
};

class KnockbackSystem : public System
{
public:

	inline String SystemName() { return "Knockback System"; }

	void Run() override;

};
#pragma once
