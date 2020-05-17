#include "Core.h"

//#############################################################################
//# General core functions, and thread loop handler:                          #
//#############################################################################

bool pld::Core::OnUserCreate() {
	initVfx();
	loadSpritesAndDecals();
	setPresets();
	reportStateChange();
	this->state = pld::State::Titlescreen;
	return true;
}

bool pld::Core::OnUserUpdate(float elapsed_time) {
	switch (state) {
		case pld::State::Titlescreen:
			state = onUserUpdateTitlescreen(elapsed_time); break;
		case pld::State::Level:
			state = onUserUpdateLevel(elapsed_time); break;
		case pld::State::LevelUp:
			state = onUserUpdateLevelUp(elapsed_time); break;
		case pld::State::Highscore:
			state = onUserUpdateHighscore(elapsed_time); break;
		case pld::State::Settings:
			state = onUserUpdateSettings(elapsed_time); break;
		case pld::State::Ease:
			state = onUserUpdateEase(elapsed_time); break;
		default:
			state = pld::State::Titlescreen; break;
	}
	return scurvy;
}

void pld::Core::reportStateChange(bool set_to) {
	this->state_changed = set_to;
}

void pld::Core::resetIfStateChanged() {
	if (state_changed) {
		Clear(olc::BLACK);
		if (state == pld::State::Titlescreen) {
			level.impacts.clear();
			DrawSprite({ 0, 0 }, spr_background.get());
#if defined(pldSOUND)
			sounds->at(0).get()->run();
#endif
			//drawSpriteBorder();
		}
		if (state == pld::State::Highscore) {
			// MEOD add highscore music
		}
		if (state == pld::State::Level) {
#if defined(pldSOUND)
			sounds->at(0).get()->stop();
#endif
			level.player1.points.flt = 0.0f;
			level.bolt.speed = 0.0f;
			level.impacts.clear();
			level.start = true;
			level.bolt.is_launched = false;
			level.lvl = 1; // MEDO: Set back to 1.
			level.lives = level.start_lives;
			drawSpriteBorder();
			drawWaterBottomSprite();
		}
		// MEDO: put in? drawSpriteBorder();
		this->state_changed = false;
	}
}

void pld::Core::updateFieldWidth(int screen_width) {
	if (level.max_width != 0.0) {
		level.width = level.max_width;
	} else {
		level.width = screen_width;
	}
}

olc::vf2d pld::Core::getGlobalScale() {
	double scale_x = (1.0 / (1080.0 / (double)ScreenHeight()));
	double scale_y = (1.0 / (1920.0 / (double)ScreenWidth()));
	return { (float)scale_x, (float)scale_y };
}

void pld::Core::drawImpact(float elapsed_time) {
	if (level.impacts.size() > 0) {
		//std::vector<Impact> to_be_deleted;
		//int loc = 0;
		for (Impact& imp : level.impacts) {
			if (imp.sprite < 9) {
				DrawDecal(imp.pos, dcl_impact->at(imp.sprite).get());
			}
			imp.frames += elapsed_time;
			if (imp.frames > 0.1f) {
				imp.sprite++;
				imp.frames = 0;
			}
			if (imp.sprite >= 9) {
				imp.to_be_deleted = true;
			}
			//loc++;
		}
		//for (auto& tbd : to_be_deleted) {
		//	if (impacts.find(tbd) != impacts.end) {
		//		impacts.erase(tbd);
		//	}
		//}
		//impacts.erase(std::remove(impacts.begin(), impacts.end(), [](const pld::Impact& imp){ return imp.to_be_deleted; }), impacts.end());
	}
}

void pld::Core::drawImpact(olc::vf2d pos) {
	// Adjust pos for sprite size.
	//impacts.push_back(Impact({ pos.x - 50 - bolt.scaled_radius/2, pos.y - 50 - bolt.scaled_radius/2}));
	// Adjust pos for brick sprite:
	level.impacts.push_back(Impact({ pos.x - 50, pos.y - 50 }));
}

void pld::Core::setPresets() {
	score.init = true;
	score.presets.push_back(Player(7000.0f, "THE FOOL"));
	score.presets.push_back(Player(14000.0f, "THE PARROT"));
	score.presets.push_back(Player(27000.0f, "THE COOK"));
	score.presets.push_back(Player(33000.0f, "THE DECKHAND"));
	score.presets.push_back(Player(39000.0f, "THE CANNONEER"));
	score.presets.push_back(Player(45000.0f, "THE LOOKOUT"));
	score.presets.push_back(Player(60000.0f, "THE NAVIGATOR"));
	score.presets.push_back(Player(70000.0f, "THE BOATSWAIN"));
	score.presets.push_back(Player(80000.0f, "THE HELMSMAN"));
	score.presets.push_back(Player(99003.0f, "THE CAPTAIN"));
	/*
	presets.push_back(Player(7000.0f, "The Fool"));
	presets.push_back(Player(14000.0f, "The Parrot"));
	presets.push_back(Player(27000.0f, "The Cook"));
	presets.push_back(Player(33000.0f, "The Deckhand"));
	presets.push_back(Player(39000.0f, "The Cannoneer"));
	presets.push_back(Player(45000.0f, "The Lookout"));
	presets.push_back(Player(60000.0f, "The Navigator"));
	presets.push_back(Player(70000.0f, "The Boatswain"));
	presets.push_back(Player(80000.0f, "The Helmsman"));
	presets.push_back(Player(99003.0f, "The Captain"));
	*/
}

bool pld::Core::OnUserDestroy() {
	std::cout << "OnUserDestroy called!" << std::endl;
#if defined(pldSOUND)
	for (int i = 0; i < vfx_num; ++i) {
		sounds->at(i).get()->destroy();
	}
	// Uninitialize COM
	::CoUninitialize();
#endif
	return true;
}