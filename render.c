#include <SDL2/SDL.h>
#include "player.h"
#include "grid.h"

#define screenwidth 640
#define screenheight 480
#define tiledim 20

SDL_Renderer* renderer;
SDL_Window* window;
SDL_Surface* surface;
SDL_Texture* texture;



int setupSDL(){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    atexit(quitSDL);
    if (SDL_CreateWindowAndRenderer(screenwidth,screenheight,SDL_WINDOW_INPUT_FOCUS,&window,&renderer);) {
        SDL_Log("Unable to initialize window and renderer: %s", SDL_GetError());
        return 1;
    }
    if(!(surface=SDL_LoadBMP("spritesheet.bmp"))){
        SDL_Log("Unable to initialize spritesheet", SDL_GetError());
        return 1;
    }
    if(!(texture = SDL_CreateTextureFromSurface(renderer,surface))){
        SDL_Log("Unable to initialize texture", SDL_GetError());
        return 1;
    }
    
    
}

int quitSDL(){
    SDL_DestroyTexture(texture); 
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
int render(struct player* player,struct Grid* grid){
    int x = player->coords[0];
    int y = player->coords[1];
    const htiles = screenwidth/tiledim ;
    const vtiles = screenheight/tiledim;
    int xoffset = 0,yoffset = 0;
    if(grid->c - x < htiles/2)
        x = grid->c - htiles/2,xoffset = htiles/2 - (grid->c - x);
    else if(x<htiles/2)
        x = htiles/2,xoffset = x - htiles/2;
    if(grid->r - y < vtiles/2)
        y = grid->r - vtiles/2,yoffset = vtiles/2 - (grid->r - y);
    else if(y< vtiles/2)
        y = vtiles/2,yoffset = y - vtiles/2;
    //Clear screen
    SDL_RenderClear(renderer);
    //Render texture to screen
    SDL_Rect textrect,drawrect;
    textrect.y = 0;
    textrect.h = textrect.w = drawrect.h = drawrect.w = 32;
    for(int i=0;i<htiles;i++){
        for(int j=0;j<vtiles;j++){
            textrect.x = 64+32*(*gridrc(grid,i,j));
            drawrect.x = 32*i, drawrect.y = 32*j;
            SDL_RenderCopy(renderer,texture,textrect,drawrect);
        }
    }
    //Update screen
    SDL_RenderPresent(renderer);
    return 0;
}
int main(){
   struct player* player = calloc(1,sizeof(struct player)); 
   player->x = 30;
   player->y = 30;
   struct Grid* grid = mkmap(128,128);
   setupSDL();
   render();
}
