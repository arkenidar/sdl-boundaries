
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <math.h>
#define math_pi (3.14159265358979323846264338327950288419716939937510)

void logger(char *message)
{
    SDL_Log("%s", message);
}

// pointer for mouse input and/or touch-screen input
struct pointer_struct
{
    int x, y;
    bool click, down, down_previously;
} pointer;
void pointer_init()
{
    pointer.x = pointer.y = 0;
    pointer.click = pointer.down = pointer.down_previously = false;
}
void pointer_input()
{
    Uint32 bitmask = SDL_GetMouseState(&pointer.x, &pointer.y);
    pointer.down_previously = pointer.down;
    pointer.down = bitmask & SDL_BUTTON_LMASK;
    pointer.click = pointer.down && !pointer.down_previously;
}

void draw1(SDL_Renderer *renderer, float pulse, SDL_Texture *texture1, bool shown)
{
    // draw: red pulsating rectangle
    SDL_SetRenderDrawColor(renderer, 255 * pulse, 0, 0, SDL_ALPHA_OPAQUE); // red, pulsating
    SDL_Rect rectangle = {.x = 50, .y = 100, .w = 500, .h = 200};          // position and size of a rectangle
    SDL_RenderFillRect(renderer, &rectangle);                              // fill rectangle with color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);     // white

    // draw: texture image with pulsating transparence (alpha transparence)
    SDL_SetTextureAlphaMod(texture1, SDL_ALPHA_OPAQUE * (1 - pulse)); // alpha transparence, pulsating in opposition
    SDL_RenderCopy(renderer, texture1, NULL, NULL);                   // draw in full size of render target
    SDL_SetTextureAlphaMod(texture1, SDL_ALPHA_OPAQUE);               // not transparent at all, opaque

    // draw: pointer-like image. click shows and hides it.
    int size = 100; // reduced size of texture1 (originally 3000*2943 of assets/rose.png)
    // attach to pointer (centering) and scale down to the size
    SDL_Rect rectangle2 = {.x = pointer.x - size / 2, .y = pointer.y - size / 2, .w = size, .h = size};
    if (shown)
        SDL_RenderCopy(renderer, texture1, NULL, &rectangle2); // draw in rectangle2, if shown
    SDL_ShowCursor(!shown);                                    // show default cursor image or custum cursor image
}

// app entry-point "main()": execution of program begins here and terminates here
int main(int argc, char **argv)
{
    // init program
    logger("this app is starting...");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &window, &renderer);
    SDL_SetWindowTitle(window, "[libsdl.org] SDL window: <title here> (note: this window is resizable)");
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_Texture *texture1 = IMG_LoadTexture(renderer, "assets/rose.png");
    logger(texture1 ? "texture loaded!" : "texture not loaded!");

    pointer_init();

    // states (with initializations)
    bool shown = false;

    // run loop
    bool running = true;
    while (running)
    {
        // === INPUT ===

        pointer_input();

        // event handling loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false; // end the run loop
                break;
            }
        }

        // === PROCESSING ===

        Uint64 ticks = SDL_GetTicks64();                 // elapsed time
        float pulse = fabs(sin(math_pi * ticks / 1000)); // 0.0 <-> 1.0 pulsation in time

        if (pointer.click)  // if clicked ...
            shown = !shown; // alternate: show/hide

        // === OUTPUT ===

        // clear to draw
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // white
        SDL_RenderClear(renderer);                                         // clear screen with white

        // == DRAW ==

        draw1(renderer, pulse, texture1, shown);

        // end draw
        SDL_RenderPresent(renderer);

    } // end of loop

    // end program
    logger("this app is terminating...");
    SDL_DestroyTexture(texture1);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

} // end of program
