#include "mainmenu.h"

#include "core/game/transforms.h"
#include "core/graphics/text.h"

#include "gameplay/team_game/Utilities/map_generator_utility.h"

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

		if (kEvent_.key == EDaggerKeyboard::KeyEnter && (kEvent_.action == EDaggerInputState::Pressed || kEvent_.action == EDaggerInputState::Held)) {
			show = !show;
			if (show) {

			}
			else {
				inst.ToggleSystemsPause(false);
				sprite.size = { 0,0 };
				text.Set("pixel-font", "", { 0,0,0 });
			}
		}

		if (kEvent_.key == EDaggerKeyboard::KeyP && (kEvent_.action == EDaggerInputState::Pressed || kEvent_.action == EDaggerInputState::Held)) {
			pause = !pause;
			if (pause) {
				inst.ToggleSystemsPause(true);
				sprite.size = { 0,0 };
				text.Set("pixel-font", "Press P to resume the game", { 0,0,0 });
			}
			else {
				inst.ToggleSystemsPause(false);
				sprite.size = { 0,0 };
				text.Set("pixel-font", "", { 0,0,0 });
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
		auto& text = ents.get<Text>(ent);		
	}
}