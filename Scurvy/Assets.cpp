#include "Core.h"

//#############################################################################
//# Sprites and Decals functions:                                             #
//#############################################################################

void pld::Core::loadSpritesAndDecals() {
	this->spr_title = std::unique_ptr<olc::Sprite>(new olc::Sprite("./Graphics/scurvy_alpha.png"));
	this->dcl_title = std::unique_ptr<olc::Decal>(new olc::Decal(spr_title.get()));
	this->spr_background = std::unique_ptr<olc::Sprite>(new olc::Sprite("./Graphics/pirate_2.png"));
	for (int64_t i = 0; i < 14; i++) {
		// Loop length needs to always match the vector having the most elements.
		if (i < 10) { this->spr_border->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Graphics/border_" + std::to_string(i) + ".png"))); }
		if (i < 5) {
			this->spr_water->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Graphics/water_" + std::to_string(i) + ".png")));
			this->dcl_water->push_back(std::shared_ptr<olc::Decal>(new olc::Decal(spr_water->at(i).get())));
		}
		if (i < 4) {
			this->spr_coin->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Graphics/coin_" + std::to_string(i) + ".png")));
			this->dcl_coin->push_back(std::shared_ptr<olc::Decal>(new olc::Decal(spr_coin->at(i).get())));
		}
		if (i < 8) {
			this->spr_box->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Graphics/box_" + std::to_string(i) + ".png")));
			this->dcl_box->push_back(std::shared_ptr<olc::Decal>(new olc::Decal(spr_box->at(i).get())));
		}
		if (i < 4) {
			this->spr_paddle->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Graphics/paddle_" + std::to_string(i) + ".png")));
			this->dcl_paddle->push_back(std::shared_ptr<olc::Decal>(new olc::Decal(spr_paddle->at(i).get())));
			int width = 32;
			if (i == 0) {
				level.paddle.width[0] = width;
			}
			else {
				width = level.paddle.width[(i - 1)] * 2;
				level.paddle.width.push_back(width);
			}
		}
		if (i < 6) {
			this->spr_bolt->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Graphics/bolt_alpha_" + std::to_string(i) + ".png")));
			this->dcl_bolt->push_back(std::shared_ptr<olc::Decal>(new olc::Decal(spr_bolt->at(i).get())));
		}
		if (i < 9) {
			this->spr_splash->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Graphics/splash_" + std::to_string(i) + ".png")));
			this->dcl_splash->push_back(std::shared_ptr<olc::Decal>(new olc::Decal(spr_splash->at(i).get())));
		}
		if (i < 9) {
			this->spr_impact->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Graphics/impact_" + std::to_string(i) + ".png")));
			this->dcl_impact->push_back(std::shared_ptr<olc::Decal>(new olc::Decal(spr_impact->at(i).get())));
		}
		if (i < 14) {
			if (i == 0) { this->spr_text->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Text/cursor_" + std::to_string(i) + ".png"))); }
			if (i == 1) { this->spr_text->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Text/title.png"))); }
			if (i == 2) { this->spr_text->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Text/sail_as_captain.png"))); }
			if (i == 3) { this->spr_text->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Text/highscore.png"))); }
			if (i == 4) { this->spr_text->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Text/settings.png"))); }
			if (i == 5) { this->spr_text->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Text/play.png"))); }
			if (i == 6) { this->spr_text->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Text/quit.png"))); }
			if (i == 7) { this->spr_text->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Text/highscore.png"))); }
			if (i == 8) { this->spr_text->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Text/normal.png"))); }
			if (i == 9) { this->spr_text->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Text/hard.png"))); }
			if (i == 10) { this->spr_text->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Text/bottle_of_rum.png"))); }
			if (i == 11) { this->spr_text->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Text/choose_difficulty.png"))); }
			if (i == 12) { this->spr_text->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Text/resign.png"))); }
			if (i == 13) { this->spr_text->push_back(std::shared_ptr<olc::Sprite>(new olc::Sprite("./Text/again.png"))); } //restart
			this->dcl_text->push_back(std::shared_ptr<olc::Decal>(new olc::Decal(spr_text->at(i).get())));
		}
	}
}

#if defined(pldSOUND)
void pld::Core::loadVfx() {
	//std::wstring mp3path = L"./music_0.mp3";
	for (int i = 0; i < vfx_num; i++)
	{
		sounds->push_back(std::shared_ptr<Sound>(new Sound));
	}
	int status = 0;
	if (sounds->at(0).get()->load(L"./Vfx/music.mp3")) { ++status; }
	if (sounds->at(1).get()->load(L"./Vfx/splash.mp3")) { ++status; }
	if (sounds->at(2).get()->load(L"./Vfx/chop.mp3")) { ++status; }
	if (sounds->at(3).get()->load(L"./Vfx/crack.mp3")) { ++status; }
	if (status != vfx_num) {
		std::cerr << "VFX load failure!" << std::endl;
	}
}
#endif