#pragma once
#ifndef _CSOUND_H_
#define _CSOUND_H_

#include <fmod.hpp>
#include "gameNode.h"

#define SOUND_MAX 0.1f
#define SOUND_MIN 0.0f
#define SOUND_DEFAULT 0.1f
#define SOUND_WEIGHT 0.1f

class CSound : public gameNode
{
private:
    static FMOD_SYSTEM* g_sound_system;

    FMOD_SOUND* m_sound;
    FMOD_CHANNEL* m_channel;

    float m_volume;
    FMOD_BOOL m_bool;
public:
    CSound(const char* path, bool loop);
    ~CSound();

    static int Init();
    static int Release();

    int play();
    int pause();
    int resume();
    int stop();
    int volumeUp();
    int volumeDown();

    int Update();
};

#endif
