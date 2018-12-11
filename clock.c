#include "clock.h"

#define PI = 3.147;

int get_angle(int seconds){

    int angle_to_return = (360/60) * seconds; 
}

clock_t* init_clock(const char* path, int pos_x, int pos_y, int start_seconds, SDL_Renderer* renderer)
{
    clock_t* clock = SDL_malloc(sizeof(clock_t));
    if(!clock){
        fprintf(stderr, "could not allocate memory for clock_t structure\n");
        return NULL;
    }
    SDL_memset(clock, 0, sizeof(clock_t));

    int width;
    int height;
    int color_channel;

    unsigned char* data = stbi_load(path, &width, &height, &color_channel, 4);

    clock->hand = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height);
    if(!clock->hand){
        SDL_Log("could not create texture [%s]", SDL_GetError());
        return NULL;
    }

    int pitch            = 0;
    unsigned char* pixel = NULL;

    if (SDL_LockTexture( clock->hand, NULL, (void **)&pixel, &pitch))
    {
        SDL_Log("Unable to lock texture: %s", SDL_GetError());
        return NULL;
    }

    SDL_memset(pixel, 0, width * height * color_channel);
    SDL_memcpy(pixel, data, width * height * color_channel);
    SDL_UnlockTexture( clock->hand);

    clock->width = width;
    clock->height = height;
    clock->position_x = pos_x;
    clock->position_y = pos_y;
    clock->angle = 0;

    clock->pivot.x = clock->width / 2;
    clock->pivot.y = clock->height - 10;

    return clock;
}

void move_clock(SDL_Renderer* renderer, clock_t* clock, SDL_Rect* dest, int current_second){

int angle = get_angle(current_second);
SDL_RenderCopyEx(renderer, clock->hand, NULL, dest,angle , &clock->pivot, SDL_FLIP_NONE);
}
