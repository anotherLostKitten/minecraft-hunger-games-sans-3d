#include <SDL2/SDL.h>
#include "keysdown.h"

int handlekey(SDL_Event event,struct keysdown keys){
    switch(event.type){
        case SDL_KEYDOWN:
            crementer = -2;
        case SDL_KEYUP:
            crementer++;
            switch(event.key.keysym.sym){
                case SDLK_RIGHT:
                case SDLK_a:
                    keys->righta+=crementer;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    keys->downs+=crementer;
                    break
                case SDLK_LEFT:
                case SDLK_d:
                        keys->leftd+=crementer;
                        break;
                case SDLK_UP:
                case SDLK_w:
                        keys->upw+=crementer;
                        break;
                case SDLK_z:
                case SDLK_j:
                        if(crementer==1)
                            keys->zj=1;
                        break;
                case SDLK_x:
                case SDLK_k:
                        if(crementer==1)
                            keys->xk=1;
                        break;
                case SDLK_c:
                case SDLK_l:
                        if(crementer==1)
                            keys->cl=1;
                        break;
            }
            break;
        default:
            break;
    } 
}
