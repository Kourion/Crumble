#include "Core.h"

//#############################################################################
//# Level loop handler and level generation procedures:                       #
//#############################################################################

pld::State pld::Core::onUserUpdateLevel(float elapsed_time) {
	resetIfStateChanged();
	drawLevel(level.start);
	drawPaddle(elapsed_time);
	drawBolt(elapsed_time);
	drawImpact(elapsed_time);

	//////////////////////////////////////////////////////////
	// TODO check is this needed? Shouldnt the map auto report?
	int remaining_bricks = 0;
	for (auto& row : level.map) {
		remaining_bricks += (int)row.second.pos.size();
	}
	if (remaining_bricks == 0) {
		level.next = true;
	}
	//////////////////////////////////////////////////////////

	if (level.next) {
		level.bolt.deactivateSilently();
		level.lives = level.start_lives;
		level.impacts.clear();
		level.lvl++;
		level.start = true;
		level.levelUp = true;
		return pld::State::LevelUp;
	}

	if (level.game_over) {
		// Note:
		// In onUserUpdateHighscore() level.game_over is needed to be true.
		// Resetting level.game_over occurs in showHighscore(), 
		// when all game over cleanup is finished.

		level.lvl = 1;
		level.lives = level.start_lives;
		level.bolt.deactivateSilently();
		reportStateChange();
		return pld::State::Highscore;
	}

	if (GetKey(olc::ESCAPE).bPressed) {
		this->escaped_from_state = pld::State::Level;
		return pld::State::Settings;
	}
	return pld::State::Level;
}


void pld::Core::drawLevel(bool generateLevel) {
	updateFieldWidth(ScreenWidth());
	//int inner_field_width = level.width - (4 * tiles.size);
	//int row_one_y = 120;
	//int row_height = 20;
	//bool isGreen = true;

	std::string str = "";
	str += level.player1.name;
	str += ": Level(" + std::to_string(level.lvl) + ") Score[";
	str += std::to_string((int)level.player1.score);
	str += "] Lives(";
	str += std::to_string(level.lives);
	str += ") Score-Multiplier"; str += "{"; str += std::to_string((int)level.bolt.speed/2); str += "x}";
	DrawStringDecal({ 32, (float)(3+level.top_btm_offset) }, str, olc::Pixel(246, 198, 55), { 2.0f, 2.0f});
	
	if (generateLevel) {
#if defined(pldSOUND)
		sounds->at(4).get()->play();
#endif
		generateWallElements();
		level.start = false;
		level.next = false;
	}

	if (level.map.size() == 0) {
		level.next = true;
	}
	else {
		// Iterate through all wall elements and draw them.
		for (std::pair<const int, LevelRow>& row : level.map) {
			for (std::pair<olc::vi2d, int>& block : row.second.pos ) {
				olc::vi2d pos = block.first;
				int length = block.second;
				if(length == 1) {
					DrawDecal(pos, dcl_box->at(0).get());  //, { 1.0f, 1.0f }, olc::GREEN
				} else if (length == 2) {
					DrawDecal(pos, dcl_box->at(1).get());
					pos.x += tiles.size;
					DrawDecal(pos, dcl_box->at(3).get());
				} else {
					DrawDecal(pos, dcl_box->at(1).get());
					pos.x += tiles.size;
					length -= 2;
					for (int i = 0; i < length; i++) {
						DrawDecal(pos, dcl_box->at(2).get());
						pos.x += tiles.size;
					}
					DrawDecal(pos, dcl_box->at(3).get());
				}
			}
		}
	}
}

void pld::Core::generateWallElements() {
	level.map.clear();
	updateFieldWidth(ScreenWidth());
	int inner_field_width = level.width - (tiles.size * 4);
	int block_num__ = inner_field_width / tiles.size;
	int empty_pixel = inner_field_width % tiles.size;
	int amount_of_rows = level.lvl+ level.min_rows < level.max_rows ? level.lvl + level.min_rows : level.max_rows;
	int y_offset = 100;
	const int row_spacer = 5;
	int y_offset_max = 100 + amount_of_rows * tiles.size;
	float base_scale = 2.0f;
	for (int row_num = 0; row_num < amount_of_rows; row_num++) {
		int block_num = block_num__;
		level.map[row_num] = LevelRow();
		int x_offset = tiles.size * 2;
		y_offset = y_offset_max - (row_num * tiles.size) - (row_num * row_spacer);
		int blocks = 0;
		while (block_num > 0) {
			int block_width = random_engine(1, std::min<int>(5, block_num));
			level.map[row_num].pos.push_back( { { x_offset, y_offset }, block_width } );
			x_offset += block_width * tiles.size;
			block_num -= block_width;
			blocks++;
		}
		int empty_pixel_per_block = empty_pixel / blocks;
		int spacing_offset = empty_pixel_per_block;
		for (std::pair<olc::vi2d, int> &block : level.map[row_num].pos) {
			block.first.x += spacing_offset;
			spacing_offset += empty_pixel_per_block;
		}
	}
}
