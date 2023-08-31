#ifndef _GAME_H
#define _GAME_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdlib.h>

#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4

#define fireflies_max 7
#define jump_count_max 15
#define light_max 3

extern SDL_Renderer *render;
extern SDL_Window *window;
extern SDL_Surface *player_surface;
extern SDL_Texture *player_texture;
extern SDL_Texture *mask_texture;
extern SDL_Rect light_rect;
extern SDL_Texture *light_texture;
extern SDL_Texture *firefly_texture;
extern SDL_Texture *bg_texture;

extern bool is_jump;

struct Lights{
    SDL_Rect rect;
};

struct Fireflies{
    SDL_Rect rect;
    int move_direction;
};

struct Player{
    SDL_Rect rect;
    SDL_Rect src_rect;
    int direction;
    bool moving;
    int animation_index;
    int animation_timer;
};

extern struct Player player;
extern struct Fireflies fireflies[fireflies_max];
extern struct Lights lights[light_max];

extern int jump_count;

void game_init();
void load_textures();
void move_player();
void HandleEvent();
void render_player();
void spawn_fireflies();
void move_fireflies();
void player_jump();

#endif
