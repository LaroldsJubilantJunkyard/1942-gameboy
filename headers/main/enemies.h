#ifndef ENEMIES_HEADER
#define ENEMIES_HEADER set

#include <gb/gb.h>

#define ENEMYCOLOR_SMALL_GREY 2
#define ENEMYCOLOR_SMALL_GREEN 4
#define ENEMYCOLOR_SMALL_ORANGE 3

#define ENEMYSTART_BOTTOM_LEFT 0
#define ENEMYSTART_BOTTOM_RIGHT 1

#define ENEMYSTART_LEFT_TOP 2
#define ENEMYSTART_LEFT_BOTTOM 3

#define ENEMYSTART_RIGHT_TOP 4
#define ENEMYSTART_RIGHT_BOTTOM 5

#define ENEMYSTART_TOP_LEFT 6
#define ENEMYSTART_TOP_RIGHT 7

#define FLY_DOWNWARDS_FLIIPTOWARDS_PLAYER 0
#define FLY_UPWARDS_FLIIPTOWARDS_PLAYER 1
#define FLY_RIGHT_TURNPTOWARDS_PLAYER 2
#define FLY_LEFT_TURNPTOWARDS_PLAYER 3
#define FLYDOWNARDS_TOWARDS_PLAYER 4
#define FLYUPWARDS_TOWARDS_PLAYER 5
#define FLYRIGHT_TOWARDS_PLAYER 6
#define FLYLEFT_TOWARDS_PLAYER 7

#define FACING_RIGHT 0
#define FACING_UP 64
#define FACING_LEFT 128
#define FACING_DOWN 192

#define TOP_OR_LEFT 0
#define MIDDLE 1
#define BOTTOM_OR_RIGHT 2

#define FLYSTRAIGHT 0
#define FLYTOWARDS_DIRECTLY 1
#define DELAYED_FLYTOWARDS 2
#define TURNTOWARDS_DIRECTLY 3
#define DELAYED_TURNTOWARDS 4

#define MAX_NUMBER_ENEMIES_ON_SCREEN 10
typedef struct EnemyPlane{
    uint16_t enemyDirection;
    uint16_t delay;
    uint8_t startDirection;
    uint8_t enemyType,active;
    int16_t velocityX,velocityY;
    int16_t x,y;
    int8_t health;
    uint8_t frame;
    uint8_t path;
    uint8_t flash;
    uint8_t collisionBoxWidth, collisionBoxHeight;
    uint8_t collisionBoxX, collisionBoxY;
} EnemyPlane;

extern uint8_t enemiesOnScreen;


extern EnemyPlane enemies[MAX_NUMBER_ENEMIES_ON_SCREEN];


void SetupEnemies();
void SortEnemies();
uint8_t UpdateAllEnemies(uint8_t startingSprite);
void SpawnEnemy(uint8_t enemyType,uint8_t path,uint8_t position,int16_t offsetX, int16_t offsetY,uint16_t delay);

#endif