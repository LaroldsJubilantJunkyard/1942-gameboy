#ifndef BULLETS_HEADER
#define BULLETS_HEADER set

typedef struct Bullet{

    int16_t x,y;
    uint8_t active;

}Bullet;

#define BULLETS_START SmallEnemyPlane_TILE_COUNT+PlayerPlane_TILE_COUNT+MediumEnemyPlane_TILE_COUNT
#define MAX_NUMBER_BULLETS 5


void SetupBullets();
void SpawnBullet(int16_t x, int16_t y);
uint8_t UpdateAllBullets(uint8_t startingSprite);

extern Bullet bullets[MAX_NUMBER_BULLETS];
extern int16_t minX,minY,maxX,maxY;

#endif