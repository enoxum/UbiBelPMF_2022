#pragma once

#include "core/system.h"
#include "core/core.h"
    
using namespace dagger;

class ServerStateSyncSystem
    : public System
{
    inline String SystemName() { return "Server State Sync System"; }

    void Run() override;
};