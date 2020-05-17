#include "Bolt.h"
#include "Core.h"

//#############################################################################
//# Bolt functions of Bolt class and bolt functions of Core class.            #
//#############################################################################


//#############################################################################
//# Bolt functions of Bolt class:                                             #
//#############################################################################

void pld::Bolt::switchLeftRight() {
	left_right = (left_right == pld::Directions::Left) ? pld::Directions::Right : pld::Directions::Left;
}

void pld::Bolt::switchUpDown() {
	up_down = up_down == pld::Directions::Up ? pld::Directions::Down : pld::Directions::Up;
}

void pld::Bolt::updateDirection(pld::CollisionType collision) {
	switch (collision) {
		// Case Water, no update needed, bolt should be destroyed on contact!
	case CollisionType::Paddle: // Flat paddle == floor, other paddles need specific behaviour.
	case CollisionType::Ceiling:
	case CollisionType::Floor:	// Real floor, not water!
		switchUpDown();
		break;
	case CollisionType::Wall:
	case CollisionType::WallLeft:
	case CollisionType::WallRight:
		switchLeftRight();
		break;
	case CollisionType::BoxTop: // Top and Bottom.
		switchUpDown();
		break;
	case CollisionType::BoxSide: // Left and Right.
		switchLeftRight();
		break;
	default:
		break;
	}
}

int pld::Bolt::chooseDecal() {
	int select = 0;
	if (up_down == pld::Directions::Stationary) {
		return 0;
	}
	select = (up_down == pld::Directions::Up) ? 1 : 3;
	select += (left_right == pld::Directions::Right) ? 0 : 1;
	return select;
}

void pld::Bolt::deactivate() {
	speed = 0;
	is_launched = false;
	up_down = pld::Directions::Stationary;
	left_right = pld::Directions::Stationary;
	is_destroyed = true;
	drift = 0.5f;
}

void pld::Bolt::deactivateSilently() {
	speed = 0;
	is_launched = false;
	is_destroyed = false;
	up_down = pld::Directions::Stationary;
	left_right = pld::Directions::Stationary;
}


//#############################################################################
//# Core class procedures concerning bolts:                                   #
//#############################################################################

void pld::Core::drawBolt(float elapsed_time) {
	//P(t) = Start + time * (End - Start);
	// x+= (target -x) * .1

	if (!level.bolt.is_destroyed) {
		if (!level.bolt.is_launched) {
			level.bolt.pos = level.paddle.getPos();
			level.bolt.pos.x += ((level.paddle.width[level.paddle.num] / 2) - (level.bolt.scaled_radius));
			level.bolt.pos.y -= 32;
			//if (GetKey(olc::SPACE).bHeld) {
			//	if (bolt.speed < 500.0f) {
			//		bolt.speed = 500.0f;
			//	}
			//	bolt.speed += 1000.0f * elapsed_time;
			//	if (bolt.speed > 1000.0f) {
			//		bolt.speed = 1000.0f;
			//	}
			//}
			if (GetKey(olc::SPACE).bReleased) {
				level.bolt.speed = (float)(ease == Ease::Normal ? 500 : ease == Ease::Hard ? 700 : 900); //Last one is Ease::BoR
				level.bolt.is_launched = true;
				updateDeviation();
				updateBolt(elapsed_time, pld::Directions::Up, level.past_paddle_speed >= 0 ? pld::Directions::Right : pld::Directions::Left);
			}
		}
		if (GetKey(olc::R).bPressed) {
			level.bolt.deactivate();
		}
		updateBolt(elapsed_time);
		ensureBoltWithinBounds();
		olc::Decal* decal = dcl_bolt->at(level.bolt.chooseDecal()).get();
		DrawDecal(level.bolt.pos, decal, level.bolt.scale);
	}
	else {
		drawBoltDestruction(elapsed_time);
	}
}

void pld::Core::updateBolt(float elapsed_time, pld::Directions up_down, pld::Directions left_right) {
	level.bolt.up_down = up_down;
	level.bolt.left_right = left_right;
	updateBolt(elapsed_time);
}

