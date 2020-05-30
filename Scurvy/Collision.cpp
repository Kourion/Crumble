#include "Core.h"

//#############################################################################
//# Collision detection functions:                                            #
//#############################################################################

//((ScreenHeight() % tile_size) / 2) + ((int)(ScreenHeight() / tile_size)) * tile_size)
pld::CollisionType pld::Core::willCollide(olc::vf2d expected_pos) {

	//DrawCircle(bolt.pos.x - 2, bolt.pos.y - 2, 2, olc::BLUE);

	expected_pos.x += level.bolt.scaled_radius; //((320) * bolt.scale_val);
	expected_pos.y += level.bolt.scaled_radius; //((320) * level.bolt.scale_val);
	
	//expected_pos.y += ((320) * bolt.scale_val);

	//DrawCircle(expected_pos.x - 2, expected_pos.y - 2, 2, olc::RED);

	// MEDO: TOP Collision needs to be earlier, both with wall and box

	CollisionType collision = CollisionType::NoCollision;
	int row_num = 0;
	int row_pos = 0;
	for (std::pair<int, LevelRow> row : level.map) {
		row_pos = 0;
		for (std::pair<olc::vi2d, int> brick : row.second.pos)
		{
			if (
				expected_pos.x > brick.first.x - level.bolt.scaled_radius 
				&& expected_pos.x < brick.first.x + tiles.size * brick.second + level.bolt.scaled_radius
				&& expected_pos.y > brick.first.y - level.bolt.scaled_radius && expected_pos.y < brick.first.y + 32 + level.bolt.scaled_radius
				&& (
					(
					expected_pos.x > brick.first.x  && expected_pos.x < brick.first.x + tiles.size * brick.second
					&&
					expected_pos.y > brick.first.y - level.bolt.scaled_radius && expected_pos.y < brick.first.y + 32 + level.bolt.scaled_radius
					)
					||
					( 
					expected_pos.x < brick.first.x + tiles.size * brick.second + level.bolt.scaled_radius
					&&
					expected_pos.y > brick.first.y && expected_pos.y < brick.first.y + 32
					)
				   )
				) 
			{

				//float flt_distance_vertical =
				//	level.bolt.up_down == Directions::Up ?
				//	brick.first.y + 32 + level.bolt.scaled_radius - expected_pos.y :
				//	expected_pos.y - brick.first.y - level.bolt.scaled_radius;

				//float flt_distance_horizontal =
				//	level.bolt.left_right == Directions::Right ?
				//	expected_pos.x - brick.first.x - level.bolt.scaled_radius :
				//	brick.first.x + tiles.size * brick.second + level.bolt.scaled_radius - expected_pos.x;
				
				//collision = std::abs(flt_distance_vertical) < std::abs(flt_distance_horizontal) ? CollisionType::BoxTop : CollisionType::BoxSide;

				if (expected_pos.x > brick.first.x && expected_pos.x < brick.first.x + tiles.size * brick.second
					&&
					expected_pos.y > brick.first.y - level.bolt.scaled_radius && expected_pos.y < brick.first.y + 32 + level.bolt.scaled_radius) {
					collision = CollisionType::BoxTop;
				}
				else if (expected_pos.x < brick.first.x + tiles.size * brick.second + level.bolt.scaled_radius
						&&
						expected_pos.y > brick.first.y&& expected_pos.y < brick.first.y + 32) {
					collision = CollisionType::BoxSide;
				}

				//std::cout << std::abs(flt_distance_vertical) << ((bolt.up_down == Directions::Up) ? "Up" : "Down") << "," << std::abs(flt_distance_horizontal) << ((bolt.left_right == Directions::Right) ? "Right" : "Left") << std::endl;
				row_num = row.first;

				// Collisions give score points!
				level.player1.points.flt += level.bolt.speed / brick.second;

				for (int i = 0; i < brick.second; i++)
				{
					drawImpact({ (float)(brick.first.x + tiles.size * i), (float)(brick.first.y) }); //expected_pos
				}
				break;
			}
			if (collision != CollisionType::NoCollision) { break; }
			row_pos++;
		}
		if (collision != CollisionType::NoCollision) { break; }
	}
	//std::cout << row_num << " -- " << row_pos << std::endl;
	//std::cout << level_map.size() << " -- " << std::endl;
	if (collision != CollisionType::NoCollision) { 
		level.map.at(row_num).pos.erase(level.map.at(row_num).pos.begin() + row_pos);
		return collision; 
	}

	if (expected_pos.x > level.width - tiles.size - level.bolt.scaled_radius) {
		return CollisionType::WallRight;
	}
	if (expected_pos.x < tiles.size + level.bolt.scaled_radius) {
		return CollisionType::WallLeft;
	}
	if (expected_pos.y < tiles.size + level.bolt.scaled_radius) {
		return CollisionType::Ceiling;
	}

	if (expected_pos.y > ScreenHeight() - tiles.size - level.bolt.scaled_radius
		&& expected_pos.x > (level.paddle.getPos().x) // Actually +-7 but that feels of.
		&& expected_pos.x < (level.paddle.getPos().x + level.paddle.width[level.paddle.num])) {

		// TODO: Maybe specifiy where on the paddle the collision occurred?
		return CollisionType::Paddle;
	}
	else if (expected_pos.y > ScreenHeight() - tiles.size - level.bolt.scaled_radius ) {
		return CollisionType::Water;
	}
	return CollisionType::NoCollision;
}

//Edge calculation ?