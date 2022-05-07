#pragma once

#include"utils.h"
#include"pipe.h"

using namespace std;

class Gothem:LTexture
{
    public :
    bool init(bool IsSuperMan);
    
    void render();
    void Free();

    void resetTime()
    {
        time = 0;
    }

    void fall();
    void update(short int pipeWid , short int pipeHei);

    private:
        short int angle, time, x0;
        short int ahead = 0;
        string saved_path = "";
        position posGothem;


};