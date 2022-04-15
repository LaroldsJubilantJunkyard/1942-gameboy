#include "gb/gb.h"
#include "common.h"




uint8_t Start_CopyrightGameState();uint8_t Update_CopyrightGameState();uint8_t End_CopyrightGameState();
uint8_t Start_LaroldsJubilantJunkyardGameState();uint8_t Update_LaroldsJubilantJunkyardGameState();uint8_t End_LaroldsJubilantJunkyardGameState();
uint8_t Start_StartScreenGameState();uint8_t Update_StartScreenGameState();uint8_t End_StartScreenGameState();
uint8_t Start_MenuScreenGameState();uint8_t Update_MenuScreenGameState();uint8_t End_MenuScreenGameState();
uint8_t Start_NextLevelGameState();uint8_t Update_NextLevelGameState();uint8_t End_NextLevelGameState();
uint8_t Start_GameplayGameState();uint8_t Update_GameplayGameState();uint8_t End_GameplayGameState();
uint8_t Start_ResultsGameState();uint8_t Update_ResultsGameState();uint8_t End_ResultsGameState();
uint8_t Start_GameOverGameState();uint8_t Update_GameOverGameState();uint8_t End_GameOverGameState();


const uint8_t (*AllGameStates[][3])(void)={
    {0,0,0},
    {&Start_CopyrightGameState,&Update_CopyrightGameState,&End_CopyrightGameState},
    {&Start_LaroldsJubilantJunkyardGameState,&Update_LaroldsJubilantJunkyardGameState,&End_LaroldsJubilantJunkyardGameState},
    {&Start_StartScreenGameState,&Update_StartScreenGameState,&End_StartScreenGameState},
    {&Start_MenuScreenGameState,&Update_MenuScreenGameState,&End_MenuScreenGameState},
    {&Start_NextLevelGameState,&Update_NextLevelGameState,&End_NextLevelGameState},
    {&Start_GameplayGameState,&Update_GameplayGameState,&End_GameplayGameState},
    {&Start_ResultsGameState,&Update_ResultsGameState,&End_ResultsGameState},
    {&Start_GameOverGameState,&Update_GameOverGameState,&End_GameOverGameState},
};

void main(void){


    // This enables Sound
    // these registers must be in this specific order!
    NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
    NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
    NR51_REG = 0xFF; // is 1111 1111 in binary, select which chanels we want to use in this case all of them. One bit for the L one bit for the R of all four channels

    DISPLAY_ON;
    SHOW_BKG;
    SHOW_SPRITES;
    SPRITES_8x16;
    SHOW_WIN;


    uint8_t currenGameState=GAMEFIRSTLOAD;
    uint8_t nextGameState=COPYRIGHT_GAMESTATE;

    while(TRUE){

        joypadPrevious=joypadCurrent;
        joypadCurrent=joypad();

        // If we should change gamestate
        if(currenGameState!=nextGameState){
            
            // Call our game state's end function
            if(currenGameState!=GAMEFIRSTLOAD)AllGameStates[currenGameState][2]();

            currenGameState=nextGameState;
            
            // Call our new game states start function
            AllGameStates[currenGameState][0]();
        }

        // Update our gamestate
        nextGameState = AllGameStates[currenGameState][1]();

        wait_vbl_done();
    }
}