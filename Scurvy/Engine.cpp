#define OLC_PGE_APPLICATION
#include "Engine.h"
#include "Core.h"


//#############################################################################
//# Startup and engine initialisation:                                        #
//#############################################################################

int main()
{
	int screen_width_a = 1920; //1920; 
	int screen_height_a = 1080; //1080;
	int screen_width_b = 1440;
	int screen_height_b = 900;

	// MEDO: Startup menu to choose default resolution.
//	pld::Startup startup(screen_width, screen_height);
//	if(startup.Construct(400, 200, 1, 1)){
//		startup.Start();
//		screen_width = startup.getScreenWidth();
//		screen_height = startup.getScreenHeight();
//	}

	pld::Core core;
	//if (core.Construct(screen_width_a, screen_height_a, 1, 1, true, true)) {
	if (core.Construct(screen_width_b, screen_height_b, 1, 1, false, true)) {
		core.Start();
	}



	return 0;
}
