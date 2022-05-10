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
    bool isOnMouse = false;

    int index = 0;
    int countEnter = 0;

    String fstCharSprite = "matattack:characters:fox:idle:idle1";
    String sndCharSprite = "matattack:characters:fox:idle:idle1";

    String fstCharAnimation = "fox";
    String sndCharAnimation = "fox";

protected:
    void LevelChooser(LevelChangeEvent lce);
    void OnKey(KeyboardEvent ke);
    void CharacterSelect(KeyboardEvent ke);
    void LevelSelect(MouseEvent me);
};
