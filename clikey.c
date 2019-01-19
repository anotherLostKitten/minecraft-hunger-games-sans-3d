#include <SDL2/SDL.h>
#include "keysdown.h"

int handlekey(SDL_Event event,struct keysdown* keys){
    int multiplier = 0;
    switch(event.type){
        case SDL_KEYDOWN:
            multiplier=1; 
        case SDL_KEYUP:
            switch(event.key.keysym.sym){
                case SDLK_RIGHT:
                case SDLK_d:
                    keys->rightd=multiplier;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    keys->downs=multiplier;
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                        keys->lefta=multiplier;
                        break;
                case SDLK_UP:
                case SDLK_w:
                        keys->upw=multiplier;
                        break;
                case SDLK_z:
                case SDLK_j:
                        if(multiplier==1)
                            keys->zj=1;
                        break;
                case SDLK_x:
                case SDLK_k:
                        if(multiplier==1)
                            keys->xk=1;
                        break;
                case SDLK_c:
                case SDLK_l:
                        if(multiplier==1)
                            keys->cl=1;
                        break;
            }
            break;
        case SDL_QUIT:
            keys->quit=1;
        default:
            break;
    } 
}
void printkeys(struct keysdown* keys){
    printf("left %d right %d up %d down %d zj %d xk %d cl %d\n",keys->lefta,keys->rightd,keys->upw,keys->downs,keys->zj,keys->xk,keys->cl);
}
