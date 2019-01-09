#include <SDL2/SDL.h>

int main(){return 0;}


int handlekey(struct keysdown keys){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        int crementer = 0;
        keys->xk=0;
        keys->zj=0;
        keys->cl=0;
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
        keys->xk=0;
        keys->zj=0;
        keys->cl=0;
    }
}
