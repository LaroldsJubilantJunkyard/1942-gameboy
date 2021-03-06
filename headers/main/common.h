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
#define GAMEOVER_GAMESTATE 8

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define BULLETS_START SmallEnemyPlane_TILE_COUNT+PlayerPlane_TILE_COUNT
#define SMALL_EXPLOSION_TILES_START BULLETS_START+Bullets_TILE_COUNT
#define MEDIUM_EXPLOSION_TILES_START SMALL_EXPLOSION_TILES_START+SmallExplosion_TILE_COUNT

extern uint8_t joypadCurrent,joypadPrevious,timer;

extern int16_t playerPlaneX, playerPlaneY;
extern uint8_t drawOnBackground;


void DrawText(uint8_t x, uint8_t y, unsigned char *text);
void DrawTextWithPalette(uint8_t x, uint8_t y, unsigned char *text,uint8_t palette);
void DrawNumber(uint8_t x,uint8_t y, uint32_t number,uint8_t digits);

void DrawNumberWithPalette(uint8_t x,uint8_t y, uint32_t number,uint8_t digits,uint8_t palette);

#endif