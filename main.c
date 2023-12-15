
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <math.h>

#define math_pi (3.14159265358979323846264338327950288419716939937510)

SDL_Renderer *renderer; // global variable (common)
TTF_Font *font;         // global variable (common)

enum enum_textures
{
    cursor,
    rose,
    enum_textures_count // always last, to keep count ("enum" keyword kind of counts)
};
SDL_Texture *textures[enum_textures_count]; // global variable (common)

bool is_point_in_rectangle(SDL_Rect *rectangle, int x, int y)
{
    return x >= rectangle->x && y >= rectangle->y &&
           x <= (rectangle->x + rectangle->w) &&
           y <= (rectangle->y + rectangle->h);
}

void logger(char *message)
{
    SDL_Log("%s", message);
}

// pointer for mouse input and/or touch-screen input
struct pointer_struct
{
    int x, y;
    bool click, down, down_previously;
} pointer; // global variable (common)

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

void draw_pulsating()
{

    Uint64 ticks = SDL_GetTicks64();                            // elapsed time
    double pulse = fabs(sin(math_pi * ((double)ticks / 1000))); // 0.0 <-> 1.0 pulsation in time

    // draw: red pulsating rectangle
    if (true)
    {
        SDL_SetRenderDrawColor(renderer, (Uint8)(255 * pulse), 0, 0, SDL_ALPHA_OPAQUE); // red, pulsating
        SDL_Rect rectangle = {.x = 50, .y = 100, .w = 500, .h = 200};                   // position and size of a rectangle
        SDL_RenderFillRect(renderer, &rectangle);                                       // fill rectangle with color
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);              // white
    }

    // draw: texture image with pulsating transparence (alpha transparence)
    if (true)
    {
        SDL_SetTextureAlphaMod(textures[rose],
                               SDL_ALPHA_OPAQUE * (1 - pulse));   // alpha transparence, pulsating in opposition
        SDL_RenderCopy(renderer, textures[rose], NULL, NULL);     // draw in full size of render target
        SDL_SetTextureAlphaMod(textures[rose], SDL_ALPHA_OPAQUE); // not transparent at all, opaque
    }
}

void draw_pointer(bool shown)
{
    // draw: pointer-like image. click shows and hides it.
    int size = 50; // reduced size of texture1 (originally 3000*2943 of assets/rose.png)
    // attach to pointer (centering) and scale down to the size
    SDL_Rect rectangle2 = {.x = pointer.x /* - size / 2 */, .y = pointer.y /* - size / 2 */, .w = size, .h = size};
    if (shown)
        SDL_RenderCopy(renderer, textures[cursor], NULL, &rectangle2); // draw in rectangle2, if shown
    SDL_ShowCursor(!shown);                                            // show default cursor image or custom cursor image
}

