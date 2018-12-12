
#include <SDL.h>
#include "stb_image.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct analogic_clock{
    SDL_Texture* hand;
    SDL_Rect destination;
    int width;
    int height;
    int angle;
    int position_x;
    int position_y;
    SDL_Point pivot;
}analogic_clock_t;

int get_angle(int seconds); 

analogic_clock_t* init_clock(const char* path, int pos_x, int pos_y, int start_seconds, SDL_Renderer* renderer );

void move_clock(SDL_Renderer *renderer, analogic_clock_t *clock, int current_second);