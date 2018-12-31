#include <stdio.h>
#include <SDL.h>

int main(int argc, char* argv[])
{
    int rc = SDL_Init(SDL_INIT_VIDEO);
    if (rc < 0) {
        printf("SDL_Init failed (%s)\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "SDL2Test",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("SDL_CreateWindow failed (%s)\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* surface = SDL_GetWindowSurface(window);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0x00, 0x00));
    SDL_UpdateWindowSurface(window);

    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
