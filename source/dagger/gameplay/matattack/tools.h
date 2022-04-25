#pragma once

#if defined(DAGGER_DEBUG)

#include "core/system.h"
#include "core/core.h"

#include "tools/toolmenu.h"

using namespace dagger;

namespace matattack
{
    class Tools
        : public System
        , public Publisher<ToolMenuRender>
        , public Subscriber<GUIRender>
    {
        bool m_lvl1 = false;
        bool m_lvl2 = false;
        bool m_lvl3 = false;

    public:
        inline String SystemName() { return "Matattack Tools System"; }

        void SpinUp() override;
        void WindDown() override;

    protected:
        void RenderToolMenu();
        void LevelChooser();

    };
}

#endif //defined(DAGGER_DEBUG)
