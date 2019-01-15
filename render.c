#include <SDL2/SDL.h>
#include "player.h"
#include "grid.h"
#include "cell_auto_mapgen.h"
#include "keysdown.h"
#include "clikey.h"

#define screenwidth 640
#define screenheight 480
#define tiledim 32

SDL_Renderer* renderer;
SDL_Window* window;
SDL_Surface* surface;
SDL_Texture* texture;

void quitSDL();
int setupSDL(){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    atexit(quitSDL);
    if (SDL_CreateWindowAndRenderer(screenwidth,screenheight,SDL_WINDOW_INPUT_FOCUS,&window,&renderer)) {
        SDL_Log("Unable to initialize window and renderer: %s", SDL_GetError());
        return 1;
    }
    if(!(surface=SDL_LoadBMP("spritesheet.bmp"))){
        SDL_Log("Unable to initialize spritesheet %s", SDL_GetError());
        return 1;
    }
    if(!(texture = SDL_CreateTextureFromSurface(renderer,surface))){
        SDL_Log("Unable to initialize texture %s", SDL_GetError());
        return 1;
    }
    
    
}

void quitSDL(){
    SDL_DestroyTexture(texture); 
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
int render(struct player* player,struct Grid* grid,struct player** playarray){
    int x = player->coords[1];
    int y = player->coords[0];
    const int htiles = screenwidth/tiledim ;
    const int vtiles = screenheight/tiledim;
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
            textrect.x = 64+32*(*gridrc(grid,j-vtiles/2+y+yoffset,i-htiles/2+x+xoffset));
            drawrect.x = 32*i, drawrect.y = 32*j;
            SDL_RenderCopy(renderer,texture,&textrect,&drawrect);
        }
    }
    for(int i=0;playarray[i];i++){
        int px = playarray[i]->coords[1];
        int py = playarray[i]->coords[0];
        textrect.y = textrect.x = 0;
        drawrect.x = 32*(px-x+htiles/2+xoffset);
        drawrect.y = 32*(py-y+vtiles/2+yoffset);
        SDL_RenderCopy(renderer,texture,&textrect,&drawrect);
    }
    //Update screen
    SDL_RenderPresent(renderer);
    return 0;
}
int main(){
   struct Grid* grid = mkmap(128,128);
   struct player* player = makePlayer(grid);
   char quit = 0;
   setupSDL();
   SDL_Event event;
   struct keysdown* keys = calloc(sizeof(struct keysdown),1);
   struct player** playarray = calloc(sizeof(struct player*),10);
   playarray[0] = player;
   while(!quit){
        while(SDL_PollEvent(&event)){
            int crementer = 0;
            keys->xk=0;
            keys->zj=0;
            keys->cl=0;
            switch(event.type){
                case SDL_KEYUP:
                case SDL_KEYDOWN:
                    handlekey(event,keys);
                    break;
                case SDL_QUIT:
                    quit = 1;
                    break;
            }
            keys->xk=0;
            keys->zj=0;
            keys->cl=0;
        }
       render(player,grid,playarray);
   }
   return 0;
}
