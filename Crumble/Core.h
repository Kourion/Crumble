#pragma once

//#############################################################################
//# The Core class, handles main loop, data, and executes the procedures:     #
//#############################################################################

#define pldSOUND

#if defined(pldSOUND)
#include "Sound.h"
#endif //if defined(pldSOUND)

#include "Engine.h"
#include "Enum.h"
#include "Random.h"
#include "LevelRow.h"
#include "Paddle.h"
#include "Bolt.h"
#include "Impact.h"
#include "Player.h"
#include "Animator.h"
#include "State.h"

namespace pld {

class Core : public olc::PixelGameEngine
{
private:
	// Data Containers:
	pld::Tiles tiles;
	pld::LevelState level;
	pld::ScoreScreen score;
	pld::Animator animator;
	pld::ButtonState button;

	// Variables:
	pld::Random random_engine = { 100 };
	pld::State state;
	pld::State escaped_from_state;
	pld::Ease ease;

	bool state_changed = false;
	bool load_next_frame = true;
public:
	bool restart = false;
public:
	// Engine Call Implementation:
	Core() {
		this->tiles = Tiles();
		this->level = LevelState();
		this->score = ScoreScreen();
		this->button = ButtonState();
		sAppName = "Crumble";
	}
	bool OnUserCreate() override;
	bool OnUserUpdate(float elapsed_time) override;
	bool OnUserDestroy();
private:
	// Internal procedures:
	olc::vf2d getGlobalScale();
	std::string getScoreEntry(int i, float points, std::string name);
	CollisionType willCollide(olc::vf2d expected_pos);
	State onUserUpdateTitlescreen(float elapsed_time);
	State onUserUpdateLevel(float elapsed_time);
	State onUserUpdateHighscore(float elapsed_time);
	State onUserUpdateSettings(float elapsed_time);
	State onUserUpdateEase(float elapsed_time);
	State onUserUpdateLevelUp(float elapsed_time);
	State showHighscore(float elapsed_time);
	State inputListenerTitlescreen(float elapsed_time);
	State buttonPlay(olc::vf2d pos, olc::vf2d scale, float elapsed_time, pld::State state, int id);
	State buttonPlay(olc::vf2d pos, olc::vf2d scale, float elapsed_time, bool is_restart, pld::State state, int id);
	State buttonRestart(olc::vf2d pos, olc::vf2d scale, float elapsed_time, pld::State state, int id);
	State buttonResign(olc::vf2d pos, olc::vf2d scale, float elapsed_time, pld::State state, int id);
	State buttonQuit(olc::vf2d pos, olc::vf2d scale, float elapsed_time, pld::State state, int id);
	State buttonHighscore(olc::vf2d pos, olc::vf2d scale, float elapsed_time, pld::State state, int id);
	State buttonEase(olc::vf2d pos, olc::vf2d scale, float elapsed_time, pld::Ease ease, pld::State state, int id);
	void drawButton(olc::vf2d pos, olc::vf2d scale, olc::vi2d size, std::shared_ptr<olc::Decal> dcl, const olc::Pixel &tint, bool background);
	void drawButton(olc::vf2d pos, olc::vf2d scale, olc::vi2d size, std::shared_ptr<olc::Decal> dcl, const olc::Pixel& tint, bool background, bool text);
	void setPresets();
	void loadSpritesAndDecals();
	void drawSpriteBorder();
	void drawWaterBottomDecal(float elapsed_time);
	void drawMenuBorder();
	void drawWaterBottomSprite();
	void reportStateChange(bool set_to = true);
	void resetIfStateChanged();
	void loadHighscorePresets();
	void updateFieldWidth(int screen_width);
	void drawPaddle(float elapsed_time);
	void drawBolt(float elapsed_time);
	void drawLevel(bool level_start);
	void drawCursor(float elapsed_time, olc::vf2d pos);
	void drawBoltDestruction(float elapsed_time);
	void generateWallElements();
	void initWaterTiles();
	void ensureBoltWithinBounds();
	void updatePaddleOffsetX(float paddle_speed, float elapsed_time, int num);
	void updateBolt(float elapsed_time);
	void updateBolt(float elapsed_time, pld::Directions up_down, pld::Directions left_right);
	void drawImpact(olc::vf2d pos);
	void drawImpact(float elapsed_time);
	void updateSelectionSound(bool selected, int id);
	void initVfx();
	void loadVfx();
	void updateDeviation();
	void initButtons();
private:
	// MEDO: Put together with Vfx, into Assets.h
	// Sprites and Decals:
	std::unique_ptr<olc::Sprite> spr_title; 
	std::unique_ptr<olc::Decal> dcl_title;
	std::unique_ptr<olc::Sprite> spr_background;
	std::unique_ptr<olc::Sprite> spr_highscore;
	std::vector< std::shared_ptr<olc::Sprite> > spr_text[14];
	std::vector< std::shared_ptr<olc::Decal> > dcl_text[14];
	std::vector< std::shared_ptr<olc::Sprite> > spr_water[5];
	std::vector< std::shared_ptr<olc::Decal> > dcl_water[5];
	std::vector< std::shared_ptr<olc::Sprite> > spr_border[10];
	std::vector< std::shared_ptr<olc::Sprite> > spr_coin[4];
	std::vector< std::shared_ptr<olc::Decal> > dcl_coin[4];
	std::vector< std::shared_ptr<olc::Sprite> > spr_box[8];
	std::vector< std::shared_ptr<olc::Decal> > dcl_box[8];
	std::vector< std::shared_ptr<olc::Sprite> > spr_splash[9];
	std::vector< std::shared_ptr<olc::Decal> > dcl_splash[9];
	std::vector< std::shared_ptr<olc::Sprite> > spr_paddle[4];
	std::vector< std::shared_ptr<olc::Decal> > dcl_paddle[4];
	std::vector< std::shared_ptr<olc::Sprite> > spr_bolt[6];
	std::vector< std::shared_ptr<olc::Decal> > dcl_bolt[6];
	std::vector< std::shared_ptr<olc::Sprite> > spr_impact[9];
	std::vector< std::shared_ptr<olc::Decal> > dcl_impact[9];
#if defined(pldSOUND)
	std::vector< std::shared_ptr<Sound> > sounds[11];
	const int vfx_num = 12;
#endif
};
}
