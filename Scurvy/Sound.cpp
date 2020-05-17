#include "Core.h"
#if defined(pldSOUND)

#include "Sound.h"
#include <uuids.h>

bool pld::Sound::load(str_l szFile) { //LPCWSTR
    destroy();
    ready = false;
    if (SUCCEEDED(CoCreateInstance(CLSID_FilterGraph,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_IGraphBuilder,
        (void**)&this->graphBuilder)))
    {
        graphBuilder->QueryInterface(IID_IMediaControl, (void**)&mediaControl);
        graphBuilder->QueryInterface(IID_IMediaEventEx, (void**)&mediaEventEx);
        graphBuilder->QueryInterface(IID_IBasicAudio, (void**)&basicAudio);
        graphBuilder->QueryInterface(IID_IMediaSeeking, (void**)&mediaSeeking);

        HRESULT hresult = graphBuilder->RenderFile(szFile, NULL);
        if (SUCCEEDED(hresult)) {
            ready = true;
            if (mediaSeeking) {
                mediaSeeking->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
                mediaSeeking->GetDuration(&duration); // returns 10,000,000 for a second.
                duration = duration;
            }
        }
    }
    return ready;
}

bool pld::Sound::play() {
    bool success = false;
    LONGLONG start = 0;
    success = setPositions(&start, &duration, true);
    return success && run();
}

bool pld::Sound::run() {
    if (ready && mediaControl) {
        HRESULT hr = mediaControl->Run();
        return SUCCEEDED(hr);
    }
    return false;
}

bool pld::Sound::stop() {
    if (ready && mediaControl) {
        HRESULT hr = mediaControl->Stop();
        return SUCCEEDED(hr);
    }
    return false;
}

bool pld::Sound::setVolume(long vol) {
    if (ready && basicAudio) {
        HRESULT hresult = basicAudio->put_Volume(vol);
        return SUCCEEDED(hresult);
    }
    return false;
}

long pld::Sound::getVolume() {
    if (ready && basicAudio) {
        long vol = -1;
        HRESULT hresult = basicAudio->get_Volume(&vol);
        if (SUCCEEDED(hresult)) { return vol; }
    }
    return -1;
}

LONGLONG pld::Sound::getDuration() {
    return duration;
}

LONGLONG pld::Sound::getCurrentPosition() {
    if (ready && mediaSeeking) {
        LONGLONG curpos = -1;
        HRESULT hresult = mediaSeeking->GetCurrentPosition(&curpos);
        if (SUCCEEDED(hresult)) { return curpos; }
    }
    return -1;
}

bool pld::Sound::setPositions(int64_t* pCurrent, int64_t* pStop, bool bAbsolutePositioning) {
    if (ready && mediaSeeking) {
        DWORD flags = 0;
        if (bAbsolutePositioning) {
            flags = AM_SEEKING_AbsolutePositioning | AM_SEEKING_SeekToKeyFrame;
        }
        else {
            flags = AM_SEEKING_RelativePositioning | AM_SEEKING_SeekToKeyFrame;
        }
        HRESULT hresult = mediaSeeking->SetPositions(pCurrent, flags, pStop, flags);
        if (SUCCEEDED(hresult)) { return true; }
    }
    return false;
}

void pld::Sound::destroy() {
    if (mediaControl) { mediaControl->Stop(); }
    if (graphBuilder) {
        graphBuilder->Release();
        graphBuilder = NULL;
    }
    if (mediaControl) {
        mediaControl->Release();
        mediaControl = NULL;
    }
    if (mediaEventEx) {
        mediaEventEx->Release();
        mediaEventEx = NULL;
    }
    if (basicAudio) {
        basicAudio->Release();
        basicAudio = NULL;
    }
    if (mediaSeeking) {
        mediaSeeking->Release();
        mediaSeeking = NULL;
    }
    ready = false;
}

#endif