#include "mainmenu.h"

#include "core/game/transforms.h"
#include "core/graphics/text.h"

#include "gameplay/team_game/Utilities/map_generator_utility.h"
#include "gameplay/team_game/team_game_main.h"

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
			m_restart = true;
		}

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
				AssignSprite(sprite, "Background:introduction");
				sprite.size = { 400,300 };
				sprite.position = {0,125,0};
				text.Set("pixel-font", "Press P to resume the game", { 0,0,0 });
				sprite.UseAsUI();
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

		if (m_restart) {
			m_restart = false;
			Engine::Registry().clear();
			team_game::SetupWorld();
		}

		auto& sprite = ents.get<Sprite>(ent);
		auto& text = ents.get<Text>(ent);		
	}
}
