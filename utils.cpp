#include"gameplay.h"
#include<iostream>


bool LTexture::Quit = false;
bool LTexture::Die = true;

short int LTexture::Score = 0 ;
SDL_Window* LTexture::gWindow = NULL;
SDL_Renderer* LTexture::gRenderer = NULL;
SDL_Event LTexture::Event;

LTexture::LTexture()
{
    Texture = NULL;
}

short int LTexture::GetWid()
{
    return tWid;
}

short int LTexture::GetHei()
{
    return tHei;
}

void LTexture::Free()
{
    if(Texture != NULL){
        SDL_DestroyTexture(Texture);
        Texture = NULL;
        tWid = 0;
        tHei = 0;

    }
}


void LTexture::Render(short int x, short int y , short int angle , SDL_Rect* clip , SDL_RendererFlip flip)
{
    SDL_Rect Rec_Render = {x,y,tWid,tHei};
    if(clip == NULL)
    {
        Rec_Render.w = clip ->w;
        Rec_Render.h = clip ->h;
    }

    SDL_RenderCopyEx(gRenderer , Texture , clip, &Rec_Render , angle , NULL , flip);

}

bool LTexture::Load(string path , double scale)
{
    Free();

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL)
    {
        cout << "Unable to load image , Error : " << path.c_str() << IMG_GetError() << endl;

    }
    else 
    {
        SDL_SetColorKey(loadedSurface , SDL_TRUE , SDL_MapRGB(loadedSurface -> format ,0x00 , 0xFF , 0xFF));

        Texture = SDL_CreateTextureFromSurface(gRenderer , loadedSurface);
        if(Texture == NULL)
        {
            cout << "Cannot create Texture from : " << path.c_str() << endl << "SDL Errors : " << SDL_GetError() << endl;
        }
        else
        {
            tWid = (loadedSurface -> w) *scale;
            tHei = (loadedSurface -> h) *scale;
        }

        SDL_FreeSurface(loadedSurface);

    }
    SDL_SetRenderDrawColor(gRenderer , 0xFF,0xFF , 0xFF , 0xFF);

    return Texture != NULL;


}

bool LTexture::isNULL()
{
    if(Texture == NULL) return true;
    return false;
}

void position::getPosition(const short int x, const short int y)
{
    this ->x = x;
    this ->y = y;
}



