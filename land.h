#pragma once

#include"utils.h"
#include<iostream>
#include<vector>

using namespace std;

class Land:LTexture
{
    public:
    bool init();
    void Free();
    void Render();
    void update();

    private : 
    position posLand;
};