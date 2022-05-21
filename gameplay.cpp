#include "gameplay.h"
#include "utils.h"
#include <iostream>

void game::TakeInput()
{
    while(SDL_PollEvent(&Event) != 0)
    {
        if (Event.type == SDL_QUIT)
        {
            PlayerInput.Type = input::QUIT;
            Quit = true;
        }
        else if (Event.type == SDL_MOUSEBUTTONDOWN || (Event.type == SDL_KEYDOWN && 
		(Event.key.keysym.sym == SDLK_SPACE || Event.key.keysym.sym == SDLK_UP) && Event.key.repeat == 0) )
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
    InitGraphic();
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
    ReleaseGraphic();
}

void game::ReleaseGraphic()
{
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    SDL_DestroyRenderer( gRenderer );
    gRenderer = NULL;
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

bool game::InitGraphic()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		cout << "SDL could not initialize! SDL Error: %s\n" <<  SDL_GetError() << endl; ;
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			cout <<"Warning: Linear texture filtering not enabled!" << endl;
		}

		gWindow = SDL_CreateWindow( "Flappy Doge", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		if( gWindow == NULL )
		{
			cout <<  "Window could not be created! SDL Error: %s\n", SDL_GetError() ;
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				cout << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError() ;
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					cout <<  "SDL_image could not initialize! SDL_image Error: %s\n" <<  IMG_GetError() ;
					success = false;
				}

				if( TTF_Init() == -1 )
				{
					cout <<  "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() ;
					success = false;
				}
			}
		}
	}

	return success;
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

	for (signed char i = len - 1; i >= 0; i--)
	{
		signed char number = s[i] - '0';
		if (number == 1)
		{
			image.Load("res/number/small/1.png", scaleNum);
		}
		else if (number == 2)
		{
			image.Load("res/number/small/2.png", scaleNum);
		}
		else if (number == 3)
		{
			image.Load("res/number/small/3.png", scaleNum);
		}
		else if (number == 4)
		{
			image.Load("res/number/small/4.png", scaleNum);
		}
		else if (number == 5)
		{
			image.Load("res/number/small/5.png", scaleNum);
		}
		else if (number == 6)
		{
			image.Load("res/number/small/6.png", scaleNum);
		}
		else if (number == 7)
		{
			image.Load("res/number/small/7.png", scaleNum);
		}
		else if (number == 8)
		{
			image.Load("res/number/small/8.png", scaleNum);
		}
		else if (number == 9)
		{
			image.Load("res/number/small/9.png", scaleNum);
		}
		else
		{
			image.Load("res/number/small/0.png", scaleNum);
		}
		image.Render(260 - image.GetWid() * (len - i - 1) * 0.75 - 5 * (len - i - 1), 268);
	}
	image.Free();
}

void game::Render_Score_Large()
{
    string s = to_string(Score);
	signed char len = s.length();
	LTexture image;

	for (signed char i = 0; i < len; i++)
	{
		signed char number = s[i] - '0';
		if (number == 1)
		{
			image.Load("res/number/large/1.png", 1);
		}
		else if (number == 2)
		{
			image.Load("res/number/large/2.png", 1);
		}
		else if (number == 3)
		{
			image.Load("res/number/large/3.png", 1);
		}
		else if (number == 4)
		{
			image.Load("res/number/large/4.png", 1);
		}
		else if (number == 5)
		{
			image.Load("res/number/large/5.png", 1);
		}
		else if (number == 6)
		{
			image.Load("res/number/large/6.png", 1);
		}
		else if (number == 7)
		{
			image.Load("res/number/large/7.png", 1);
		}
		else if (number == 8)
		{
			image.Load("res/number/large/8.png", 1);
		}
		else if (number == 9)
		{
			image.Load("res/number/large/9.png", 1);
		}
		else 
		{
			image.Load("res/number/large/0.png", 1);
		}
		image.Render((SCREEN_WIDTH - (image.GetWid() * len + (len - 1) * 10)) / 2 + (i + 30) * i, 100);
	}
	image.Free();
}

