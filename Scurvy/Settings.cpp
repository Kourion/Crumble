#include "Core.h"

//#############################################################################
//# Settings screen and its interactions:                                     #
//#############################################################################

// MEDO: SETTINGS SCREEN!

pld::State pld::Core::onUserUpdateSettings(float elapsed_time) {
	pld::State next = pld::State::Settings;
	olc::vf2d title_text_pos((float)(ScreenWidth() / 2 - 331.5 * getGlobalScale().x), (float)(48*getGlobalScale().y));
	DrawDecal(title_text_pos, dcl_text->at(1).get(), getGlobalScale());
	std::string menu_title = "Settings";
	olc::vf2d menu_pos((float)(ScreenWidth() / 2 - 331.5 * getGlobalScale().x), (float)(280 * getGlobalScale().y));
	//DrawStringDecal(menu_title_pos, menu_title, olc::YELLOW, { 10.0f, 10.0f } );
	drawButton(menu_pos, {0.5f, 0.5f}, {(int)(42*getGlobalScale().x), (int)(44*(getGlobalScale().y))},
		dcl_text->at(4), olc::NONE, false, false);

	next = buttonResign({ ScreenWidth() / 2 - 4 *tiles.size * getGlobalScale().x,
		ScreenHeight() / 2 - 2 * tiles.size * getGlobalScale().y }, { 0.5f, 0.5f }, elapsed_time, next);

	if (GetKey(olc::ESCAPE).bPressed) {
		return escaped_from_state;
	}
	if (GetKey(olc::X).bPressed) {
		level.bolt.deactivateSilently();
		reportStateChange();
		return pld::State::Titlescreen;
	}
	if (GetKey(olc::T).bPressed) {
		reportStateChange();
		return pld::State::Titlescreen;
	}
	if (GetKey(olc::H).bPressed) {
		if (level.player1.name.size() == 0) {
			level.player1.name = "THE FOOL";
		}
		return pld::State::Highscore;
	}
	return next;
}

void pld::Core::drawMenuBorder() {

}