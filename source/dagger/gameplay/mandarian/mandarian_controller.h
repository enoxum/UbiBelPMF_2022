#pragma once

#include "core/core.h"
#include "core/system.h"
#include "gameplay/mandarian/mandarian_controller_fsm.h"

using namespace dagger;

namespace mandarian 
{

	class MandarianControllerSystem
		: public System
	{
		MandarianControllerFSM mandarianFSM;

	public:
		String SystemName() override {
			return "Mandarian Controller System";
		}

		void Run() override;
	};

}