#pragma once

#include"utils.h"
#include<iostream>
#include<vector>

using namespace std;

class Land:LTexture
{
    public:
    bool init();
    void Render();
    void update();
    void Free();
    private : 
    position posLand;
};