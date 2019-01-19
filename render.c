#include "render.h"

#define screenwidth 640
#define screenheight 480
#define tiledim 32

SDL_Renderer* renderer;
SDL_Window* window;
SDL_Surface* surface;
SDL_Texture* texture;

int setupSDL(){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    atexit(SDL_Quit);
    if (SDL_CreateWindowAndRenderer(screenwidth+100,screenheight,SDL_WINDOW_INPUT_FOCUS,&window,&renderer)) {
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
    SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
}

int render(struct player* player,struct Grid* grid,struct player* playarray,struct enemy* enemyarray,struct equipment* equarray){
    int x = player->coords[1];
    int y = player->coords[0];
    const int htiles = screenwidth/tiledim ;
    const int vtiles = screenheight/tiledim;
    puts("clearing for render");
    //Clear screen
    SDL_RenderClear(renderer);
    //Render texture to screen
    SDL_Rect textrect,drawrect;
    textrect.y = 0;
    textrect.h = textrect.w = drawrect.h = drawrect.w = 32;
    for(int i=0;i<htiles;i++){
        for(int j=0;j<vtiles;j++){
            char* wallstat = gridrc(grid,y+j-vtiles/2,x+i-htiles/2);
            textrect.x = 64+32*(wallstat?*wallstat:0);
            drawrect.x = 32*i, drawrect.y = 32*j;
            SDL_RenderCopy(renderer,texture,&textrect,&drawrect);
        }
    }
    puts("rendering tiles");
    for(int i=0;i<NUM_PLAYERS;i++){
        if(playarray[i].coords[0]==-1) continue;
        int px = playarray[i].coords[1];
        int py = playarray[i].coords[0];
        textrect.y = textrect.x = 0;
        drawrect.x = 32*(px-x+htiles/2);
        drawrect.y = 32*(py-y+vtiles/2);
        SDL_RenderCopy(renderer,texture,&textrect,&drawrect);
    }
    puts("rendered players");
    for(int i=0;i<MAXENMY;i++){
        if(enemyarray[i].coords[0]==-1) continue;
        int px = enemyarray[i].coords[1];
        int py = enemyarray[i].coords[0];
        textrect.y = 0;
        textrect.x = 32;
        drawrect.x = 32*(px-x+htiles/2);
        drawrect.y = 32*(py-y+vtiles/2);
        SDL_RenderCopy(renderer,texture,&textrect,&drawrect);
    }
    puts("rendered enemies");
    for(int i=0;i<MAXEQ;i++){
        if(equarray[i].coords[0]==-1) continue;
        int px = equarray[i].coords[1];
        int py = equarray[i].coords[0];
        textrect.y = textrect.x = 32;
        drawrect.x = 32*(px-x+htiles/2);
        drawrect.y = 32*(py-y+vtiles/2);
        SDL_RenderCopy(renderer,texture,&textrect,&drawrect);
    }
    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf",23);
    SDL_Color color = {255,255,255};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, "jimbob", color);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    drawrect.x = screenwidth, drawrect.y = 0, drawrect.w = 100, drawrect.h = 100;
    //draw the item pictures to the sides

    //end of drawing item pictures
    SDL_RenderCopy(renderer,Message,NULL,&drawrect);
    //Update screen
    SDL_RenderPresent(renderer);
    return 0;
}
/*   //server side tasks for main server
    srand(time(NULL));
    struct Grid* grid = mkmap(128,128);//this is before deletion
    //send the grid to the client
    int playsem,playshm;
    makeshm("playarray",&playsem,&playshm,sizeof(struct player)*1);
    struct player* playarray;
    accshm(playsem,playshm,-1,&playarray);
    struct keysdown* keys = calloc(sizeof(struct keysdown),1);//NOTE CLIENT SIDE IN FINAL VERSION then it should be written to a pipe, the server should read the struct and execute as of now unimplemented actions based on this.
    makePlayer(grid,playarray);
    struct player* player= &playarray[0];
    int enemysem,enemyshm;
    makeshm("enemyarray",&enemysem,&enemyshm,sizeof(struct enemy)*50);
    struct enemy* enemyarray;
    accshm(enemysem,enemyshm,-1,&enemyarray);
    int equsem,equshm;
    makeshm("equarray",&equsem,&equshm,sizeof(struct enemy)*50);
    struct equipment* equarray;
    accshm(equsem,equshm,-1,&equarray);
    char quit = 0;
    setupSDL();
    SDL_Event event;
    for(int i = 0;i<50;i++){
        makeEnemy(grid,&(enemyarray[i]));
    }
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
        render(player,grid,playarray,enemyarray,equarray);
    }
    accshm(playsem,playshm,1,&playarray);
    accshm(enemysem,enemyshm,1,&enemyarray);
    accshm(equsem,equshm,1,&equarray);
    closeshm("playarray",playsem,playshm);
    closeshm("enemyarray",enemysem,enemyshm);
    closeshm("equarray",equsem,equshm);
    return 0;
}
*/
