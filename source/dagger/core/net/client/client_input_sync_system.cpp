#include "client_input_sync_system.h"
#include "core/engine.h"
#include "core/net/common/net.h"
#include "core/net/client/client.h"
#include "core/net/client/enet_client_system.h"
#include "core/net/common/message.h"
#include "core/input/inputs.h"

using namespace dagger;
using namespace dagger::net;

void ClientInputSyncSystem::Run()
{
    auto& registry = Engine::Registry();
    auto& ctx = registry.ctx<client::NetworkContext>();

    registry.view<NetworkedTag, InputReceiver>().each([&](auto _, const InputReceiver& input_) {
        ctx.packetSignal.publish(Packet{input_});
    });
}
