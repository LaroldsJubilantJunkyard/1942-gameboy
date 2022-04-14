#pragma bank 1


#include "gb/gb.h"
#include "common.h"


extern uint16_t bulletsFired;
extern uint16_t bulletsMissed;
extern int16_t rolls;
extern int16_t bonus;
void SetupStageScreen();

uint8_t Start_ResultsGameState(){

    SetupStageScreen();

    uint32_t bulletsHit = bulletsFired-bulletsMissed;

    uint32_t percentage = 100;
    
    // Avoid division by zero
    if(bulletsFired>0)percentage=(100*bulletsHit)/bulletsFired;

    drawOnBackground=TRUE;DrawText(1,12,"Shot Percent:");
    drawOnBackground=TRUE;DrawText(1,14,"Bonus:");
    drawOnBackground=TRUE;DrawText(1,16,"Rolls x1000:");


    uint8_t n =1;
    if(percentage>=10)n=2;
    if(percentage==100)n=3;
    drawOnBackground=TRUE;DrawText(18-n,12,"%");

    drawOnBackground=TRUE;DrawNumber(19-n,12,percentage,n);
    drawOnBackground=TRUE;DrawNumber(15,14,0,4);
    drawOnBackground=TRUE;DrawNumber(15,16,0,4);

    
    return TRUE;
}
uint8_t Update_ResultsGameState(){

    // If a or start are pressed
    // Go to thenext level game state
    if((joypadCurrent &J_A)&&!(joypadPrevious&J_A))return NEXTLEVEL_GAMESTATE;
    if((joypadCurrent &J_START)&&!(joypadPrevious&J_START))return NEXTLEVEL_GAMESTATE;

    // Stay on this screen
    return RESULTS_GAMESTATE;
}
uint8_t End_ResultsGameState(){

    
    currentLevel++;
    return TRUE;
}
