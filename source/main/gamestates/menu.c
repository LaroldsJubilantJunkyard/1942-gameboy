#include <gb/gb.h>
#include "common.h"
#include "graphics/Dinosaur.h"
#include "graphics/Buttons.h"
#include "graphics/Font.h"
#include "graphics/TitleScreen.h"

void SetupMenu(){

    move_bkg(0,0);

    set_bkg_data(0,Font_TILE_COUNT,Font_tiles);
    set_bkg_data(Font_TILE_COUNT,TitleScreen_TILE_COUNT,TitleScreen_tiles);
    VBK_REG=1;set_bkg_tiles(0,0,20,18,TitleScreen_map_attributes);
    VBK_REG=0;set_bkg_based_tiles(0,0,20,18,TitleScreen_map,Font_TILE_COUNT);

    // Hide all sprites
    for(uint8_t i=0;i<MAX_HARDWARE_SPRITES;i++){
        move_sprite(i,0,0);
    }

    // Clear the windows top row
    ClearWindowTopRow();

    // Place the buttons in VRAM and on the screen
    set_sprite_data(Dinosaur_TILE_COUNT,Buttons_TILE_COUNT,Buttons_tiles);
    move_metasprite(Buttons_metasprites[0],Dinosaur_TILE_COUNT,startSprite,120,72);

    FadeIn(FADE_BACKGROUND|FADE_SPRITES);
}


void UpdateMenu(){

    if((joypadCurrent & J_A)&& !(joypadPrevious & J_A)){

        nextState=LEVEL_SELECT;

        
    FadeOut(FADE_SPRITES|FADE_BACKGROUND);

    }else if(counter>20){
        if(get_win_tile_xy(3,0)==0){

            DrawTextWithPalette(2,0,"Press A to Start");
        }else{
            ClearWindowTopRow();
        }
        counter=0;
    }
}