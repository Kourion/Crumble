#include "Core.h"

//#############################################################################
//# Ease-selection-screen:                                                    #
//#############################################################################

pld::State pld::Core::onUserUpdateEase(float elapsed_time) {
	pld::State next = pld::State::Ease;
	float button_tile_scale = 0.5f;
	olc::vf2d button_scale = { button_tile_scale, button_tile_scale };

	DrawDecal({ScreenWidth() / 2 - (931 / 2) * getGlobalScale().x, 
		(float)((ScreenHeight() / 2) - (18.0 * tiles.size * (double)button_tile_scale * 1.5 * getGlobalScale().y)) },
		dcl_text->at(11).get());
	
	next = buttonEase({ (float)((ScreenWidth() / 2) - (15/2 * tiles.size * (float)button_tile_scale * getGlobalScale().x)),
		(float)((ScreenHeight() / 2) - (8.0 * tiles.size * (double)button_tile_scale * 1.5 * getGlobalScale().y)) },
		button_scale, elapsed_time, Ease::Normal, next, 3);

	next = buttonEase({ (float)((ScreenWidth() / 2) - (11/2 * tiles.size * (float)button_tile_scale * getGlobalScale().x)),
		(float)((ScreenHeight() / 2) - (2.0 * tiles.size * (double)button_tile_scale * 1.5 * getGlobalScale().y)) },
		button_scale, elapsed_time, Ease::Hard, next, 4);

	next = buttonEase({ (float)((ScreenWidth() / 2) - (26/2 * tiles.size * (float)button_tile_scale * getGlobalScale().x)),
		(float)((ScreenHeight() / 2) + (4.0 * tiles.size * (double)button_tile_scale * 1.5 * getGlobalScale().y)) },
		button_scale, elapsed_time, Ease::BoR, next, 5);

	return next;
}