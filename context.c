#include "context.h"
#include <stdio.h>

int new_context(context_t* context, int width, int height, const char* title)
{
    int ret = 0;
    //Initialize SDL and check for errors
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("ERROR: could not initialize SDL.");
        goto cleanup;
    }
  
    context->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!context->window)
    {
        printf("ERROR: could not initialize mainWindow.");
        goto cleanup_window;
    }
    //Initialize renderer
    context->renderer = SDL_CreateRenderer(context->window , -1, SDL_RENDERER_ACCELERATED);
    if (!context->renderer)
    {
        printf("ERROR: could not initialize renderer.");
        goto cleanup_renderer;
    }

    context->width = width;
    context->height = height;

    goto cleanup;

cleanup_renderer:
    SDL_DestroyRenderer(context->renderer);
cleanup_window:
    SDL_DestroyWindow(context->window);
    SDL_Quit();
cleanup:
    return ret;
}