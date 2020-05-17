#pragma once

//#############################################################################
//# Sound class as interface for the windows api:                             #
//#############################################################################

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#include <strmif.h>
#include <control.h>

#pragma comment(lib, "strmiids.lib")
//"Long Pointer to Constant Wide String"
typedef _Null_terminated_ CONST WCHAR* str_l;

namespace pld {
    class Sound {
    private:
        IGraphBuilder* graphBuilder = NULL;
        IMediaControl* mediaControl = NULL;
        IMediaEventEx* mediaEventEx = NULL;
        IBasicAudio* basicAudio = NULL;
        IMediaSeeking* mediaSeeking = NULL;
        bool active = false;
        LONGLONG duration = 0;
    public:
        Sound() { }
        ~Sound() { destroy(); }
        bool load(str_l filename);
        // Play is search + run.
        bool play();
        bool run();
        bool stop();

        // Volume goes from -10000 (lowest) to 0 (highest).
        bool setVolume(long vol);
        long getVolume();

        // Divide by 10.000.000 to get result in seconds.
        LONGLONG getDuration();
        LONGLONG getCurrentPosition();
        bool setPositions(LONGLONG *ptr_cur, LONGLONG *ptr_stop, bool absolute_pos);

        void destroy();
    };
}