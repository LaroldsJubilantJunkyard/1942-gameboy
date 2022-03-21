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

    drawOnBackground=TRUE;DrawText(1,12,"Shot Percentage:");
    drawOnBackground=TRUE;DrawText(18,12,"%");
    drawOnBackground=TRUE;DrawText(1,14,"Bonus:");
    drawOnBackground=TRUE;DrawText(1,16,"Rolls x1000:");

    drawOnBackground=TRUE;DrawNumber(16,12,percentage,2);
    drawOnBackground=TRUE;DrawNumber(14,12,0,4);
    drawOnBackground=TRUE;DrawNumber(15,12,0,4);

    
    return TRUE;
}
uint8_t Update_ResultsGameState(){
    if((joypadCurrent &J_A)||(joypadCurrent&J_START))return NEXTLEVEL_GAMESTATE;
    return RESULTS_GAMESTATE;
}
uint8_t End_ResultsGameState(){
    return TRUE;
}
