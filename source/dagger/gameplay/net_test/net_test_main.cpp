#include "net_test_main.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"
#include "core/game/transforms.h"
#include "core/net/client/client.h"
#include "core/net/server/server.h"

using namespace dagger;
using namespace net_test;
using namespace net;

enum class EMsgType {
    Shoot, Jump
};

void test_message_io() {
    Message<EMsgType> msg;
    msg.header.id = EMsgType::Shoot;
    
    int x = 3;
    bool b = false;
    double d = 3.141;
    struct {
        float x;
        float y;
    } pts[10];

    msg << x << b << d << pts;

    x = 123;
    b = true;
    d = 1.1;

    msg >> pts >> d >> b >> x;
}

void NetTest::GameplaySystemsSetup(){
    test_message_io();
}


void NetTest::CoreSystemsSetup()
{
    auto& engine = Engine::Instance();
    engine.AddSystem<TransformSystem>();
}

void NetTest::WorldSetup(){
}

