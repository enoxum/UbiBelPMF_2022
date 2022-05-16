
#include "core/engine.h"
#include "gameplay/ping_pong/ping_pong_main.h"
#include "gameplay/platformer/platformer_main.h"
#include "gameplay/racing/racing_main.h"
#include "gameplay/team_game/team_game_main.h"
#include "gameplay/tiles_example/tiles_example_main.h"
#include "gameplay/editor/editor_main.h"
#include "gameplay/glavonje/glavonje_client.h"
#include "gameplay/glavonje/glavonje_server.h"

int main(int argc_, char** argv_)
{
	dagger::Engine engine;
	if (argc_ == 2 && strcmp(argv_[1], "client")) 
	{
		return engine.Run<glavonje::GlavonjeClient>();
	}
	return engine.Run<glavonje::GlavonjeServer>();
}
