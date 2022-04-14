#pragma bank 1

#include <gb/gb.h>
#include <gb/metasprites.h>
#include "common.h"
#include "graphics/Font.h"
#include "graphics/PlaneScreen.h"
#include "graphics/MenuScreen.h"

extern uint16_t bulletsFired;
extern uint16_t bulletsMissed;
extern uint16_t enemiesShot;
extern int16_t rolls;
extern int16_t bonus;
extern int8_t retries;

uint8_t Start_GameOverGameState(){

    retries--;

    SHOW_BKG;
    HIDE_WIN;
    HIDE_SPRITES;
    move_bkg(0,0);
    

    set_bkg_palette(0,7,MenuScreen_palettes);
    set_bkg_data(0,Font_TILE_COUNT,Font_tiles);

    

    uint32_t bulletsHit = bulletsFired-bulletsMissed;

    uint32_t percentage = 100;
    
    // Avoid division by zero
    if(bulletsFired>0)percentage=(100*bulletsHit)/bulletsFired;

    VBK_REG=1;
    fill_bkg_rect(0,0,20,18,4);
    VBK_REG=0;
    fill_bkg_rect(0,0,20,18,0);

    
    drawOnBackground=TRUE;DrawTextWithPalette(1,5,"Game Over Player 1",4);
    drawOnBackground=TRUE;DrawTextWithPalette(1,9,"Your score",4);
    drawOnBackground=TRUE;DrawTextWithPalette(1,11,"Enemies Shot",4);
    drawOnBackground=TRUE;DrawTextWithPalette(1,13,"Percentage",4);

    uint8_t n =1;
    if(percentage>=10)n=2;
    if(percentage==100)n=3;

    drawOnBackground=TRUE;DrawNumberWithPalette(12,9,score,7,4);
    drawOnBackground=TRUE;DrawNumberWithPalette(15,11,enemiesShot,4,4);
    drawOnBackground=TRUE;DrawNumberWithPalette(19-n,13,percentage,n,4);
    drawOnBackground=TRUE;DrawTextWithPalette(18-n,13,"%",4);
    return TRUE;
}

uint8_t Update_GameOverGameState(){

    // If a or start are pressed
    // Go to thenext level game state
    if((joypadCurrent &J_A)&&!(joypadPrevious&J_A))return retries>=0 ? NEXTLEVEL_GAMESTATE : STARTSCREEN_GAMESTATE;
    if((joypadCurrent &J_START)&&!(joypadPrevious&J_START))return retries>=0 ? NEXTLEVEL_GAMESTATE : STARTSCREEN_GAMESTATE;

    return GAMEOVER_GAMESTATE;
}

uint8_t End_GameOverGameState(){

    return TRUE;
}