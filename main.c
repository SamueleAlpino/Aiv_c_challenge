#define SDL_MAIN_HANDLED
#define STB_IMAGE_IMPLEMENTATION
#include <string.h>
#include "context.h"
#include "clock.h"

time_t theTime;
struct tm *aTime;
int seconds = 0;

int main(int argc, char **argv)
{
    SDL_Rect target_rect;
    SDL_Texture *texture;

    context_t ctx ;
    new_context(&ctx, 1024,768,"Test");

    analogic_clock_t *my_clock = init_clock("hand.png", ctx.width / 2, ctx.height / 2, 0, ctx.renderer);

    //Main game loop
    while (1)
    {
        //Get Time
        theTime = time(NULL);
        aTime = localtime(&theTime);
        seconds = aTime->tm_sec;

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

        SDL_RenderClear(ctx.renderer);
        move_clock(ctx.renderer, my_clock, seconds);
        SDL_RenderPresent(ctx.renderer);
    }

    SDL_DestroyWindow(ctx.window);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(ctx.renderer);
    SDL_Quit();

    return 0;
}
