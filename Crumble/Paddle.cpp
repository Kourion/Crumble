#include "Core.h"

//#############################################################################
//# Paddle functions:                                                         #
//#############################################################################

void pld::Core::drawPaddle(float elapsed_time) {
	float base_speed = 500.0f;
	bool moving = false;
	int num = level.paddle.num; //Change paddle vesion.
	if (GetKey(olc::A).bHeld) { updatePaddleOffsetX(-base_speed, elapsed_time, num); moving = true; }
	if (GetKey(olc::D).bHeld) { updatePaddleOffsetX(base_speed, elapsed_time, num); moving = true; }
	if (GetKey(olc::LEFT).bHeld) { updatePaddleOffsetX(-base_speed, elapsed_time, num); moving = true; }
	if (GetKey(olc::RIGHT).bHeld) { updatePaddleOffsetX(base_speed, elapsed_time, num); moving = true; }
	DrawDecal(level.paddle.getPos(), dcl_paddle->at(num).get());
	if (level.paddle.speed != 0.0 && !moving) { level.paddle.speed = 0; }
}

void pld::Core::updatePaddleOffsetX(float base_speed, float elapsed_time, int num) {
	updateFieldWidth(ScreenWidth());
	// MEDO: Add random paddle speed as difficulty effect?
	if (level.paddle.speed > 0 && base_speed > 0) {
		level.paddle.speed += base_speed * 3 * elapsed_time;
	}
	else if (level.paddle.speed < 0 && base_speed < 0) {
		level.paddle.speed += base_speed * 3 * elapsed_time;
	}
	else {
		level.paddle.speed = base_speed * 3 * elapsed_time;
	}
	if (level.paddle.speed > 250.0f) {
		level.paddle.speed = 250.0f;
	}
	else if (level.paddle.speed < -250.0f) {
		level.paddle.speed = -250.0f;
	}
	level.past_paddle_speed = level.paddle.speed;
	float paddle_speed = (base_speed + level.paddle.speed) * 3 * elapsed_time /* random_engine(1, 5)*/;
	float max_offset = (float)((level.width - 2 * tiles.size) / 2);
	if (paddle_speed > 0) {
		if ((level.paddle.offset + paddle_speed) < (max_offset - level.paddle.width[num]/2)) {
			level.paddle.offset += paddle_speed;
		}
		else {
			level.paddle.offset = max_offset - level.paddle.width[num]/2;
		}
	}
	else if (paddle_speed < 0) {
		if ((level.paddle.offset + paddle_speed) > (-max_offset + level.paddle.width[num] / 2)) {
			level.paddle.offset += paddle_speed;
		}
		else {
			level.paddle.offset = -max_offset + level.paddle.width[num] / 2;
		}
	}
}
