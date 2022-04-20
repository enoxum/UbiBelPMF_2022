#pragma once

#include "core/core.h"
#include "core/system.h"

using namespace dagger;
 
class JumpingSystem : public System
{
public:
	inline String SystemName() { return "Jumping System"; }

	void Run() override;
};
