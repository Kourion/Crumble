#include "Core.h"

pld::State pld::Core::onUserUpdateLevelUp(float elapsed_time) {
	pld::State next = pld::State::LevelUp;
	// play level up sound
	// show level up counter decal (have it scale from tiny to screen covering)
	// switch to the next level after a while
	if (level.switch_timer < 0) {
	
	}
	return next;
}