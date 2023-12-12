
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <math.h>

#define math_pi (3.14159265358979323846264338327950288419716939937510)

SDL_Renderer *renderer; // global

enum enum_textures {
    cursor,
    rose,
    enum_textures_count
};
SDL_Texture *textures[enum_textures_count]; // global

bool is_point_in_rectangle(SDL_Rect *rectangle, int x, int y) {
    return x >= rectangle->x && y >= rectangle->y &&
           x <= (rectangle->x + rectangle->w) &&
           y <= (rectangle->y + rectangle->h);
}

void logger(char *message) {
    SDL_Log("%s", message);
}

// pointer for mouse input and/or touch-screen input
struct pointer_struct {
    int x, y;
    bool click, down, down_previously;
} pointer;

void pointer_init() {
    pointer.x = pointer.y = 0;
    pointer.click = pointer.down = pointer.down_previously = false;
}

void pointer_input() {
    Uint32 bitmask = SDL_GetMouseState(&pointer.x, &pointer.y);
    pointer.down_previously = pointer.down;
    pointer.down = bitmask & SDL_BUTTON_LMASK;
    pointer.click = pointer.down && !pointer.down_previously;
}

void draw_pulsating() {

    Uint64 ticks = SDL_GetTicks64();                 // elapsed time
    double pulse = fabs(sin(math_pi * ((double) ticks / 1000))); // 0.0 <-> 1.0 pulsation in time

    // draw: red pulsating rectangle
    if (true) {
        SDL_SetRenderDrawColor(renderer, (Uint8) (255 * pulse), 0, 0, SDL_ALPHA_OPAQUE); // red, pulsating
        SDL_Rect rectangle = {.x = 50, .y = 100, .w = 500, .h = 200};          // position and size of a rectangle
        SDL_RenderFillRect(renderer, &rectangle);                              // fill rectangle with color
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);     // white
    }

    // draw: texture image with pulsating transparence (alpha transparence)
    if (true) {
        SDL_SetTextureAlphaMod(textures[rose],
                               SDL_ALPHA_OPAQUE * (1 - pulse)); // alpha transparence, pulsating in opposition
        SDL_RenderCopy(renderer, textures[rose], NULL, NULL);                   // draw in full size of render target
        SDL_SetTextureAlphaMod(textures[rose], SDL_ALPHA_OPAQUE);               // not transparent at all, opaque
    }
}

void draw_pointer(bool shown) {
    // draw: pointer-like image. click shows and hides it.
    int size = 50; // reduced size of texture1 (originally 3000*2943 of assets/rose.png)
    // attach to pointer (centering) and scale down to the size
    SDL_Rect rectangle2 = {.x = pointer.x /* - size / 2 */, .y = pointer.y /* - size / 2 */, .w = size, .h = size};
    if (shown)
        SDL_RenderCopy(renderer, textures[cursor], NULL, &rectangle2); // draw in rectangle2, if shown
    SDL_ShowCursor(!shown);                                    // show default cursor image or custom cursor image
}

void draw_checkbox(int x, int y, int size1, int size2, bool *checkbox_is_checked_state) {
    int size_extern = size1;
    SDL_Rect rectangle_checkbox_background = {.x = x, .y = y, .w = size_extern, .h = size_extern};

    bool is_inside_checkbox = is_point_in_rectangle(&rectangle_checkbox_background, pointer.x, pointer.y);
    if (pointer.click && is_inside_checkbox)
        *checkbox_is_checked_state = !*checkbox_is_checked_state;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); // black
    SDL_RenderFillRect(renderer, &rectangle_checkbox_background);

    if (*checkbox_is_checked_state) {
        int size_intern = size2;
        int size_diff = size_extern - size_intern;
        SDL_Rect rectangle_checkbox_checkmark = {
                .x = x + size_diff / 2,
                .y = y + size_diff / 2,
                .w = size_intern, .h = size_intern};

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE); // green
        SDL_RenderFillRect(renderer, &rectangle_checkbox_checkmark);
    }
}

// app entry-point "main()": execution of program begins here and terminates here
int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv) {
    // init program
    logger("this app is starting...");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    ///SDL_Renderer *renderer; // it was made a global variable
    SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &window, &renderer);
    SDL_SetWindowTitle(window, "[libsdl.org] SDL window: <title here> (note: this window is resizable)");
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    textures[cursor] = IMG_LoadTexture(renderer, "assets/cursor.png");
    textures[rose] = IMG_LoadTexture(renderer, "assets/rose.png");
    bool textures_loaded = true;
    for (int i = 0; i < sizeof textures / sizeof(SDL_Texture *); i++) {
        if (textures[i] == NULL) {
            textures_loaded = false;
            break;
        }
    }
    logger(textures_loaded ? "textures loaded!" : "textures not loaded!");

    pointer_init();

    // states (with initializations)
    bool shown = true;

    // states of check-boxes
    bool checkbox_is_checked[4] = {true, false, true, true};

    // run loop
    bool running = true;
    while (running) {
        // === INPUT ===

        pointer_input();

        // event handling loop
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false; // end the run loop
                    break;
            }
        }

        // === PROCESSING ===

        ///if (pointer.click)  /* if clicked ... */ shown = !shown; /* alternate: show/hide */

        // === OUTPUT ===

        // clear to draw
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // white
        SDL_RenderClear(renderer);                                         // clear screen with white

        // == DRAW ==

        draw_pulsating();

        // add check-boxes (visual+behaviour)
        for (int i = 0; i < sizeof checkbox_is_checked / sizeof(bool); i++)
            draw_checkbox(10, 10 + 70 * i, 50, 30, checkbox_is_checked + i);

        draw_pointer(shown);

        // end draw
        SDL_RenderPresent(renderer);

    } // end of loop

    // end program
    logger("this app is terminating...");
    for (int i = 0; i < sizeof textures / sizeof(SDL_Texture *); i++)
        SDL_DestroyTexture(textures[i]);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

} // end of program
