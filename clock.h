
#include <SDL.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct clock{
    SDL_Texture* hand;
    SDL_Rect destination;
    int width;
    int height;
    int angle;
    int position_x;
    int position_y;
    SDL_Point pivot;

}clock_t;

int get_angle(int seconds); 

struct clock* init_clock(const char* path, int pos_x, int pos_y, int start_seconds, SDL_Renderer* renderer );

void move_clock(SDL_Renderer* renderer, clock_t* clock, SDL_Rect* dest, int current_second);