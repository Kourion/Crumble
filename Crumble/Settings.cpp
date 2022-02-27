#include "Core.h"

//#############################################################################
//# Settings screen and its interactions:                                     #
//#############################################################################

// MEDO: SETTINGS SCREEN!

pld::State pld::Core::onUserUpdateSettings(float elapsed_time) {
	pld::State next = pld::State::Settings;
	olc::vf2d title_text_pos((float)(ScreenWidth() / 2 - 331.5 * getGlobalScale().x), (float)(48*getGlobalScale().y));
	DrawDecal(title_text_pos, dcl_text->at(1).get(), getGlobalScale());

	{
		/// Drawing text "Settings" directly to screen. (Deprecated, drawing as decal below.)
		// std::string menu_title = "Settings";
		// DrawStringDecal(menu_title_pos, menu_title, olc::YELLOW, { 10.0f, 10.0f } );
	}
	{
		/// Drawing border arounds settings menu. (Dprecated for now, as its kinda ugly.)
		// olc::vf2d menu_pos((float)(ScreenWidth() / 2 - 331.5 * getGlobalScale().x), (float)(280 * getGlobalScale().y));
		// drawButton(menu_pos, { 0.5f, 0.5f }, { (int)(42 * getGlobalScale().x), (int)(44 * (getGlobalScale().y)) },
		//	 dcl_text->at(4), olc::NONE, false, false);
	}
	
	if (escaped_from_state == pld::State::Level) {
		next = buttonResign({ ScreenWidth() / 2 - 4 *tiles.size * getGlobalScale().x,
			ScreenHeight() / 2 - 2 * tiles.size * getGlobalScale().y }, { 0.5f, 0.5f }, elapsed_time, next, 8);
		
	} else {
		const auto align_y = title_text_pos.y + ((50 + 140) * getGlobalScale().y);
		const auto hsc_txt_pos = olc::vf2d(ScreenWidth() / 2 - (447 / 2) * getGlobalScale().x, align_y);
		//447x90
		DrawDecal(hsc_txt_pos, dcl_text->at(4).get(), getGlobalScale());
	}

	if (GetKey(olc::ESCAPE).bPressed) {
		return escaped_from_state;
	}
	if (GetKey(olc::X).bPressed) {
		level.bolt.deactivateSilently();
		reportStateChange();
		return pld::State::Titlescreen;
	}
	if (GetKey(olc::L).bPressed) {
		level.lives++;
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