void game::Render_Highest_Score()
{
	ifstream fileIn("Components/data/HighestScore.txt");
	fileIn >> HighestScore; 
	ofstream fileOut("Components/data/HighestScore.txt", ios::trunc);

	if (Score > HighestScore)
	{
		HighestScore = Score;
	}
	string s = to_string(HighestScore);
	signed char len = s.length();
	LTexture image;

	for (signed char i = len-1; i >= 0; i--)
	{
		signed char number = s[i] - '0';
		if (number == 1)
		{
			image.Load("res/number/small/1.png", scaleNum);
		}
		else if (number == 2)
		{
			image.Load("res/number/small/2.png", scaleNum);
		}
		else if (number == 3)
		{
			image.Load("res/number/small/3.png", scaleNum);
		}
		else if (number == 4)
		{
			image.Load("res/number/small/4.png", scaleNum);
		}
		else if (number == 5)
		{
			image.Load("res/number/small/5.png", scaleNum);
		}
		else if (number == 6)
		{
			image.Load("res/number/small/6.png", scaleNum);
		}
		else if (number == 7)
		{
			image.Load("res/number/small/7.png", scaleNum);
		}
		else if (number == 8)
		{
			image.Load("res/number/small/8.png", scaleNum);
		}
		else if (number == 9)
		{
			image.Load("res/number/small/9.png", scaleNum);
		}
		else
		{
			image.Load("res/number/small/0.png", scaleNum);
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
	image.Load("Components/image/message.png", 1);
	image.Render((SCREEN_WIDTH - image.GetWid()) / 2, 180);
	image.Free();
}

void game::Render_Background()
{
	LTexture image;
	image.Load("Components/image/background.png", 1);
	image.Render(0, 0);
	image.Free();
}

void game::Render_Background_Nightmode()
{
	LTexture image;
	image.Load("Components/image/background-night.png", 1);
	image.Render(0, 0);
	image.Free();
}

void game::RenderLand()
{
	LTexture image;
	image.Load("Components/image/land.png", 1);
	image.Render((SCREEN_WIDTH - image.GetWid()) / 2, SCREEN_HEIGHT- image.GetHei());
	image.Free();
}

void game::Resume()
{
	LTexture image;
	image.Load("Components/image/resume.png", 1);
	image.Render(SCREEN_WIDTH - 50, 20);
	image.Free();
}

void game::Pause()
{
	LTexture image;
	image.Load("Components/image/pause.png", 1);
	image.Render(SCREEN_WIDTH - 50, 20);
	image.Free();
}

void game::RenderPauseTab()
{
	LTexture image;
	image.Load("Components/image/pauseTab.png", 1);
	image.Render((SCREEN_WIDTH - image.GetWid()) / 2, 230);
	image.Free();
}

void game::Batman()
{
	LTexture image;
	image.Load("Components/image/Batman.png", 0.8);
	image.Render(105, 315);
	image.Free();
}

void game::Superman()
{
	LTexture image;
	image.Load("Components/image/Superman.png", 0.8);
	image.Render(105, 315);
	image.Free();
}

void game::RenderNextButton()
{
	LTexture image;
	image.Load("Components/image/nextRight.png", 1);
	image.Render(149, 322);
	image.Load("Components/image/nextLeft.png", 1);
	image.Render(88, 322);
	image.Free();
}

bool game::Change_Characters()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (((x > 149 && x < 149+13)  || (x > 88 && x < 88 + 13)) && (y > 322 && y < 322 + 16))
	{
		return true;
	}
	return false;
}

void game::RenderGameOver()
{
	LTexture image;
	image.Load("Components/image/gameOver.png", 1);
	image.Render((SCREEN_WIDTH - image.GetWid()) / 2, 150);
	image.Free();
}

void game::RenderMedals()
{
	LTexture image;
		
	if (Score > 20 && Score <= 50)
	{
		image.Load("Components/image/silver.png", scaleNum);
	}
	else if (Score > 50)
	{
		image.Load("Components/image/gold.png", scaleNum);
	}
	else 
	{
		image.Load("Components/image/bronze.png", scaleNum);
	}
	image.Render(82, 275);

	image.Free();
}

void game::replay()
{
	LTexture image;
	image.Load("Components/image/replay.png", 1);
	image.Render((SCREEN_WIDTH - image.GetWid()) / 2, 380);
	image.Free();
}

bool game::checkReplay()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x > (SCREEN_WIDTH - 100)/2 && x < (SCREEN_WIDTH + 100) / 2 && y > 380 && y < 380 + 60)
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