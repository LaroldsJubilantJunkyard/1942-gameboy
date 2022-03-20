#include "gb/gb.h"
#include "common.h"



uint8_t Start_PasswordGameState(){
    return TRUE;
}
uint8_t Update_PasswordGameState(){
    return PASSWORD_GAMESTATE;
}
uint8_t End_PasswordGameState(){
    return TRUE;
}
