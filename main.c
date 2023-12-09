
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>
#define math_pi (3.14159265358979323846264338327950288419716939937510)

void logger(char *message)
{
    SDL_Log("%s", message);
}

int main(int argc, char **argv)
{
    // init
    logger("this app is starting...");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &window, &renderer);
    SDL_SetWindowTitle(window, "[libsdl.org] SDL window: <title here> (note: this window is resizable)");

    // run loop
    bool running = true;
    while (running)
    {
        // === INPUT ===

        // event handling loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            }
        }

        // === OUTPUT ===

        // clear to draw
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // white
        SDL_RenderClear(renderer);

        // draw
        SDL_Rect rectangle = {.x = 50, .y = 100, .w = 500, .h = 200};
        Uint64 ticks = SDL_GetTicks64();
        float pulse = fabs(sin(math_pi * ticks / 1000));
        SDL_SetRenderDrawColor(renderer, 255 * pulse, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &rectangle);

        // end draw
        SDL_RenderPresent(renderer);
    }

    // end
    logger("this app is terminating...");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
