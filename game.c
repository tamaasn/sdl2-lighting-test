#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Window *window;
SDL_Renderer *render;

SDL_Surface *player_surface;

SDL_Texture *player_texture;
SDL_Texture *mask_texture;
SDL_Texture *light_texture;
SDL_Texture *firefly_texture;
SDL_Texture *bg_texture;

struct Player player;
struct Fireflies fireflies[fireflies_max];
struct Lights lights[light_max];

SDL_Rect light_rect;
int random_number;
int jump_count=1;

bool is_jump=false;

void spawn_fireflies(){
    for(int i=0;i<fireflies_max;i++){
        fireflies[i].rect.x = rand()%600;
        fireflies[i].rect.y = rand()%400;
        fireflies[i].rect.w = 16;
        fireflies[i].rect.h = 16;
    }
}

void move_fireflies(){
    for(int i=0;i<fireflies_max;i++){
        random_number = rand()%5;
        switch(random_number){
            case 1: fireflies[i].rect.x += 5;break;
            case 2: fireflies[i].rect.x -= 5;break;
            case 3: fireflies[i].rect.y += 5;break;
            case 4: fireflies[i].rect.y -= 5;break;
        }
        if (fireflies[i].rect.x > 624){
            fireflies[i].rect.x -= 5;
        }
        else if (fireflies[i].rect.x < 1){
            fireflies[i].rect.x += 5;
        }
        else if (fireflies[i].rect.y < 1){
            fireflies[i].rect.y += 5;
        }
        else if (fireflies[i].rect.y > 464){
            fireflies[i].rect.y -= 5;
        }
    }
}

void player_jump(){
    if (is_jump){
        jump_count++;
        if(jump_count > jump_count_max){
            is_jump=false;
            jump_count=1;
        }
        player.rect.y -= 30/jump_count;
    }
}


void load_textures(){
    player_surface = IMG_Load("images/player.png");
    player_texture = SDL_CreateTextureFromSurface(render , player_surface);
    SDL_Surface *surface = IMG_Load("images/mask.png");
    mask_texture = SDL_CreateTextureFromSurface(render , surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("images/light.png");
    light_texture = SDL_CreateTextureFromSurface(render , surface);
    surface = IMG_Load("images/firefly.png");
    firefly_texture = SDL_CreateTextureFromSurface(render , surface);
    surface = IMG_Load("images/bg.png");
    bg_texture = SDL_CreateTextureFromSurface(render , surface);
    SDL_FreeSurface(player_surface);
    SDL_FreeSurface(surface);
}

void game_init(){
    player.rect.w = 64;
    player.rect.h = 64;
    player.rect.y = 416;
    player.rect.x = 1;

    player.src_rect.w = 16;
    player.src_rect.h = 16;
    player.src_rect.x = 0;
    player.src_rect.y = 0;

    player.direction = RIGHT;

    player.animation_index=0;
    player.animation_timer=5;

    player.moving = false;

    light_rect.w = 128;
    light_rect.h = 128;
    light_rect.x = 400;
    light_rect.y = 352;

    for (int i =0;i<light_max;i++){
        lights[i].rect.x = i*200;
        lights[i].rect.y = 352;
        lights[i].rect.w = 128;
        lights[i].rect.h = 128;
    }

    Uint32 render_flag = SDL_RENDERER_ACCELERATED;
    window = SDL_CreateWindow("Meow game" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 640,480,0);
    render = SDL_CreateRenderer(window , -1 , render_flag);
    //SDL_SetRenderDrawColor(render , 255 , 255 , 255 , 0);

}

void render_player(){
    SDL_RenderCopy(render , player_texture , NULL,&player.rect);
}

void player_animation(){
    if (player.animation_timer-- < 1){
        if(player.animation_index++ >= 2){
            player.animation_index = 0;
        }
        player.src_rect.x = player.animation_index * 16;
        player.animation_timer=5;
        //printf("%d" , player.src_rect.x);
    }
}

void HandleEvent(SDL_Event event){
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:exit(0);break;
            case SDL_KEYDOWN:
                          switch(event.key.keysym.scancode){
                              case SDL_SCANCODE_A: player.moving=true;player.direction=LEFT;break;
                                case SDL_SCANCODE_D: player.moving=true;player.direction=RIGHT;break;
                                case SDL_SCANCODE_SPACE: is_jump=true;break;
                          }break;
            case SDL_KEYUP:
                          switch(event.key.keysym.scancode){
                                case SDL_SCANCODE_A: player.moving=false;break;
                                case SDL_SCANCODE_D: player.moving=false;break;
                          }break;
        }
    }

    if (player.moving == true){
        switch(player.direction){
            case RIGHT: player.rect.x += 5;player_animation();break;
            case LEFT : player.rect.x -= 5;player_animation();break;
        }
    }
}
