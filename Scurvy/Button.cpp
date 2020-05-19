#include "Core.h"

//#############################################################################
//# Button drawing, listener and interactions:                                #
//#############################################################################

pld::State pld::Core::buttonPlay(olc::vf2d pos, olc::vf2d scale, float elapsed_time, pld::State state, int id) {
	return buttonPlay(pos, scale, elapsed_time, false, state, id);
}

pld::State pld::Core::buttonPlay(olc::vf2d pos, olc::vf2d scale, float elapsed_time, bool is_restart, pld::State state, int id) {
	int vertical_tiles = 5;
	int horizontal_tiles = is_restart ? 15 : 11;
	olc::vf2d buttonDimensions = { horizontal_tiles*tiles.size *scale.x, vertical_tiles*tiles.size *scale.y };
	
	int text = is_restart ? 13 : 5;

	if (level.player1.name.size() > 0) {
		if (GetMouseX() > pos.x && GetMouseX() < pos.x + buttonDimensions.x
			&& GetMouseY() > pos.y && GetMouseY() < pos.y + buttonDimensions.y) {

			// warp color : drawButton(pos, scale, dcl_text->at(5));
			drawButton(pos, scale, {horizontal_tiles, vertical_tiles}, dcl_text->at(text), olc::GREY, true);
			if (GetMouse(0).bPressed) {
				sounds->at(9).get()->play();
				reportStateChange();
				return pld::State::Ease;
			}
			updateSelectionSound(true, id);
		}
		else {
			drawButton(pos, scale, { horizontal_tiles, vertical_tiles }, dcl_text->at(text), olc::NONE, true);
			updateSelectionSound(false, id);
		}
	}
	else {
		// draw dark greyed out (disabled) button!
		drawButton(pos, scale, { horizontal_tiles, vertical_tiles }, dcl_text->at(text), olc::DARK_GREY, true);
	}
	return state;
}

void pld::Core::drawButton(olc::vf2d pos, olc::vf2d scale, olc::vi2d size, std::shared_ptr<olc::Decal> dcl, const olc::Pixel& tint, bool background) {
	drawButton(pos, scale, size, dcl, tint, background, true);
}

void pld::Core::drawButton(olc::vf2d pos, olc::vf2d scale, olc::vi2d size, std::shared_ptr<olc::Decal> dcl, const olc::Pixel &tint, bool background, bool text) {
	// The horizontal loop draws all corners.
	for (int i = 0; i < size.x; i++)
	{
		// 0 is full
		// 1 is right open
		// 2 is left adn right open
		// 3 is is left open
		// 4 is top and btm open
		// 5 is full 
		// 6 is full open mix
		// 7 is full open mix

		int tile = i == 0 ? 7 : i == size.x - 1 ? 7 : 2;
		if (tint == olc::NONE) {
			DrawDecal({ pos.x + i * tiles.size * scale.x, pos.y }, dcl_box->at(tile).get(), scale);
			DrawDecal({ pos.x + i * tiles.size * scale.x, pos.y + (size.y - 1) * tiles.size * scale.y }, dcl_box->at(tile).get(), scale);
		}
		else {
			DrawDecal({ pos.x + i * tiles.size * scale.x, pos.y }, dcl_box->at(tile).get(), scale, tint);
			DrawDecal({ pos.x + i * tiles.size * scale.x, pos.y + (size.y - 1) * tiles.size * scale.y }, dcl_box->at(tile).get(), scale, tint);
		}
	}
	// The horizontal loop draws no corners.
	for (int i = 1; i < size.y-1; i++)
	{
		int tile = 4;
		if (tint == olc::NONE) {
			DrawDecal({ pos.x, pos.y + i * tiles.size * scale.y }, dcl_box->at(tile).get(), scale);
			DrawDecal({ pos.x + (size.x - 1) * tiles.size * scale.x, pos.y + i * tiles.size * scale.y }, dcl_box->at(tile).get(), scale);
		}
		else {
			DrawDecal({ pos.x, pos.y + i * tiles.size * scale.y }, dcl_box->at(tile).get(), scale, tint);
			DrawDecal({ pos.x + (size.x - 1) * tiles.size * scale.x, pos.y + i * tiles.size * scale.y }, dcl_box->at(tile).get(), scale, tint);
		}
		if (background) {
			for (int j = 1; j < size.x - 1; j++) {
				tile = 6;
				if (tint == olc::NONE) {
					DrawDecal({ pos.x + j * tiles.size * scale.x, pos.y + i * tiles.size * scale.y }, dcl_box->at(tile).get(), scale);
					//FillRect({ (int)(pos.x + j * tile_size * scale.x), (int)(pos.y + i * tile_size * scale.y) }, {16, 16}, olc::BLACK);
				}
				else {
					DrawDecal({ pos.x + j * tiles.size * scale.x, pos.y + i * tiles.size * scale.y }, dcl_box->at(tile).get(), scale, tint);
				}
			}
		}
	}
	if (text) {
		int corner_offset = 2;
		if (tint == olc::NONE) {
			DrawDecal({ pos.x + corner_offset + tiles.size * scale.x, pos.y + corner_offset + tiles.size * scale.y }, dcl.get(), scale);
		}
		else {
			DrawDecal({ pos.x + corner_offset + tiles.size * scale.x , pos.y + corner_offset + tiles.size * scale.y }, dcl.get(), scale, tint);
		}
	}

	//DrawDecal(const olc::vf2d & pos, olc::Decal * decal, const olc::vf2d & scale, const olc::Pixel & tint)
}

