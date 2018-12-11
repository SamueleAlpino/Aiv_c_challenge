#define SDL_MAIN_HANDLED
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <string.h>
#include "clock.h"

const int WINDOW_HEIGHT = 480;
const int WINDOW_WIDTH = 640;

time_t theTime;
struct tm *aTime;
int seconds = 0;


int main(int argc, char **argv)
{
    //Init Window
    SDL_Window *mainWindow = NULL;  //To hold the main window
    SDL_Renderer *renderer = NULL;  //To hold the renderer
  
    //Get Time
    theTime = time(NULL);
	aTime = localtime(&theTime);
	seconds = aTime->tm_sec;
    
    SDL_Rect targetRect;          
    SDL_Texture *bmpTexture; 

    //Initialize SDL and check for errors
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("ERROR: could not initialize SDL.");
    }

    //Create a window
    mainWindow = SDL_CreateWindow("CHALLENGE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!mainWindow)
    {
        printf("ERROR: could not initialize mainWindow.");
    }

    //Initialize renderer
    renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

    clock_t* my_clock = init_clock("hand.png",WINDOW_WIDTH/2, WINDOW_HEIGHT / 2,0,renderer);
    
    
    //Define rectangle where pacman image is to be blitted
    targetRect.w = 30;
    targetRect.h = 30;
    targetRect.x = (WINDOW_WIDTH / 2) - (targetRect.w / 2);
    targetRect.y = (WINDOW_HEIGHT / 2) - (targetRect.h / 2);

    //Main game loop
    while (1)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            //Quit when user x's out the window
            if (e.type == SDL_QUIT)
            {
                return 0;
            }

            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    return 0;
                }
            }
        }

        move_clock(renderer, my_clock,&targetRect, seconds);
        SDL_RenderClear(renderer);
     //   SDL_RenderCopy(renderer, bmpTexture, NULL, &targetRect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(mainWindow);
    SDL_DestroyTexture(bmpTexture);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
