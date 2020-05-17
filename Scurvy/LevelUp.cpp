#include "Core.h"

pld::State pld::Core::onUserUpdateLevelUp(float elapsed_time) {
	pld::State next = pld::State::LevelUp;
	if (level.levelUp) {
		level.levelUp = false;
		level.switch_timer = 0.8f;
#if defined(pldSOUND)
		sounds->at(6).get()->play();
#endif	
	}
	// play level up sound
	// show level up counter decal (have it scale from tiny to screen covering)
	// switch to the next level after a while
	if (level.switch_timer < 0) {
		return pld::State::Level;
	}
	level.switch_timer -= elapsed_time;
	return next;
}