pld::State pld::Core::buttonRestart(olc::vf2d pos, olc::vf2d scale, float elapsed_time, pld::State state, int id) {
	return buttonPlay(pos, scale, elapsed_time, true, state, id);
}

pld::State pld::Core::buttonResign(olc::vf2d pos, olc::vf2d scale, float elapsed_time, pld::State state, int id) {
	int vertical_tiles = 5;
	int horizontal_tiles = 15;
	olc::vf2d buttonDimensions = { horizontal_tiles * tiles.size * scale.x, vertical_tiles * tiles.size * scale.y };

	if (GetMouseX() > pos.x && GetMouseX() < pos.x + buttonDimensions.x
		&& GetMouseY() > pos.y && GetMouseY() < pos.y + buttonDimensions.y) {

		// warp color : drawButton(pos, scale, dcl_text->at(5));
		drawButton(pos, scale, { horizontal_tiles, vertical_tiles }, dcl_text->at(12), olc::GREY, true);
		if (GetMouse(0).bPressed) {
			sounds->at(9).get()->play();
			level.bolt.deactivateSilently();
			reportStateChange();
			return pld::State::Titlescreen;
		}
		updateSelectionSound(true, id);
	}
	else {
		drawButton(pos, scale, { horizontal_tiles, vertical_tiles }, dcl_text->at(12), olc::NONE, true);
		updateSelectionSound(false, id);
	}
	return state;
}

pld::State pld::Core::buttonQuit(olc::vf2d pos, olc::vf2d scale, float elapsed_time, pld::State state, int id) {
	int vertical_tiles = 5;
	int horizontal_tiles = 11;
	olc::vf2d buttonDimensions = { horizontal_tiles * tiles.size * scale.x, vertical_tiles * tiles.size * scale.y };

	if (GetMouseX() > pos.x && GetMouseX() < pos.x + buttonDimensions.x
		&& GetMouseY() > pos.y && GetMouseY() < pos.y + buttonDimensions.y) {

		// warp color : drawButton(pos, scale, dcl_text->at(5));
		drawButton(pos, scale, { horizontal_tiles, vertical_tiles }, dcl_text->at(6), olc::GREY, true);
		if (GetMouse(0).bPressed) {
			sounds->at(9).get()->play();
			OnUserDestroy();
			//exit(EXIT_SUCCESS);
			load_next_frame = false;
			return state;
		}
		updateSelectionSound(true, id);
	}
	else {
		drawButton(pos, scale, { horizontal_tiles, vertical_tiles }, dcl_text->at(6), olc::NONE, true);
		updateSelectionSound(false, id);
	}
	return state;
}

pld::State pld::Core::buttonHighscore(olc::vf2d pos, olc::vf2d scale, float elapsed_time, pld::State state, int id) {
	int vertical_tiles = 5;
	int horizontal_tiles = 19;
	olc::vf2d buttonDimensions = { horizontal_tiles * tiles.size * scale.x, vertical_tiles * tiles.size * scale.y };

	if (GetMouseX() > pos.x && GetMouseX() < pos.x + buttonDimensions.x
		&& GetMouseY() > pos.y && GetMouseY() < pos.y + buttonDimensions.y) {

		// warp color : drawButton(pos, scale, dcl_text->at(5));
		drawButton(pos, scale, { horizontal_tiles, vertical_tiles }, dcl_text->at(7), olc::GREY, true);
		if (GetMouse(0).bPressed) {
			sounds->at(9).get()->play();
			if (level.player1.name.size() == 0) {
				level.player1.name = "THE FOOL";
			}
			return pld::State::Highscore;
		}
		updateSelectionSound(true, id);
	}
	else {
		drawButton(pos, scale, { horizontal_tiles, vertical_tiles }, dcl_text->at(7), olc::NONE, true);
		updateSelectionSound(false, id);
	}
	return state;
}

pld::State pld::Core::buttonEase(olc::vf2d pos, olc::vf2d scale, float elapsed_time, pld::Ease ease, pld::State state, int id) {
	int vertical_tiles = 5;
	int horizontal_tiles = ease == Ease::Normal ? 15 : ease == Ease::Hard ? 11 : 26; // Last one is Ease::BoR.
	olc::vf2d buttonDimensions = { horizontal_tiles * tiles.size * scale.x, vertical_tiles * tiles.size * scale.y };

	int text = ease == Ease::Normal ? 8 : ease == Ease::Hard ? 9 : 10; // Last one is Ease::BoR.
	if (GetMouseX() > pos.x && GetMouseX() < pos.x + buttonDimensions.x
		&& GetMouseY() > pos.y && GetMouseY() < pos.y + buttonDimensions.y) {
		updateSelectionSound(true, id);
		
		// warp color : drawButton(pos, scale, dcl_text->at(5));
		drawButton(pos, scale, { horizontal_tiles, vertical_tiles }, dcl_text->at(text), olc::GREY, true);
		if (GetMouse(0).bPressed) {
			sounds->at(9).get()->play();
			this->ease = ease;
			// state change broadcast needed?
			return pld::State::Level;
		}
	}
	else {
		drawButton(pos, scale, { horizontal_tiles, vertical_tiles }, dcl_text->at(text), olc::NONE, true);
		updateSelectionSound(false, id);
	}
	return state;
}

void pld::Core::updateSelectionSound(bool selected, int id) {
#if defined (pldSOUND)	
	if (selected) {
		if (button.selected[id] == false) {
			button.selected[id] = true;
			sounds->at(10).get()->play();
		}
	}
	else {
		if (button.selected[id]) {
			button.selected[id] = false;
		}
	}
#endif
}