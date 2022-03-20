#include "gb/gb.h"
#include "common.h"


uint8_t Start_OptionsGameState(){
    return TRUE;
}
uint8_t Update_OptionsGameState(){
    return OPTIONS_GAMESTATE;
}
uint8_t End_OptionsGameState(){
    return TRUE;
}
