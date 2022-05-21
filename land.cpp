

#include"land.h"
#include<iostream>
#include<stdlib.h>
#include<stdio.h>



bool Land::init()
{
    posLand.getPosition(0, SCREEN_HEIGHT - LAND_HEIGHT );
    string back_path = "Components/image/land.png";
    if (isNULL())
    {
        if ( Load( back_path.c_str(), 1 ) )
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

void Land::Render()
{
    if (posLand.x > 0)
    {
        LTexture::Render(posLand.x , posLand.y);
    }
    else if (posLand.x > -SCREEN_WIDTH && posLand.x <= 0)
    {
        LTexture::Render(posLand.x, posLand.y);
        LTexture::Render(posLand.x + SCREEN_WIDTH, posLand.y , 0, NULL);
    }
    else
    {
        posLand.getPosition(0, SCREEN_HEIGHT - LAND_HEIGHT);
        LTexture::Render(posLand.x, posLand.y);
    }
}

void Land::update()
{
    posLand.x -= 3;
}

void Land::Free()
{
    Free();
}