int draw_checkbox(int x, int y, int size1, int size2,
                  bool *checkbox_is_checked_state,
                  char *check_box_labels_string)
{
    TTF_SetFontSize(font, size1);

    int size_extern = size1;
    SDL_Rect rectangle_checkbox_background = {.x = x, .y = y, .w = size_extern, .h = size_extern};

    // ☐,☑ used. usable also: ☒ ◉ ◎
    const size_t text_checked_size = 1001;
    char text_checked_no[text_checked_size];
    char text_checked_yes[text_checked_size];
    snprintf(text_checked_no, text_checked_size, "\u2610 %s", check_box_labels_string);
    snprintf(text_checked_yes, text_checked_size, "\u2611 %s", check_box_labels_string);

    char *text = *checkbox_is_checked_state ? text_checked_yes : text_checked_no;
    int w, h;
    /// TTF_SizeUTF8(font, text, &w, &h);

    // calculate size
    SDL_Color color_foreground_sizing = {.r = 0, .g = 0, .b = 0, .a = SDL_ALPHA_OPAQUE}; // black
    // TTF_RenderUTF8_Blended_Wrapped -> TTF_RenderUTF8_Solid_Wrapped
    SDL_Surface *surface_text_sizing = TTF_RenderUTF8_Solid_Wrapped(font, text, color_foreground_sizing, 0);
    // size
    w = surface_text_sizing->w;
    h = surface_text_sizing->h;
    SDL_FreeSurface(surface_text_sizing);

    SDL_Rect rectangle_checkbox_label = {.x = x, .y = y, .w = w, .h = h};
    rectangle_checkbox_label.x += size_extern + 10;

    bool is_inside_checkbox = false;

    is_inside_checkbox =
        is_inside_checkbox || is_point_in_rectangle(&rectangle_checkbox_background, pointer.x, pointer.y);

    is_inside_checkbox = is_inside_checkbox || is_point_in_rectangle(&rectangle_checkbox_label, pointer.x, pointer.y);

    if (pointer.click && is_inside_checkbox)
        *checkbox_is_checked_state = !*checkbox_is_checked_state;

    if (true)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); // black
        SDL_RenderFillRect(renderer, &rectangle_checkbox_background);

        if (*checkbox_is_checked_state)
        {
            int size_intern = size2;
            int size_diff = size_extern - size_intern;
            SDL_Rect rectangle_checkbox_checkmark = {
                .x = x + size_diff / 2,
                .y = y + size_diff / 2,
                .w = size_intern,
                .h = size_intern};

            SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE); // green
            SDL_RenderFillRect(renderer, &rectangle_checkbox_checkmark);
        }
    }

    // add text

    SDL_Color color_foreground = {.r = 0, .g = 0, .b = 0, .a = SDL_ALPHA_OPAQUE}; // black

    SDL_Color color_background_red = {.r = 255, .g = 0, .b = 0, .a = SDL_ALPHA_TRANSPARENT};       // red transparent
    SDL_Color color_background_white = {.r = 255, .g = 255, .b = 255, .a = SDL_ALPHA_TRANSPARENT}; // white transparent

    text = *checkbox_is_checked_state ? text_checked_yes : text_checked_no;
    /// TTF_SizeUTF8(font, text, &rectangle_checkbox_label.w, &rectangle_checkbox_label.h);
    // TTF_RenderUTF8_Blended_Wrapped works fine
    SDL_Surface *surface_text = TTF_RenderUTF8_LCD_Wrapped(font, text, color_foreground, is_inside_checkbox ? color_background_red : color_background_white, 0);
    // size
    rectangle_checkbox_label.w = surface_text->w;
    rectangle_checkbox_label.h = surface_text->h;
    /// SDL_FreeSurface(surface_text); // still used below

    SDL_Texture *texture_text = SDL_CreateTextureFromSurface(renderer, surface_text);
    SDL_FreeSurface(surface_text);
    SDL_RenderCopy(renderer, texture_text, NULL, &rectangle_checkbox_label);
    SDL_DestroyTexture(texture_text);

    return rectangle_checkbox_label.h;
}

// app entry-point "main()": execution of program begins here and terminates here
int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{

    // init program
    logger("this app is starting...");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    /// SDL_Renderer *renderer; // it was made a global variable
    SDL_CreateWindowAndRenderer(1000, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &window, &renderer);
    SDL_SetWindowTitle(window,
                       "|| https://github.com/arkenidar/sdl-boundaries || "
                       " [libsdl.org] SDL window title (note: this window is resizable)");

    // images support
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    textures[cursor] = IMG_LoadTexture(renderer, "assets/cursor.png");
    textures[rose] = IMG_LoadTexture(renderer, "assets/rose.png");
    bool textures_loaded = true;
    for (int i = 0; i < enum_textures_count; i++)
    {
        if (textures[i] == NULL)
        {
            textures_loaded = false;
            break;
        }
    }
    logger(textures_loaded ? "textures loaded!" : "textures not loaded!");

    // TTF fonts support
    TTF_Init();
    font = TTF_OpenFont("assets/symbola.ttf", 72);
    logger(font ? "font loaded!" : "font not loaded!");

    pointer_init();

    // states (with initializations)
    /// bool shown = true;

    // states of check-boxes
    bool checkbox_is_checked[4] = {true, false, true, true};

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

        /// if (pointer.click)  /* if clicked ... */ shown = !shown; /* alternate: show/hide */

        // === OUTPUT ===

        // clear to draw
        SDL_SetRenderDrawColor(renderer, 188, 188, 188, SDL_ALPHA_OPAQUE); // grey
        SDL_RenderClear(renderer);                                         // clear screen with white

        // == DRAW ==

        /// draw_pulsating();

        // add check-boxes (visual+behaviour)

        char *check_box_labels_strings[sizeof checkbox_is_checked / sizeof(bool)] = {
            "option 1", "option 2 ...", "another option in \n 3 lines \n !!!!", "last option"};

        int y = 10;
        int height;
        for (int i = 0; i < sizeof checkbox_is_checked / sizeof(bool); i++)
        {
            height = draw_checkbox(10, y, 50, 30, checkbox_is_checked + i, check_box_labels_strings[i]);
            y += height + 10;
        }

        /// draw_pointer(shown);

        // end draw
        SDL_RenderPresent(renderer);

    } // end of loop

    // end program
    logger("this app is terminating...");
    for (int i = 0; i < enum_textures_count; i++)
        SDL_DestroyTexture(textures[i]);
    TTF_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

} // end of program
