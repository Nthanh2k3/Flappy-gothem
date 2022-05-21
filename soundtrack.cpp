#include"soundtrack.h"
#include<stdio.h>
#include<iostream>
#include<string>


bool sound::init()
{
    string breath_path = "Components/sound/breath.wav";
    string hit_path ="Components/sound/á.wav";
    string sound_path = "Components/image/sound.png";

    bool success = true;
    if(SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        cout << "SDL cannot be initialized ! , SDL error :" << SDL_GetError() << endl;
        success = false;
    }
    else
    {
        if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,2048)<0)
        {
            cout << "SDL_mixer cannot be initialized , SDL Error :" << Mix_GetError() << endl;
            success = false;
        }

        breath = Mix_LoadWAV(breath_path.c_str());
        if(breath == NULL)
        {
            cout << "SDL_mixer cannot load the WAV file!,SDL Error" << Mix_GetError() << endl;
            success = false;
        }

        hit = Mix_LoadWAV(hit_path.c_str());
        if(hit == NULL)
        {
            cout << "SDL_mixer cannot load the WAV file!,SDL Error" << Mix_GetError() << endl;
            success = false;
        }

        if(!Load(sound_path))
        {
            return false;
        }

        active.x = 0;
        active.y = 0;
        active.w = GetWid();
        active.h = GetHei()/2;
        mute.x = 0;
        mute.y = GetHei()/2;
        mute.w = GetWid();
        mute.h = GetHei() / 2;
        isPlay = true;



    }
    return success;

}

void sound::Free()
{
    Free();

    Mix_FreeChunk(breath);
    breath = NULL;
    Mix_FreeChunk(hit);
    hit = NULL;

    Mix_Quit();
}

void sound::playBreath()
{
    if (isPlay)
    {
        Mix_PlayChannel( -1, breath, 0 );
    }
}

void sound::playHit()
{
    if (isPlay)
    {
        Mix_PlayChannel(-1, hit, 0);
    }
}

void sound::RenderSound()
{
    if (isPlay)
    {
        Render(POS_X, POS_Y, 0, &active);
    }
    else
    {
        Render(POS_X, POS_Y, 0, &mute);
    }
}

bool sound::CheckSound()
{
    int x,y;
    SDL_GetMouseState(&x,&y);
    if(x > POS_X && x < POS_X + GetWid() && y>POS_Y && y<POS_Y + GetHei())
    {
        isPlay = !isPlay;
        return true;
    }
    return false;
}