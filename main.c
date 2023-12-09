
#include <SDL2/SDL.h>

void logger(char* message)
{
    SDL_Log("%s", message);
}

int main(int argc, char **argv)
{
    logger("this app is starting...");

    // add here...

    logger("this app is terminating...");
    
    return 0;
}
