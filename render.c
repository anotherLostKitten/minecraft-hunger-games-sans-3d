#include "SDL.h"

int setupSDL(){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
}

int quitSDL(){
    SDL_Quit();

}

int render(){

    return 0;
}
