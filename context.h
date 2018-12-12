#include <SDL.h>

typedef struct context{
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
}context_t;

int new_context(context_t* context, int width, int height, const char* title);

