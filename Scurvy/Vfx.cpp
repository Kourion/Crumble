#include "Core.h"

//#############################################################################
//# Load Vfx, currently only for Windows:                                     #
//#############################################################################

#if defined(pldSOUND)

void pld::Core::initVfx() {
	// Initialize COM
	::CoInitialize(NULL);
	loadVfx();
	// Play title music.
	sounds->at(0).get()->run();
	//for (int i = 0; i < vfx_num; i++)
	//{
	//	vfx->push_back(0.0f);
	//}
}

#endif