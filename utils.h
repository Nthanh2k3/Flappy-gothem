#pragma once

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<vector>
#include<stdio.h>
#include<SDL_ttf.h>

using namespace std;

class position {
    public: 
        short int x,y,angle,state ;
        void getPosition(const short int x, const short int y);

};

class LTexture{
    public: 
        LTexture();

        ~LTexture (){};

        bool isNULL();

        bool Load(string path , double scale = 1);

        short int GetWid();
        short int GetHei();

        void Free();

        void Render(short int x , short int y , short int angle = 0 , SDL_Rect *Clip = NULL ,SDL_RendererFlip = SDL_FLIP_NONE);


        public : 

            SDL_Texture* Texture;
            short int tWid;
            short int tHei;

        public : 

            static SDL_Window* gWindow;
            static SDL_Renderer* gRenderer;
            static SDL_Event Event;
            static bool Quit;
            static short int Score;
            static bool Die;

            static const short int SCREEN_WIDTH = 350;
            static const short int SCREEN_HEIGHT = 600 ; 
            static const short int PIPE_SPACE = 150 ; 
            static const short int TOTAL_PIPES = 4;
            static const short int PIPES_DISTANCE = 220;
            static const short int LAND_HEIGHT = 140;
            static const short int GOTHEM_HEIGHT = 35;
            static const short int GOTHEM_WIDTH = 50;
};

