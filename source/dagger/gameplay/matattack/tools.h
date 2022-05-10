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
        , public Subscriber<ToolMenuRender>
    {

    public:
        inline String SystemName() { return "Matattack Tools System"; }

        void SpinUp() override;
        void WindDown() override;

    protected:
        void RenderToolMenu();

    };
}

#endif //defined(DAGGER_DEBUG)
