#include "Core.h"

//#############################################################################
//# Title screen loop handler and functions:                                  #
//#############################################################################

static bool first = true;

pld::State pld::Core::onUserUpdateTitlescreen(float elapsed_time) {
	resetIfStateChanged();

	olc::vf2d title_image_pos(ScreenWidth() / 2 - 240* getGlobalScale().x, (64 + 165)* getGlobalScale().y);
	olc::vf2d title_text_pos((float)(ScreenWidth() / 2 - 331.5* getGlobalScale().x), 48* getGlobalScale().y);//ScreenHeight() / 3 - ScreenHeight() / 5 - ScreenHeight() / 10);

	DrawDecal(title_image_pos, dcl_title.get(), getGlobalScale());
	DrawDecal(title_text_pos, dcl_text->at(1).get(), getGlobalScale());
	//std::string wait_for_name_text = "CAPTAIN";
	//DrawStringDecal(title_pos, title, olc::YELLOW, { 15.0F, 15.0F });

	olc::vf2d choose_name_text_pos(ScreenWidth() / 2 - 405 * getGlobalScale().x, ScreenHeight() - 300 * getGlobalScale().y); // - 450
	olc::vf2d player_name_text_pos(ScreenWidth() / 2 - 250 * getGlobalScale().x, ScreenHeight() - 170 * getGlobalScale().y);

	DrawDecal(choose_name_text_pos, dcl_text->at(2).get(), getGlobalScale());

	pld::State next = inputListenerTitlescreen(elapsed_time);
	//DrawStringDecal(text_pos, choose_name, olc::YELLOW, { 7.0f, 7.0f }); //wait_for_name_text
	// CUSTOM YELLOW COLOR ->F6C637 ->rgb(246, 198, 55)
	drawButton({ ScreenWidth() / 2 - 275 * getGlobalScale().x, ScreenHeight() - 198 * getGlobalScale().y },
		{ 0.5f, 0.5f }, {(int)(32 * getGlobalScale().x), (int)(7 * getGlobalScale().y)}, dcl_coin->at(1), olc::NONE, false);
	DrawStringDecal(player_name_text_pos, level.player1.name, olc::Pixel(246, 198, 55), { 7.0f * getGlobalScale().x, 7.0f * getGlobalScale().y });

	drawCursor(elapsed_time, player_name_text_pos);

	// Buttons:
	int button_quit_horizontal_tiles = 11; // getHorizontal(pld::Button::Quit);
	int button_highscore_horizontal_tiles = 19; // getHorizontal(pld::Button::Highscore);
	const int button_offset_x = 405;
	const int button_offset_y = 155;
	float button_tile_scale = 0.5f;
	olc::vf2d button_scale = { button_tile_scale, button_tile_scale };
	constexpr int static_offset_quit = 40;
	const int button_offset_quit = (int)(button_quit_horizontal_tiles * tiles.size * button_tile_scale + static_offset_quit);
	constexpr int static_offset_highscore = 65;
	const int button_offset_highscore = (int)(button_highscore_horizontal_tiles * tiles.size * button_tile_scale + static_offset_highscore);
	next = buttonQuit({ ScreenWidth() / 2 - button_offset_x * getGlobalScale().x,
		(float)(ScreenHeight() / 2 + button_offset_y * getGlobalScale().y) },
		button_scale, elapsed_time, next);
	next = buttonHighscore({ ScreenWidth() / 2 - (button_offset_x - button_offset_quit) * getGlobalScale().x,
		(float)(ScreenHeight() / 2 + button_offset_y * getGlobalScale().y) },
		button_scale, elapsed_time, next);
	next = buttonPlay({ ScreenWidth() / 2 - (button_offset_x - button_offset_quit - button_offset_highscore) * getGlobalScale().x,
		(float)(ScreenHeight() / 2 + button_offset_y * getGlobalScale().y) },
		button_scale, elapsed_time, next);
	
	if (sounds->at(0).get()->getCurrentPosition() == sounds->at(1).get()->getDuration()) {
		LONGLONG zero = 0;
		LONGLONG duration = sounds->at(1).get()->getDuration();
		sounds->at(0).get()->setPositions(&zero, &duration, true);
		sounds->at(0).get()->play();
	}


	return next;
}

pld::State pld::Core::inputListenerTitlescreen(float elapsed_time) {
	const int max_string_length = 8;
	if (GetKey(olc::A).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "A"; }
	if (GetKey(olc::B).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "B"; }
	if (GetKey(olc::C).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "C"; }
	if (GetKey(olc::D).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "D"; }
	if (GetKey(olc::E).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "E"; }
	if (GetKey(olc::F).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "F"; }
	if (GetKey(olc::G).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "G"; }
	if (GetKey(olc::H).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "H"; }
	if (GetKey(olc::I).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "I"; }
	if (GetKey(olc::J).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "J"; }
	if (GetKey(olc::K).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "K"; }
	if (GetKey(olc::L).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "L"; }
	if (GetKey(olc::M).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "M"; }
	if (GetKey(olc::N).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "N"; }
	if (GetKey(olc::O).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "O"; }
	if (GetKey(olc::P).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "P"; }
	if (GetKey(olc::Q).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "Q"; }
	if (GetKey(olc::R).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "R"; }
	if (GetKey(olc::S).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "S"; }
	if (GetKey(olc::T).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "T"; }
	if (GetKey(olc::U).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "U"; }
	if (GetKey(olc::V).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "V"; }
	if (GetKey(olc::W).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "W"; }
	if (GetKey(olc::X).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "X"; }
	if (GetKey(olc::Y).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "Y"; }
	if (GetKey(olc::Z).bPressed && level.player1.name.size() < max_string_length) { level.player1.name += "Z"; }

	if (GetKey(olc::BACK).bPressed && level.player1.name.size() > 0) { 
		level.player1.name.pop_back(); animator.return_key_control = -0.1f; 
	}

	if (GetKey(olc::BACK).bHeld && level.player1.name.size() > 0) {
		animator.return_key_control += elapsed_time; 
		if (animator.return_key_control > 0.1f) { level.player1.name.pop_back(); animator.return_key_control = 0; }
	}

	if (GetKey(olc::ENTER).bPressed && level.player1.name != "") {
		reportStateChange();
		return pld::State::Ease;
	}

	if (GetKey(olc::ESCAPE).bPressed) {
		this->escaped_from_state = pld::State::Titlescreen;
		return pld::State::Settings;
	}

	return pld::State::Titlescreen;
}

void pld::Core::drawCursor(float elapsed_time, olc::vf2d pos) {

	if (animator.cursor_control < 0.4f) {
		animator.cursor_control += elapsed_time;
	} 
	else if (animator.cursor_control < 0.8f) {
		DrawDecal({ pos.x + 56 * getGlobalScale().x * level.player1.name.size(), pos.y - 5 }, dcl_text->at(0).get(), getGlobalScale());
		animator.cursor_control += elapsed_time;
	}
	else {
		animator.cursor_control = 0.0f;
	}

}