#pragma once
#include <vector>
#include "Engine.h"

namespace pld {
	struct LevelRow {
		std::vector<std::pair<olc::vi2d, int>> pos;
		LevelRow() {
		}
	};
}