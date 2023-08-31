#include "game.h"
#include <stdio.h>
int main(){
    game_init();
    int i;
    load_textures();
    spawn_fireflies();
    bool closed=false;
    SDL_Event event;
    while (!closed){
        SDL_RenderClear(render);
        HandleEvent(event);
        SDL_RenderCopy(render , bg_texture , NULL , NULL);
        SDL_RenderCopy(render , player_texture , &player.src_rect , &player.rect);
        SDL_RenderCopy(render , mask_texture , NULL , NULL);
        for(i=0;i<light_max;i++){
            SDL_RenderCopy(render , light_texture , NULL , &lights[i].rect);
        }
        move_fireflies();
        for (int i=0;i<fireflies_max;i++){
            SDL_RenderCopy(render , firefly_texture , NULL , &fireflies[i].rect);
        }
        if (is_jump){
            player_jump();
        }
        if (player.rect.y < 416 && !is_jump){
            player.rect.y += 10;
        }
        else if (player.rect.y > 416){
            player.rect.y = 416;
        }


        SDL_RenderPresent(render);
        SDL_Delay(1000/60);
    }
}
