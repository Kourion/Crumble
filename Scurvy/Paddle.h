#pragma once
#include "Enum.h"
#include "Engine.h"

//#############################################################################
//# Paddle data struct, represents state of a paddle:                         #
//#############################################################################

namespace pld {
	class Paddle {
	public:
		int num = 3;
		olc::vf2d base_pos = { 0.0f, 0.0f };
		float speed = 0.0f;
		float offset = 0.0f;
		std::vector<int> width = { 0 };
		PaddleShape shape = PaddleShape::Flat;
		olc::vf2d getPos() {
			return { base_pos.x + offset, base_pos.y};
		}
	};
}