#pragma once

#include <tuple>
#include "core/game/transforms.h"

namespace dagger
{
    namespace net {
        struct NetworkedTag {};    

        // TODO: add more template meta programming magic to enable user defined appending to the tuple
        static const auto NetworkedComponents = std::tuple<Transform>{};
    }
} // namespace dagger
