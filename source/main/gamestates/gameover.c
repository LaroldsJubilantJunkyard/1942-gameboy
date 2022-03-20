#include <gb/gb.h>
#include "common.h"
#include "graphics/Dinosaur.h"
#include "graphics/Buttons.h"

void SetupGameOver(){

    FadeOut(FADE_SPRITES);
    
    // Hide all sprites
    for(uint8_t i=0;i<MAX_HARDWARE_SPRITES;i++){
        move_sprite(i,0,0);
    }

    // Place the buttons in VRAM and on the screen
    set_sprite_data(Dinosaur_TILE_COUNT,Buttons_TILE_COUNT,Buttons_tiles);
    move_metasprite(Buttons_metasprites[1],Dinosaur_TILE_COUNT,startSprite,72,72);

    FadeIn(FADE_SPRITES);

    ClearWindowTopRow();
    DrawTextWithPalette(1,0,"Press A to Continue");
}

void UpdateGameOver(){
    if((joypadCurrent & J_A)&& !(joypadPrevious & J_A)){
        nextState=LEVEL_SELECT;

        FadeOut(FADE_SPRITES|FADE_BACKGROUND);
    }
}
