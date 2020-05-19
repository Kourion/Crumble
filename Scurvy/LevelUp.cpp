#include "Core.h"

//#############################################################################
//# LevelUp procedures:                                                       #
//#############################################################################

pld::State pld::Core::onUserUpdateLevelUp(float elapsed_time) {
	pld::State next = pld::State::LevelUp;
	std::string str = "";
	str += level.player1.name;
	str += ": Level(" + std::to_string(level.lvl) + ") Score[";
	str += std::to_string((int)level.player1.points.flt);
	str += "] Lives(";
	str += std::to_string(level.lives);
	str += ") Score-Multiplier"; str += "{"; str += std::to_string((int)level.bolt.speed); str += "x}";
	DrawStringDecal({ 32, (float)(3 + level.top_btm_offset) }, str, olc::Pixel(246, 198, 55), { 2.0f, 2.0f });
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