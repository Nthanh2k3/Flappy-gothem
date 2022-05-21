#include"gameplay.h"
#include"utils.h"
#include<time.h>
#include<stdlib.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>



const short int FPS = 60;
const short int FrameDelay = 1000/FPS;
using namespace std;

int main(int argc, char** argv)
{
    Uint32 frameStart;
    short int frameTime;
    game g;
    bool isMenu = 0;
    bool isPause = 0;
    bool isSound = 1;
    bool isSuperman = 0;

    while(!g.Is_Quit())
    {
        frameStart = SDL_GetTicks();
        
        if (g.Is_Die())
        {
            if (isMenu) {
                g.sound.playHit();
                g.Gothem.render();
            }
            g.PlayerInput.Type = game::input::NONE;
            while(g.Is_Die() && !g.Is_Quit())
            {
                g.TakeInput();
                if (isMenu == 1 && g.PlayerInput.Type == game::input::PLAY)
                {
                    if (g.checkReplay())
                    {
                        isMenu = 0;
                    }
                    g.PlayerInput.Type = game::input::NONE;
                }
                if (!isSuperman) g.Render_Background();
                else g.Render_Background_Nightmode();
                g.pipe.render();
                g.land.Render();
                if (isMenu)
                {
                    g.Gothem.render();
                    g.Gothem.fall();
                    g.RenderGameOver();
                    g.RenderMedals();
                    g.Render_Score_Small();
                    g.Render_Highest_Score();
                    g.replay();
                }
                else
                {
                    g.pipe.init();
                    g.Gothem.init(isSuperman); 
                    g.Gothem.render();
                    g.Render_Messages();
                    if (g.PlayerInput.Type == game::input::PLAY)
                    {
                        g.Restart();
                        isMenu = 1;
                        g.PlayerInput.Type = game::input::NONE;
                    }
                    g.land.update();
                }
                g.display();
            }
            g.pipe.init();
        }
        else
        {
            g.TakeInput();

            if (g.PlayerInput.Type == game::input::PAUSE)
            {
                isPause = abs(1 - isPause);
                g.PlayerInput.Type = game::input::NONE;
            }

            if (isPause == 0 && g.PlayerInput.Type == game::input::PLAY)
            {
                if (isSound) g.sound.playBreath();
                g.Gothem.resetTime(); 
                g.PlayerInput.Type = game::input::NONE;
            }

            if (!isSuperman) g.Render_Background();
            else g.Render_Background_Nightmode();
            g.pipe.render();
            g.land.Render();
            g.Gothem.render();
            g.Render_Score_Large();

            if (!isPause)
            {
                g.Gothem.update(g.Get_pipe_Width(), g.Get_pipe_Height());
                g.pipe.Update();
                g.land.update();
                g.Pause();
            }
            else
            {
                g.Resume();
                g.RenderPauseTab();
                g.Render_Score_Small();
                g.Render_Highest_Score();
                g.replay();
                g.sound.RenderSound();
                if (!isSuperman) g.Batman(); else g.Superman();
                g.RenderNextButton();
                if (g.PlayerInput.Type == game::input::PLAY)
                {
                    if (g.checkReplay())
                    {
                        isPause = 0;
                    }
                    else if (g.sound.CheckSound())
                    {
                        isSound = abs(1 - isSound);
                    }
                    else if (g.Change_Characters())
                    {
                        isSuperman = abs(1 - isSuperman);
                        g.Gothem.init(isSuperman);
                    }
                    g.PlayerInput.Type = game::input::NONE;
                }
            }
            g.display();
        }

        
        frameTime = SDL_GetTicks() - frameStart;
        if (FrameDelay > frameTime)
        {
            SDL_Delay(FrameDelay - frameTime);
        }
    }
    return 0;
}
