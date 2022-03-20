<<<<<<< HEAD
#ifndef COMMON_HEADER
#define COMMON_HEADER set

#define GAMEFIRSTLOAD 0
#define COPYRIGHT_GAMESTATE 1
#define LAROLDSJUBILANTJUNKYARD_GAMESTATE 2
#define STARTSCREEN_GAMESTATE 3
#define MENUSCREEN_GAMESTATE 4
#define NEXTLEVEL_GAMESTATE 5
#define GAMEPLAY_GAMESTATE 6
#define RESULTS_GAMESTATE 7
#define OPTIONS_GAMESTATE 8
#define PASSWORD_GAMESTATE 9

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

extern uint8_t joypadCurrent,joypadPrevious,timer;

extern int16_t playerPlaneX, playerPlaneY;
extern uint8_t drawOnBackground;

void DrawText(uint8_t x, uint8_t y, unsigned char *text);
void DrawTextWithPalette(uint8_t x, uint8_t y, unsigned char *text,uint8_t palette);
void DrawNumber(uint8_t x,uint8_t y, uint32_t number,uint8_t digits);
=======
#ifndef COMMON_HEADER 
#define COMMON_HEADER set

#include "gb/gb.h"

#define MAX_NUMBER_CACTUS 5
#define DINOSAUR_LEFT 32
#define DINOSAUR_MAX_NUMBER_OF_SPRITES 8

#define GAME_FIRST_LOAD 255
#define MENU 0
#define LEVEL_SELECT 1
#define GAMEPLAY 2
#define GAME_OVER 3

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define FADE_STEPS 3
#define FADE_SPRITES 1
#define FADE_BACKGROUND 2

#define NUMBER_OF_BACKGROUND_PALETTES 7
#define NUMBER_OF_SPRITE_PALETTES 5
#define FONT_PALETTE_INDEX 6

typedef struct Obstacle{

    int16_t x;
    uint8_t active;
    uint8_t type;
    uint8_t done;

}Obstacle;

typedef struct Level{
    uint8_t *tiles;
    uint8_t tileCount;
    uint8_t obstacleOffset;
    uint8_t *map;
    uint8_t *map_attributes;
    unsigned char *name;
} Level;

extern uint16_t backgroundFadeColors[];
extern uint16_t spriteFadeColors[];

extern Obstacle cactii[MAX_NUMBER_CACTUS];
extern const Level levels[];

extern uint8_t fadeAmount,joypadCurrent,joypadPrevious,started,frame,health,activeCatii,level,state,nextState,startSprite,health,activeCatii,level,state,nextState,startSprite;
extern uint16_t frameCounter,damageBlinker,spawnX,counter;
extern int16_t moveSpeed,jumpVelocity,aboveGround,dinoX;
extern uint32_t score;
 
void ClearWindowTopRow();
void FadeIn(uint8_t spritesToo);
void FadeOut(uint8_t spritesToo);
void DrawNumber(uint8_t x,uint8_t y, uint32_t number,uint8_t digits);
void DrawTextWithPalette(uint8_t x, uint8_t y, unsigned char *text );
void SetColorPalettesItem(uint16_t* original,uint16_t* palette,uint8_t count);
void UpdateColorPalettes();  

>>>>>>> f56a82457c94c5a3aa9ff8d031aa867438501f7a

#endif