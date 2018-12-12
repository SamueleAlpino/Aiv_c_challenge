#include "clock.h"
#define SCALE 0.80;
int get_angle(int seconds)
{
    int angle_to_return = (360 / 60) * seconds;
    return angle_to_return;
}

analogic_clock_t *init_clock(const char *path, int pos_x, int pos_y, int start_seconds, SDL_Renderer *renderer)
{
    analogic_clock_t *clock = malloc(sizeof(analogic_clock_t));
    if (!clock)
    {
        fprintf(stderr, "could not allocate memory for clock_t structure\n");
        return NULL;
    }

    SDL_memset(clock, 0, sizeof(analogic_clock_t));

    int width;
    int height;
    int color_channel;

    unsigned char *data = stbi_load(path, &width, &height, &color_channel, 4);

    clock->hand = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height);

    if (!clock->hand)
    {
        SDL_Log("could not create texture [%s]", SDL_GetError());
        return NULL;
    }

    int pitch = 0;
    unsigned char *pixel = NULL;

    if (SDL_LockTexture(clock->hand, NULL, (void **)&pixel, &pitch))
    {
        SDL_Log("Unable to lock texture: %s", SDL_GetError());
        return NULL;
    }

    SDL_memset(pixel, 0, width * height * color_channel);
    SDL_memcpy(pixel, data, width * height * color_channel);
    SDL_UnlockTexture(clock->hand);

    clock->width = width;
    clock->height = height;
    clock->position_x = pos_x;
    clock->position_y = pos_y;
    clock->angle = 0;
    //find right pivot position
    clock->pivot.x = (clock->width / 2) * SCALE;
    clock->pivot.y = (clock->height - 151) * SCALE;
   
    return clock;
}

void move_clock(SDL_Renderer *renderer, analogic_clock_t *clock, int current_second)
{
    int angle = get_angle(current_second);
    clock->destination.x = clock->position_x - clock->width;
    clock->destination.y = clock->position_y - clock->height;
    clock->destination.w = clock->width * SCALE;
    clock->destination.h = clock->height * SCALE;
    clock->angle         = angle;
    SDL_RenderCopyEx(renderer, clock->hand, NULL,  &clock->destination, angle, &clock->pivot , SDL_FLIP_NONE);
}
