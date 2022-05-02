#pragma once
#include "core/core.h"
#include "core/system.h"
#include "core/input/inputs.h"

using namespace dagger;

struct LevelChangeEvent {
    int lvl;
};


class LevelChangeSystem : public System
{


public:
    inline String SystemName() { return "Matattack Tools System"; }

    void SpinUp() override;
    void WindDown() override;

    bool isStarted = false;

protected:
    void LevelChooser(LevelChangeEvent lce);
    void OnKey(KeyboardEvent ke);
    void OnMouse(MouseEvent me);
};
