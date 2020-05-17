#pragma once
#include "Bolt.h"
#include "LevelRow.h"
#include "Impact.h"
#include "Player.h"
#include "Paddle.h"

namespace pld {
	struct LevelState {
		int start_lives = 3;
		int lives = start_lives;
		float past_paddle_speed = 1.0f;

		int lvl = 1;
		// 4 + lvl -> thus true min = 5.
		int min_rows = 4;
		// The max lvl that changes the board. // Maybe should be calculate dynamically from screensize.
		int max_rows = 14;
		int width = 0;
		int top_btm_offset = 0;
		// Set this to !0 to force the game field to be smaller than the screen estate would allow.
		int max_width = 0;

		std::map<int, LevelRow> map;
		std::vector<int> water_tile_selector;
		std::vector<Impact> impacts;

		// State control bools:
		bool water_initialised = false;
		// Set this to true if a game just finished to reload and save highscore.
		bool game_over = false;
		// Set this to true if a level is won.
		bool next = false;
		bool start = true;

		// Objects:
		pld::Player player1;
		pld::Paddle paddle;
		pld::Bolt bolt;

		// Timers:
		float switch_timer = 0.0f;
		bool levelUp = false;
	};

	struct Tiles {
		int size = 32;
	};

	struct ScoreScreen {
		bool has_printed = false;
		bool init = false;
		std::vector<Player> presets;
		std::map<float, std::string> entries;
	};
}