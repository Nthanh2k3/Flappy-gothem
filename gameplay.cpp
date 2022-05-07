#include"gameplay.h"
#include"utils.h"
#include<iostream>

void game::TakeInput()
{
    while(SDL_PollEvent(&Event) != 0)
    {
        if(Event.type == SDL_QUIT)
        {
            PlayerInput.Type = input::QUIT;
            Quit = true;
        } else if (Event.type == SDL_MOUSEBUTTONDOWN || (Event.type == SDL_KEYDOWN && (Event.key.keysym.sym == SDLK_SPACE || Event.key.keysym.sym == SDLK_UP)&& Event.key.repeat == 0) )
        {
            PlayerInput.Type = input::PLAY; 
        }
        else if (Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_ESCAPE && Event.key.repeat == 0)
        {
            PlayerInput.Type = input::PAUSE;
        }
        

    }
}

game::game()
{
    Init_Graphic();
    pipe.init();
    land.init();
    sound.init();

}

game::~game()
{
    Gothem.Free();
    pipe.Free();
    land.Free();
    sound.Free();
    Free();
    Release_Graphics();
}

void game::Release_Graphics()
{
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL; 
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();

}

bool game::Init_Graphic()
{
    bool Success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "SDL couldn't initialize ! Error :" << SDL_GetError() << endl;
        Success = false;
    }
    else
    {
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"))
        {
            cout << "Linear Texture filtering not enabled !" << endl;
        }

        gWindow = SDL_CreateWindow("Game Rác",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

        if(gWindow == NULL)
        {
            cout << "SDL cannot create Window , Error :" << SDL_GetError() << endl;
            Success = false;
        }

        else
        {
            gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);
            if(gRenderer == NULL)
            {
                cout << "SDL cannot create a renderer" << SDL_GetError() << endl;
                Success = false;
            }

            else
            {
                SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);

                int imgFlags = IMG_INIT_PNG;

                if(!(IMG_Init(imgFlags)& imgFlags ))
                {
                    cout << "SDL_Image could not initialize , Error" << SDL_GetError() << endl;
                    Success = false;
                }

                if(TTF_Init() == -1)
                {
                    cout << "SDL_TTF could not initialize , Error:" << SDL_GetError() << endl;
                    Success = false;
                }
            }
        }
    }
    return Success;
}

void game::display()
{
    SDL_RenderPresent(gRenderer);
    SDL_RenderClear(gRenderer);
}

void game::Render_Score_Small()
{
    string s = to_string(Score);
    signed char len = s.length();
    LTexture image;

    for(signed char i = len - 1 ; i > 0 ; i-- )
    {
        signed char number = s[i] -'0' ;
        if(number == 1)
        {
            image.Load("Components/Numberfont/1.png",scaleNum);
        }
        else if(number == 2)
        {
            image.Load("Components/Numberfont/2.png",scaleNum);
        }
        else if(number == 3)
        {
            image.Load("Components/Numberfont/3.png",scaleNum);
        }
        else if(number == 4)
        {
            image.Load("Components/Numberfont/4.png",scaleNum);
        }
        else if(number == 5)
        {
            image.Load("Components/Numberfont/5.png",scaleNum);
        }
        else if (number == 6)
        {
            image.Load("Components/Numberfont/6.png",scaleNum);
        }
        else if(number == 7)
        {
            image.Load("Components/Numberfont/7.png",scaleNum);
        }
        else if(number == 8)
        {
            image.Load("Components/Numberfont/8.png",scaleNum);
        }
        else if(number == 9)
        {
            image.Load("Components/Numberfont/9.png",scaleNum);
        }
        else if(number == 0)
        {
            image.Load("Components/Numberfont/0.png",scaleNum);
        }

        image.Render(260 - image.GetWid()*(len-i-1)* 0.75 - 5*(len - i -1 ),268);

    }
    image.Free();

}

void game::Render_Score_Large()
{
    string s = to_string(Score);
    signed char len = s.length();
    LTexture image;

    for(signed char i = 0 ; i < len ; i++ )
    {
        signed char number = s[i] - '0';
        if(number == 1)
        {
            image.Load("Components/Numberfont/1.png",scaleNum);
        }

        else if(number == 2)
        {
            image.Load("Components/Numberfont/2.png",scaleNum);
        }

        else if(number ==3)
        {
            image.Load("Components/Numberfont/3.png",scaleNum);
        }
        else if(number == 4)
        {
            image.Load("Components/Numberfont/4.png",scaleNum);
        }
        else if(number == 5)
        {
            image.Load("Components/Numberfont/5.png",scaleNum);
        }
        else if(number == 6)
        {
            image.Load("Components/Numberfont/6.png",scaleNum);
        }
        else if(number == 7)
        {
            image.Load("Components/Numberfont/7.png",scaleNum);
        }
        else if(number == 8)
        {
            image.Load("Components/Numberfont/8.png",scaleNum);
        }
        else if(number == 9)
        {
            image.Load("Components/Numberfont/9.png",scaleNum);
        }
        else if(number == 0)
        {
            image.Load("Components/Numberfont/0.png",scaleNum);
        }
		image.Render((SCREEN_WIDTH - (image.GetWid() * len + (len - 1) * 10)) / 2 + (i + 30) * i, 100);
		
    }
    image.Free();
        
}

