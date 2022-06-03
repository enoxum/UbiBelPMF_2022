#include "mainmenu.h"

#include "core/game/transforms.h"
#include "core/graphics/text.h"

#include "gameplay/team_game/Utilities/map_generator_utility.h"
#include "gameplay/team_game/team_game_main.h"

#include "timer.h"

#include<iostream>

using namespace dagger;
using namespace team_game;

void mainmenu::SpinUp()
{
	Engine::Dispatcher().sink<KeyboardEvent>().connect<&mainmenu::OnKeyboardEvent>(this);
}

void mainmenu::WindDown()
{
	Engine::Dispatcher().sink<KeyboardEvent>().disconnect<&mainmenu::OnKeyboardEvent>(this);
}

void mainmenu::OnKeyboardEvent(KeyboardEvent kEvent_) {
	auto& reg = Engine::Registry();
	auto ents = reg.view<Sprite, MainMenu_, Text>();
	auto& inst = Engine::Instance();

	for (const auto ent : ents) {

		auto& sprite = ents.get<Sprite>(ent);
		auto& mm = ents.get<MainMenu_>(ent);
		auto& text = ents.get<Text>(ent);

		if (kEvent_.key == EDaggerKeyboard::KeyR && (kEvent_.action == EDaggerInputState::Pressed || kEvent_.action == EDaggerInputState::Held)) {
			if (started) {
				Engine::Registry().clear();
				team_game::SetupWorld();
				restarted = true;
				started = false;
			}
		}

		if (kEvent_.key == EDaggerKeyboard::KeyEnter && (kEvent_.action == EDaggerInputState::Pressed || kEvent_.action == EDaggerInputState::Held)) {
			if (!started) {
				
				inst.ToggleSystemsPause(false);
				sprite.size = { 0,0 };
				text.Set("pixel-font", "", { 0,0,0 });
				restarted = false;
				started = true;
			}
		}

		if (kEvent_.key == EDaggerKeyboard::KeyP && (kEvent_.action == EDaggerInputState::Pressed || kEvent_.action == EDaggerInputState::Held)) {
			if (started) {
				pause = !pause;
				if (pause) {
					inst.ToggleSystemsPause(true);
					AssignSprite(sprite, "Background:introduction");
					sprite.size = { 400,300 };
					sprite.position = { 0,125,0 };
					text.Set("pixel-font", "Press P to resume the game", { 0,0,0 });
					sprite.UseAsUI();
				}

				else {
					inst.ToggleSystemsPause(false);
					sprite.size = { 0,0 };
					text.Set("pixel-font", "", { 0,0,0 });
					sprite.UseAsUI();
				}
			}
			
		}
	}
}

void mainmenu::Run() {

	auto& inst = Engine::Instance();

	auto& reg = Engine::Registry();
	auto ents = reg.view<Sprite, MainMenu_, Text>();

	for (const auto ent : ents) {

		auto& sprite = ents.get<Sprite>(ent);
		auto& mm = ents.get<MainMenu_>(ent);
		auto& text = ents.get<Text>(ent);

		if (mm.died) {
			
			reg.clear();
			team_game::SetupWorld();
			started = false;
		}

		if (mm.won) {
			reg.clear();
			team_game::SetupWorld();
			text.Set("pixel-font", "Bravo! Press Enter to play again.", { 0,-9,0 });
			AssignSprite(sprite, "Background:menu");
			sprite.size = { 1700, 1300 };
			started = false;
		}
	}
}
