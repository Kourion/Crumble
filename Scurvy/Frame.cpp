#include "Core.h"

//#############################################################################
//# Game frame and menu frame functions:                                      #
//#############################################################################


void pld::Core::drawSpriteBorder() {
	updateFieldWidth(ScreenWidth());
	int top_bottom_offset = (ScreenHeight() % tiles.size) / 2;
	int vertical_tiles = (ScreenHeight() / tiles.size);

	for (int i = 1; i < vertical_tiles - 1; i++) {
		DrawSprite({ 0, top_bottom_offset + i * tiles.size }, spr_border->at(1).get());
		DrawSprite({ (int)(level.width - tiles.size), top_bottom_offset + i * tiles.size }, spr_border->at(5).get());
	}
	for (int i = 1; i < (level.width / tiles.size) - 1; i++) {
		DrawSprite({ i * tiles.size, top_bottom_offset }, spr_border->at(3).get());
	}
	DrawSprite({ 0, top_bottom_offset + (vertical_tiles - 1) * tiles.size }, spr_border->at(8).get());
	DrawSprite({ 0, top_bottom_offset }, spr_border->at(2).get());
	DrawSprite({ (int)(level.width - tiles.size), top_bottom_offset }, spr_border->at(4).get());
	DrawSprite({ (int)(level.width - tiles.size), (int)(top_bottom_offset + (vertical_tiles - 1) * tiles.size) }, spr_border->at(7).get());
	level.top_btm_offset = top_bottom_offset;
}

void pld::Core::initWaterTiles() {
	updateFieldWidth(ScreenWidth());
	//std::cout << "s: (" << random_engine.isInit() << ") -> ";
	for (int i = 0; i < (level.width / tiles.size) - 2; i++) {
		int select = random_engine(3, 4);
		//std::cout << select << ", ";
		level.water_tile_selector.push_back(select);
	}
	//std::cout << std::endl;
}

// DEPRECATED: Use drawWaterBottomSprite() instead.
void pld::Core::drawWaterBottomDecal(float elapsed_time) {
	updateFieldWidth(ScreenWidth());
	if (!level.water_initialised) {
		initWaterTiles();
		level.water_initialised = true;
	}
	int top_bottom_offset = (ScreenHeight() % tiles.size) / 2;
	int vertical_tiles = (ScreenHeight() / tiles.size);
	int horizontal_tiles = (int)(level.width / tiles.size);
	int select = 0;
	float offset_y = (float)(top_bottom_offset + (vertical_tiles - 1) * tiles.size);
	DrawDecal({ (float)(1 * tiles.size),  offset_y }, dcl_water->at(1).get());
	DrawDecal({ (float)((horizontal_tiles - 2) * tiles.size),  offset_y }, dcl_water->at(0).get());
	for (int j = 2; j < (level.width / tiles.size) - 2; j++) {
		int i = j - 1;
		DrawDecal({ (float)(j * tiles.size), offset_y }, dcl_water->at(level.water_tile_selector[i]).get());
	}
	level.paddle.base_pos.x = (float)(level.width / 2);
	level.paddle.base_pos.y = offset_y;
}

void pld::Core::drawWaterBottomSprite() {
	updateFieldWidth(ScreenWidth());
	if (!level.water_initialised) {
		initWaterTiles();
		level.water_initialised = true;
	}
	int top_bottom_offset = (ScreenHeight() % tiles.size) / 2;
	int vertical_tiles = (ScreenHeight() / tiles.size);
	int horizontal_tiles = (level.width / tiles.size);
	int select = 0;
	int offset_y = (top_bottom_offset + (vertical_tiles - 1) * tiles.size);
	DrawSprite({ (1 * tiles.size),  offset_y }, spr_water->at(1).get());
	DrawSprite({ ((horizontal_tiles - 2) * tiles.size),  offset_y }, spr_water->at(0).get());
	for (int j = 2; j < (level.width / tiles.size) - 2; j++) {
		int i = j - 1;
		DrawSprite({ (j * tiles.size), offset_y }, spr_water->at(level.water_tile_selector[i]).get());
	}
	level.paddle.base_pos.x = (float)(level.width / 2);
	level.paddle.base_pos.y = (float)offset_y;
}

/*
// Deprecated
void pld::Core::drawPixelBorder() {
	updateFieldWidth(ScreenWidth());
	for (int i = 0; i < ScreenHeight() / tiles.border_width_half; i++) {
		if (i % 2 == 0) {
			FillRect(0, i * tiles.border_width_half, tiles.border_width_half, tiles.border_width_half, olc::Pixel(olc::YELLOW));
			FillRect((int32_t)(level.field_width - tiles.border_width), i * tiles.border_width_half,
				tiles.border_width_half, tiles.border_width_half, olc::Pixel(olc::YELLOW));
		}
		else {
			FillRect(tiles.border_width_half, i * border_width_half, border_width_half, border_width_half, olc::Pixel(olc::YELLOW));
			FillRect((int32_t)(field_width - border_width_half), i * border_width_half, border_width_half, border_width_half, olc::Pixel(olc::YELLOW));
		}
	}
	for (int i = 2; i < (field_width - border_width_half) / border_width_half; i++) {
		if (i % 2 == 0) {
			FillRect(i * border_width_half, 0, border_width_half, border_width_half, olc::Pixel(olc::YELLOW));
		}
		else {
			FillRect(i * border_width_half, border_width_half, border_width_half, border_width_half, olc::Pixel(olc::YELLOW));
		}
	}
}

*/