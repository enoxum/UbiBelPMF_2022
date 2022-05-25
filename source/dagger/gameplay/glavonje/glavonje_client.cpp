#include "glavonje_client.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"
#include "core/game/transforms.h"
#include <enet/enet.h>

#include "core/net/client.h"

using namespace dagger;
using namespace glavonje;

using namespace net;


class GlavonjeNetClient : public dagger::net::IClient<EMsgType> 
{
public:
    bool Shoot(UInt32 id)
    {
        Message<EMsgType> msg;
        msg.header.id = EMsgType::Shoot;
        msg << id;
        Send(msg);
    }
};

void GlavonjeClient::CoreSystemsSetup()
{
    auto& engine = Engine::Instance();
    engine.AddSystem<InputSystem>();
    engine.AddSystem<TransformSystem>();
}

void GlavonjeClient::GameplaySystemsSetup()
{

}

void GlavonjeClient::WorldSetup(){

    if (enet_initialize() != 0) {
        Logger::critical("Failed to initialize ENet");
    }
    // ShaderSystem::Use("standard");

    GlavonjeNetClient* gl = new GlavonjeNetClient();
    bool isgood= gl->Connect("127.0.0.1", 3000);
    Logger::critical(fmt::format("Connected to server: {}", isgood));

    Message<EMsgType> msg;
    msg.header.id = EMsgType::Shoot;
    
    int x = 3;
    msg << x;

    gl->Send(msg);
    // auto* camera = Engine::GetDefaultResource<Camera>();
    // camera->mode = ECameraMode::FixedResolution;
    // camera->size = { 800, 600 };
    // camera->zoom = 1;
    // camera->position = { 0, 0, 0 };
    // camera->Update();



}


