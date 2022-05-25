#include <enet/enet.h>
#include "core/core.h"
#include "core/net/v4/remote_client.h"
#include "core/net/v4/server.h"

Entity server::MakeClientEntity(Registry &registry) {
    auto &ctx = registry.ctx<server::NetworkContext>();

    Entity entity = registry.create();
    auto &client = registry.emplace<RemoteClient>(entity);
    ctx.pendingCreatedClients.push_back(entity);

    return entity;
}