void pld::Core::updateBolt(float elapsed_time) {
	float deviation_div = 3.0f;
	float deviation_rmn = deviation_div - 1.0f;

	// TODO: remove deviation from level.bolt
	// The deviation values would probably be totally fine as local vals, can be calculated from drift.
	float deviation_x = 0.0f;
	float deviation_y = 0.0f;

	float change = level.bolt.speed * elapsed_time;

	if (level.bolt.up_down != pld::Directions::Stationary) {
		float deviation = (change / deviation_div);
		float cur_change = deviation * deviation_rmn;
		deviation_x = deviation * level.bolt.drift;
		deviation_y = deviation * (1 - level.bolt.drift);
		olc::vf2d expected_pos = { 
			level.bolt.pos.x += level.bolt.left_right == Directions::Left ? -(cur_change + deviation_x) : (cur_change + deviation_x),
			level.bolt.pos.y += level.bolt.up_down == Directions::Up ? -(cur_change + deviation_y) : (cur_change + deviation_y)
		};
		CollisionType collision = willCollide(expected_pos);
		if (collision == CollisionType::Water) {
#if defined(pldSOUND)
			long long cur = 0;
			long long stop = sounds->at(1).get()->getDuration();
			sounds->at(1).get()->setPositions(&cur, &stop, true);
			sounds->at(1).get()->run();
#endif
			level.lives -= 1;
			level.bolt.deactivate();
		}
		else if (collision == CollisionType::NoCollision) {
			level.bolt.pos = expected_pos;
		}
		else {
			level.bolt.updateDirection(collision);
			if (collision == CollisionType::BoxSide || collision == CollisionType::BoxTop) {
#if defined(pldSOUND)
				//long long cur = 0;
				//long long stop = sounds->at(3).get()->getDuration();
				//sounds->at(3).get()->setPositions(&cur, &stop, true);
				//sounds->at(3).get()->run();
				sounds->at(3).get()->play();
#endif
			}
			else {
#if defined(pldSOUND)
				//long long cur = 0;
				//long long stop = sounds->at(2).get()->getDuration();
				//sounds->at(2).get()->setPositions(&cur, &stop, true);
				//sounds->at(2).get()->run();
				sounds->at(2).get()->play();
#endif
			}
			if (collision == CollisionType::Paddle) {
				updateDeviation();
			}

			deviation_x = deviation * level.bolt.drift;
			deviation_y = deviation * (1 - level.bolt.drift);

			level.bolt.pos = {
				level.bolt.pos.x += level.bolt.left_right == Directions::Left ? -(cur_change + deviation_x ) : (cur_change + deviation_x),
				level.bolt.pos.y += level.bolt.up_down == Directions::Up ? -(cur_change + deviation_y) : (cur_change + deviation_y)
			};
		}
	}
}

void pld::Core::ensureBoltWithinBounds() {
	if (level.bolt.is_launched && !level.bolt.is_destroyed) {
		if (level.bolt.pos.x < tiles.size) {
			level.bolt.pos.x = (float)tiles.size;
			level.bolt.left_right = pld::Directions::Right;
		}
		if (level.bolt.pos.x > ScreenWidth() - tiles.size - level.bolt.scaled_radius*2) {
			level.bolt.pos.x = ScreenWidth() - tiles.size - level.bolt.scaled_radius*2;
			level.bolt.left_right = pld::Directions::Left;
		}
		if (level.bolt.pos.y < tiles.size) {
			level.bolt.pos.y = (float)tiles.size;
			level.bolt.up_down = pld::Directions::Down;
		}
		if (level.bolt.pos.y > ScreenHeight() - tiles.size - level.bolt.scaled_radius*2) {
			level.bolt.pos.y = ScreenHeight() - tiles.size - level.bolt.scaled_radius*2;
			level.bolt.up_down = pld::Directions::Up;
		}
	}
}

void pld::Core::drawBoltDestruction(float elapsed_time) {
	if (level.bolt.destruction_sprite < 9) {
		DrawDecal({ level.bolt.pos.x -30, level.bolt.pos.y -60 }, dcl_splash->at(level.bolt.destruction_sprite).get());
		if (level.bolt.destruction_frame > 0.1) {
			level.bolt.destruction_sprite++;
			level.bolt.destruction_frame = 0.0;
		}
		else {
			level.bolt.destruction_frame += elapsed_time;
		}
	}
	else {
		// Stop destruction animation and reset bolt.
		level.bolt.destruction_frame = 0.0f;
		level.bolt.destruction_sprite = 0;
		if (level.lives > 0) {
			level.bolt.is_destroyed = false;
		}
		else {
			level.game_over = true;
			level.bolt.is_destroyed = false;
		}
	}
}

void pld::Core::updateDeviation() {
	if (level.paddle.speed != 0.0f) {
		level.bolt.drift = (abs(level.paddle.speed) / 250.0f);
		bool inLineMovement = ((level.bolt.left_right == pld::Directions::Right && level.paddle.speed >= 0.0f) 
			|| (level.bolt.left_right == pld::Directions::Left && level.paddle.speed <= 0.0f) );

		std::cout << "In line: " << (inLineMovement ? "true" : "false") << std::endl;

		if (abs(level.bolt.drift) > 0.5f) {
			level.bolt.drift = 0.5f;
		}

		level.bolt.drift = (inLineMovement ? 0.5f + level.bolt.drift : (0.5f - level.bolt.drift));
	}
	else {
		level.bolt.drift = 0.5f;
		std::cout << "Reset Drift!" << std::endl;
	}
}