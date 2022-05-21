#pragma once

#include"Gothem.h"
#include"pipe.h"
#include"land.h"
#include"soundtrack.h"
#include"utils.h"
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

class game:LTexture {
    public : 
    struct input{
        enum type {QUIT,PLAY,NONE,PAUSE};
        type Type;
    };
    input PlayerInput;
    Gothem Gothem;
    pipe pipe;
    sound sound;
    Land land;

    public:

    game();
    ~game();


    bool InitGraphic();

    bool Is_Quit()
    {
        return Quit;
    }

    bool Is_Die()
    {
        return Die;
    }

    bool Get_pipe_Width()
    {
        return pipe.width();
    }

    bool Get_pipe_Height()
    {
        return pipe.height();
    }

    void TakeInput();
    void display();
    void ReleaseGraphic();
    void Render_Score_Small();
    void Render_Score_Large();
    void Render_Highest_Score();
    void Render_Messages();
    void Render_Background();
    void Render_Background_Nightmode();
    void Resume();
    void Pause();
    void RenderLand();
    void RenderPauseTab();
    void Superman();
    void Batman(); 
    bool Change_Characters();
    void RenderNextButton();
    void RenderGameOver();
    void RenderMedals();
    void replay();
    bool checkReplay();
    void Restart();
    void ResetTime();


    private :

    const double scaleNum = 0.75;
    short int HighestScore ; 



};