void game::Render_Highest_Score()
{
    ifstream fileIn("Components/Data/HighestScore.txt");
    fileIn >> HighestScore;
    ofstream fileOut("Components/Data/HighestScore.txt", ios::trunc);

    if(Score > HighestScore){
        HighestScore = Score;
    }

    string s = to_string(HighestScore);
    signed char len = s.length();
    LTexture image;


    for(signed char i = len -1 ; i>=0; i -- )
    {
        signed char number = s[i] - '0';
        if(number == 1)
        {
            image.Load("Components/Numberfont/1.png",scaleNum);
        }
        else if(number == 2)
        {
            image.Load("Components/Numberfont/2.png",scaleNum);
        }
        else if(number == 3)
        {
            image.Load("Components/Numberfont/3.png",scaleNum);
        }
        else if(number == 4)
        {
            image.Load("Components/Numberfont/4.png",scaleNum);
        }
        else if(number == 5)
        {
            image.Load("Components/Numberfont/5.png",scaleNum);
        }
        else if(number == 6)
        {
            image.Load("Components/Numberfont/6.png",scaleNum);
        }
        else if(number == 7)
        {
            image.Load("Components/Numberfont/7.png",scaleNum);
        }
        else if(number == 8)
        {
            image.Load("Components/Numberfont/8.png",scaleNum);
        }
        else if(number == 9)
        {
            image.Load("Components/Numberfont/9.png",scaleNum);
        }
        else if(number == 0)
        {
            image.Load("Components/Numberfont/0.png",scaleNum);
        }
		image.Render(260 - image.GetWid()*(len-i-1)*0.75 - 5*(len - i - 1), 315);

    }
    image.Free();
    fileOut << HighestScore;
    fileIn.close();
    fileOut.close();
}

void game::Render_Messages()
{
   LTexture image;
   image.Load("Components/image/Tutorial.png", 1);
   image.Render((SCREEN_WIDTH-image.GetWid())/2,180);
   image.Free(); 
}

void game::Render_Background()
{
    LTexture image;
    image.Load("Components/image/gothem.png",1);
    image.Render(0,0);
    image.Free();
}

void game::RenderLand()
{
    LTexture image;
    image.Load("Components/image/land.png",1);
    image.Render((SCREEN_WIDTH - image.GetWid()) / 2 , (SCREEN_HEIGHT - image.GetHei()));
    image.Free();

}

void game::Resume()
{
    LTexture image;
    image.Load("Components/image/resume.png", 1);
    image.Render(SCREEN_WIDTH - 50 , 20);
    image.Free();
}

void game::RenderPauseTab()
{
    LTexture image;
    image.Load("Components/image/pausetab.png",1);
    image.Render((SCREEN_WIDTH - image.GetWid())/2 , 230);
    image.Free();

}

void game::Pause()
{
    LTexture image;
    image.Load("Components/image/pause.png",1);
    image.Render(SCREEN_WIDTH - 50 , 20);
    image.Free();
}

void game::Batman()
{
    LTexture image;
    image.Load("Components/Characters/Batman.png",0.8);
    image.Render(105,315);
    image.Free();
}

void game::Superman()
{
    LTexture image;
    image.Load("Components/Characters/Superman.png", 0.8);
    image.Render(105,315);
    image.Free();
}

bool game::Change_Characters()
{
    int x,y;
    SDL_GetMouseState(&x,&y);
    if((x > 149 && x < 162) || (x > 88 && x < 101) || (y > 322 & y < 338))
    {
        return true;
    } 
    return false;
}

void game::RenderNextButton()
{
    LTexture image;
    image.Load("Components/image/nextRight.png" , 1);
    image.Render(149,322);
    image.Load("Components/image/nextLeft.png", 1);
    image.Render(88,322);
    image.Free();

}

void game::RenderGameOver()
{
    LTexture image;
    image.Load("Components/image/GameOver", 1);
    image.Render((SCREEN_WIDTH - image.GetWid())/2 , 150);
    image.Free();

}

void game::RenderMedals()
{
    LTexture image;
    if(Score > 20 && Score <= 50)
    {
        image.Load("Components/image/Silver.png", scaleNum);
    }
    else if(Score > 50)
    {
        image.Load("Components/image/Gold.png", scaleNum);
    }
    else
    {
        image.Load("Components/image/Bronze.png",scaleNum);
    }
    image.Render(82,275);
    image.Free();
}


void game::replay()
{
    LTexture image;
    image.Load("Components/image/Replay.png",1);
    image.Render((SCREEN_WIDTH - image.GetWid())/2 , 380);
    image.Free();

}

bool game::checkReplay()
{
    int x,y;
    SDL_GetMouseState(&x,&y);
    if(x > (SCREEN_WIDTH - 100)/2 && x < (SCREEN_WIDTH + 180) /2 && y > 380 && y < 420)
    {
        return true;
    }
    return false;
}

void game::Restart()
{
    Die = false;
    Score = 0;
    Gothem.resetTime();
}








