#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
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
        bool ready = false;
        // Duration of the MP3.
        LONGLONG duration = 0;
    public:
        Sound()
        {
            //graphBuilder = NULL;
            //mediaControl = NULL;
            //mediaEventEx = NULL;
            //basicAudio = NULL;
            //mediaSeeking = NULL;
            //ready = false;
            //duration = 0;
        }

        ~Sound() { destroy(); }
        bool load(str_l filename);
        bool play(); //Implement as search + run
        bool run();
        //bool pause();
        bool stop();

        // Poll this function with msTimeout = 0, so that it return immediately.
        // If the mp3 finished playing, WaitForCompletion will return true;
        bool waitForCompletion(long msTimeout, long* EvCode);

        // -10000 is lowest volume and 0 is highest volume, positive value > 0 will fail
        bool setVolume(long vol);

        // -10000 is lowest volume and 0 is highest volume
        long getVolume();

        // Returns the duration in 1/10 millionth of a second,
        // meaning 10,000,000 == 1 second
        // You have to divide the result by 10,000,000 
        // to get the duration in seconds.
        LONGLONG getDuration();

        // Returns the current playing position
        // in 1/10 millionth of a second,
        // meaning 10,000,000 == 1 second
        // You have to divide the result by 10,000,000 
        // to get the duration in seconds.
        LONGLONG getCurrentPosition();

        // Seek to position with pCurrent and pStop
        // bAbsolutePositioning specifies absolute or relative positioning.
        // If pCurrent and pStop have the same value, the player will seek to the position
        // and stop playing. Note: Even if pCurrent and pStop have the same value,
        // avoid putting the same pointer into both of them, meaning put different
        // pointers with the same dereferenced value.
        bool setPositions(LONGLONG* pCurrent, LONGLONG* pStop, bool bAbsolutePositioning);
        void destroy();
    };
}