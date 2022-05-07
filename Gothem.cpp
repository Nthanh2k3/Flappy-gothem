#include"Gothem.h"
#include<iostream>
#include<stdio.h>

bool Gothem::init(bool IsSuperMan)
{
    string Gothem_path = "Components/image/Batman.png";
    if(IsSuperMan)
    {
        string Gothem_path = "Components/image/Superman.png";
    }

    if(saved_path == Gothem_path)
    {
        posGothem.getPosition(75, SCREEN_HEIGHT / 2 - 10);
        ahead = 0;
        angle = 0;
    }

    if(isNULL() || saved_path != Gothem_path)
    {
        saved_path = Gothem_path;
        if(Load(Gothem_path.c_str(), 1))
        {
            return true;
        }
        else
        {
            return false;
        }



    }
    return false;
}

void Gothem::Free()
{
    Free();
}

void Gothem::render()
{
    Render(posGothem.x, posGothem.y , angle);
} 

void Gothem::fall()
{
    if(Die && posGothem.y < SCREEN_HEIGHT - LAND_HEIGHT - GOTHEM_HEIGHT - 5)
    {
        if(time == 0)
        {
            x0 = posGothem.y;
            angle = -25;

        }
        else if(angle < 70 && time > 30)
        {
            angle += 3;

        }

        if(time >= 0)
        {
            posGothem.y = x0 + time * time * 0.18 - 7.3 * time;
            time++;
        }
    }
    else return;
}

void Gothem::update(short int pipeWid , short int pipeHei)
{
    if (!Die)
    {
        if (time == 0)
        {
            x0 = posGothem.y;
            angle = -25;
        }
        else if (angle < 70 && time > 30)
        {
            angle += 3;
        }

        if (time >= 0)
        {
            posGothem.y = x0 + time * time * 0.18 - 7.3 * time;
            time++;
        }

        if ( (posGothem.x + GetWid() > posPipe[ahead].x + 5) && (posGothem.x + 5 < posPipe[ahead].x + pipeWid) &&
             (posGothem.y + 5 < posPipe[ahead].y + pipeHei || posGothem.y  + GetHei() > posPipe[ahead].y + pipeHei + PIPE_SPACE + 5) )
        {
            Die = true;
        }
        else if (posGothem.x > posPipe[ahead].x + pipeWid )
        {
            ahead = ( ahead + 1 ) % TOTAL_PIPES;
            Score++;
        }

        if (posGothem.y > SCREEN_HEIGHT - LAND_HEIGHT -  GOTHEM_HEIGHT - 5 || posGothem.y < - 10 )
        {
            Die = true;
        }
    }
}