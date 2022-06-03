#pragma once

#include "core/system.h"
#include "core/core.h"
    
using namespace dagger;

class ClientInputSyncSystem
    : public System
{
    inline String SystemName() { return "Client Input Sync System"; }

    void Run() override;
};