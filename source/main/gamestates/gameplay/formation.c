#include <gb/gb.h>
#include "common.h"
#include "paths.h"
#include "enemies.h"
#include "formation.h"

const Formation TenGrey_TurnTowardsPlayer_Rightwards={
    // Path 1
    .type=ENEMYCOLOR_SMALL_GREY,
    .count=10,
    .paths={
        {.path=PATH_Setup_Left_TurnTowardsPlayer_Rightwards,.delay=30,.position=TOP_OR_LEFT,.offsetX=0,.offsetY=0},
        {.path=PATH_Setup_Left_TurnTowardsPlayer_Rightwards,.delay=60,.position=TOP_OR_LEFT,.offsetX=0,.offsetY=0},
        {.path=PATH_Setup_Left_TurnTowardsPlayer_Rightwards,.delay=90,.position=TOP_OR_LEFT,.offsetX=0,.offsetY=0},
        {.path=PATH_Setup_Left_TurnTowardsPlayer_Rightwards,.delay=120,.position=TOP_OR_LEFT,.offsetX=0,.offsetY=0},
        {.path=PATH_Setup_Left_TurnTowardsPlayer_Rightwards,.delay=150,.position=TOP_OR_LEFT,.offsetX=0,.offsetY=0},
        {.path=PATH_Setup_Left_TurnTowardsPlayer_Rightwards,.delay=180,.position=TOP_OR_LEFT,.offsetX=0,.offsetY=0},
        {.path=PATH_Setup_Left_TurnTowardsPlayer_Rightwards,.delay=210,.position=TOP_OR_LEFT,.offsetX=0,.offsetY=0},
        {.path=PATH_Setup_Left_TurnTowardsPlayer_Rightwards,.delay=240,.position=TOP_OR_LEFT,.offsetX=0,.offsetY=0},
        {.path=PATH_Setup_Left_TurnTowardsPlayer_Rightwards,.delay=270,.position=TOP_OR_LEFT,.offsetX=0,.offsetY=0},
        {.path=PATH_Setup_Left_TurnTowardsPlayer_Rightwards,.delay=300,.position=TOP_OR_LEFT,.offsetX=0,.offsetY=0}
    }
};
    
const Formation TenGrey_TurnTowardsPlayer_Leftwards={
    .type=ENEMYCOLOR_SMALL_GREY,
    .count=10,
    .paths={
        {.path=PATH_Setup_Right_TurnTowardsPlayer_Leftwards,.delay=30,.position=TOP_OR_LEFT,.offsetX=0,.offsetY=0},
        {.path=PATH_Setup_Right_TurnTowardsPlayer_Leftwards,.delay=60,.position=TOP_OR_LEFT,.offsetX=0,.offsetY=0},
        {.path=PATH_Setup_Right_TurnTowardsPlayer_Leftwards,.delay=90,.position=TOP_OR_LEFT,.offsetX=0,.offsetY=0},
        {.path=PATH_Setup_Right_TurnTowardsPlayer_Leftwards,.delay=120,.position=TOP_OR_LEFT,.offsetX=0,.offsetY=0},
        {.path=PATH_Setup_Right_TurnTowardsPlayer_Leftwards,.delay=150,.position=TOP_OR_LEFT,.offsetX=0,.offsetY=0},
        {.path=PATH_Setup_Right_TurnTowardsPlayer_Leftwards,.delay=180,.position=TOP_OR_LEFT,.offsetX=0,.offsetY=0},
        {.path=PATH_Setup_Right_TurnTowardsPlayer_Leftwards,.delay=210,.position=TOP_OR_LEFT,.offsetX=0,.offsetY=0},
        {.path=PATH_Setup_Right_TurnTowardsPlayer_Leftwards,.delay=240,.position=TOP_OR_LEFT,.offsetX=0,.offsetY=0},
        {.path=PATH_Setup_Right_TurnTowardsPlayer_Leftwards,.delay=270,.position=TOP_OR_LEFT,.offsetX=0,.offsetY=0},
        {.path=PATH_Setup_Right_TurnTowardsPlayer_Leftwards,.delay=300,.position=TOP_OR_LEFT,.offsetX=0,.offsetY=0}
    }
};