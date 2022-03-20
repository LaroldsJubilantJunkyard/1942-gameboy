#ifndef PATHS_HEADER
#define PATHS_HEADER set
#include <gb/gb.h>
#include "enemies.h"

typedef struct EnemyPath{

    void (*Setup)(EnemyPlane *enemy,uint8_t position,int16_t offsetX, int16_t offsetY);
    uint8_t (*Update)(EnemyPlane* enemy);
}EnemyPath;


extern const EnemyPath AllPaths[];


#define PATH_Setup_Left_FlyStraight 0
#define PATH_Setup_Bottom_FlyStraight 1
#define PATH_Setup_Right_FlyStraight 2
#define PATH_Setup_Top_FlyStraight 3
#define PATH_Setup_Left_FlyTowardsPlayer_Rightwards 4
#define PATH_Setup_Bottom_FlyTowardsPlayer_Upwards 5
#define PATH_Setup_Right_FlyTowardsPlayer_Leftwards 6
#define PATH_Setup_Top_FlyTowardsPlayer_Downwards 7
#define PATH_Setup_Left_Delayed_FlyTowardsPlayer_Rightwards 8
#define PATH_Setup_Bottom_Delayed_FlyTowardsPlayer_Upwards 9
#define PATH_Setup_Right_Delayed_FlyTowardsPlayer_Leftwards 10
#define PATH_Setup_Top_Delayed_FlyTowardsPlayer_Downwards 11
#define PATH_Setup_Left_TurnTowardsPlayer_Rightwards 12
#define PATH_Setup_Bottom_TurnTowardsPlayer_Upwards 13
#define PATH_Setup_Right_TurnTowardsPlayer_Leftwards 14
#define PATH_Setup_Top_TurnTowardsPlayer_Downwards 15

#endif