#ifndef BULLETS_HEADER
#define BULLETS_HEADER set

typedef struct Bullet{

    int16_t x,y;
    uint8_t active;
    int8_t explode;
    struct Bullet *next;

}Bullet;

#define MAX_NUMBER_BULLETS 5


extern Bullet* firstBullet;
extern Bullet* lastBullet;

void SetupBullets();
void RecycleBullet(Bullet* bullet);
void SpawnBullet(int16_t x, int16_t y);
uint8_t UpdateAllBullets(uint8_t startingSprite);

extern Bullet bullets[MAX_NUMBER_BULLETS];
extern int16_t minX,minY,maxX,maxY;

#endif