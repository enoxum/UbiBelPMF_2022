#include "glavonje_server.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/game/transforms.h"
#include "core/net/server.h"
#include "core/net/connection.h"

using namespace dagger;
using namespace glavonje;

class GlavonjeNetServer : public dagger::net::IServer<EMsgType>
{
public:
    GlavonjeNetServer(UInt16 port) : IServer(port) {}
};

void GlavonjeServer::CoreSystemsSetup()
{
    auto& engine = Engine::Instance();
    engine.AddSystem<InputSystem>();
    engine.AddSystem<TransformSystem>();
}

void GlavonjeServer::GameplaySystemsSetup()
{

}

void GlavonjeServer::WorldSetup()
{
    auto* server = new GlavonjeNetServer{3000};

    server->Start();
}


