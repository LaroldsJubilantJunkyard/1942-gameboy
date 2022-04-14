#ifndef COMMON_HEADER
#define COMMON_HEADER set
#include <gb/gb.h>

#define GAMEFIRSTLOAD 0
#define COPYRIGHT_GAMESTATE 1
#define LAROLDSJUBILANTJUNKYARD_GAMESTATE 2
#define STARTSCREEN_GAMESTATE 3
#define MENUSCREEN_GAMESTATE 4
#define NEXTLEVEL_GAMESTATE 5
#define GAMEPLAY_GAMESTATE 6
#define RESULTS_GAMESTATE 7
#define GAMEOVER_GAMESTATE 8

#define FADE_STEPS 3
#define FADE_SPRITES 1
#define FADE_BACKGROUND 2

#define NUMBER_OF_BACKGROUND_PALETTES 7
#define NUMBER_OF_SPRITE_PALETTES 5
#define FONT_PALETTE_INDEX 6

#define BULLETS_TILES_START SmallEnemyPlane_TILE_COUNT+PlayerPlane_TILE_COUNT
#define MEDIUM_EXPLOSION_TILES_START SmallEnemyPlane_TILE_COUNT+PlayerPlane_TILE_COUNT+Bullets_TILE_COUNT
#define SMALL_EXPLOSION_TILES_START SmallEnemyPlane_TILE_COUNT+PlayerPlane_TILE_COUNT+Bullets_TILE_COUNT+MediumExplosion_TILE_COUNT


#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

extern uint8_t joypadCurrent,joypadPrevious,timer;

extern int16_t playerPlaneX, playerPlaneY;
extern uint8_t drawOnBackground;
extern uint32_t score;

extern uint8_t currentLevel;


void DrawText(uint8_t x, uint8_t y, unsigned char *text);
void DrawTextWithPalette(uint8_t x, uint8_t y, unsigned char *text,uint8_t palette);
void DrawNumber(uint8_t x,uint8_t y, uint32_t number,uint8_t digits);

void DrawNumberWithPalette(uint8_t x,uint8_t y, uint32_t number,uint8_t digits,uint8_t palette);

void FadeIn(uint8_t fadeTarget);
void FadeOut(uint8_t fadeTarget);



typedef struct LevelData{

    uint8_t minEnemiesBeforeSpawnNew;
    uint32_t travelDistance;
}LevelData;

#endif