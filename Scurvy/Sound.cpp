#include "Core.h"
#if defined(pldSOUND)

#include "Sound.h"
#include <uuids.h>

bool pld::Sound::load(str_l file) { //LPCWSTR
    destroy();
    active = false;
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

        HRESULT hresult = graphBuilder->RenderFile(file, NULL);
        if (SUCCEEDED(hresult)) {
            active = true;
            if (mediaSeeking) {
                mediaSeeking->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
                mediaSeeking->GetDuration(&duration);
                duration = duration;
            }
        }
    }
    return active;
}

bool pld::Sound::play() {
    bool success = false;
    LONGLONG start = 0;
    success = setPositions(&start, &duration, true);
    return success && run();
}

bool pld::Sound::run() {
    if (active && mediaControl) {
        HRESULT hresult = mediaControl->Run();
        return SUCCEEDED(hresult);
    }
    return false;
}

bool pld::Sound::stop() {
    if (active && mediaControl) {
        HRESULT hresult = mediaControl->Stop();
        return SUCCEEDED(hresult);
    }
    return false;
}

bool pld::Sound::setVolume(long vol) {
    if (active && basicAudio) {
        HRESULT hresult = basicAudio->put_Volume(vol);
        return SUCCEEDED(hresult);
    }
    return false;
}

long pld::Sound::getVolume() {
    if (active && basicAudio) {
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
    if (active && mediaSeeking) {
        LONGLONG cur_pos = -1;
        HRESULT hresult = mediaSeeking->GetCurrentPosition(&cur_pos);
        if (SUCCEEDED(hresult)) { return cur_pos; }
    }
    return -1;
}

bool pld::Sound::setPositions(LONGLONG *ptr_cur, LONGLONG *ptr_stop, bool absolute_pos) {
    if (active && mediaSeeking) {
        DWORD flags = 0;
        if (absolute_pos) {
            flags = AM_SEEKING_AbsolutePositioning | AM_SEEKING_SeekToKeyFrame;
        }
        else {
            flags = AM_SEEKING_RelativePositioning | AM_SEEKING_SeekToKeyFrame;
        }
        HRESULT hresult = mediaSeeking->SetPositions(ptr_cur, flags, ptr_stop, flags);
        return (SUCCEEDED(hresult));
    }
    return false;
}

void pld::Sound::destroy() {
    active = false;
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
}

#endif