#pragma once

#include<SDL_mixer.h>
#include<string>
#include"utils.h"

using namespace std;

class sound:LTexture
{
    public :
    bool init();
    void Free();
    void playBreath();
    void playHit();
    void RenderSound();
    bool CheckSound();

    private:

    const short int POS_X = 107;
    const short int POS_Y = 267;
    bool isPlay = 0;
    Mix_Chunk* breath = NULL;
    Mix_Chunk* hit = NULL;
    Mix_Chunk* drop = NULL;
    SDL_Rect mute;
    SDL_Rect active;
};