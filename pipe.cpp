#include"pipe.h"
#include<iostream>
#include<stdio.h>

vector<position> posPipe;

bool pipe::init()
{
    posPipe.clear();
    for(signed char i = 0 ; i < TOTAL_PIPES ; i++ )
    {
        position temp;
        temp.getPosition(SCREEN_WIDTH + i * PIPES_DISTANCE + 350, (rand() % (randMax - randMin + 1)) + randMin);
        posPipe.push_back(temp);
    }

    if(isNULL())
    {
        if(Load("Components/image/pipe.ong" , 1))
        {
            return true;
        }
    }
    return false;
}

void pipe::Free()
{
    Free();
}

void pipe::render()
{
    for (signed char i = 0; i < TOTAL_PIPES; i++)
    {
        if (posPipe[i].x <= SCREEN_WIDTH && posPipe[i].x > -GetWid())
        {
            Render(posPipe[i].x, posPipe[i].y);
        }
        Render(posPipe[i].x, posPipe[i].y + GetHei() + PIPE_SPACE, 180);
    }
}

void pipe::Update()
{
    if (!Die)
    {
        for (signed char i = 0; i < TOTAL_PIPES; i++)
        {
            if (posPipe[i].x < - GetWid())
            {
                posPipe[i].y = (rand() % (randMax - randMin + 1)) + randMin;
                posPipe[i].x = posPipe[(i + TOTAL_PIPES - 1) % TOTAL_PIPES].x + PIPES_DISTANCE;
            }
            else
            {
                posPipe[i].x -= 3;
            }
        }
    }
}