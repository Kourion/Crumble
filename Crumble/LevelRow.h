#pragma once
#include <vector>
#include "Engine.h"

//#############################################################################
//# LevelRow struct, vector wrapper for future updates.                       #
//#############################################################################

namespace pld {
	struct LevelRow {
		std::vector<std::pair<olc::vi2d, int>> pos;
		LevelRow() {
		}
	};
}
