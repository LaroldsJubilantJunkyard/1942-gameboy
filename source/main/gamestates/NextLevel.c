#include "gb/gb.h"
#include "common.h"



uint8_t Start_NextLevelGameState(){
    return TRUE;
}
uint8_t Update_NextLevelGameState(){
    return NEXTLEVEL_GAMESTATE;
}
uint8_t End_NextLevelGameState(){
    return TRUE;
}