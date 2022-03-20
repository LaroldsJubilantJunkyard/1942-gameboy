#include "gb/gb.h"
#include "gb/metasprites.h"
#include "common.h"
#include "graphics/StartScreen.h"
#include "graphics/Year.h"
#include "graphics/LaroldsJubilantJunkyard.h"


uint16_t scrollValue=0;

void HandleBackgroundScrolling(){

    // If the gameboy is drawing line 0 (the top of the screen)
    if(LYC_REG==0){

        // The interrupt should next trigger at line 63
        LYC_REG=70;

        // Move everything below on the background (until our next interrupt at 63) back to the starting position
        move_bkg(0,0);


    // if the gameboy is drawing line 63
    }else  if(LYC_REG==70){

        // The interrupt should next trigger at line 63
        LYC_REG=95;

        // Move everything below on the background (until our next interrupt at 63) back to the starting position
        move_bkg(scrollValue>>4,0);

    // if the gameboy is drawing line 63
    }else if(LYC_REG==95){

        // The interrupt should next trigger at line 79
        LYC_REG=104;

        // Move everything below on the background (until our next interrupt at 79) according to this variable
        move_bkg(scrollValue>>3,0);

     // if the gameboy is drawing line 79
    }else if(LYC_REG==104){

        // The interrupt should next trigger at line 95
        LYC_REG=114;

        // Move everything below on the background (until our next interrupt at 95) according to this variable
        move_bkg(scrollValue>>2,0);

    // if the gameboy is drawing line 95
    }else if(LYC_REG==114){

        // The interrupt should next trigger at line 95
        LYC_REG=120;

        // Move everything below on the background (until our next interrupt at 95) according to this variable
        move_bkg(scrollValue>>1,0);

    // if the gameboy is drawing line 95
    }else if(LYC_REG==120){

        // The interrupt should next trigger at line 119
        LYC_REG=134;

        // Move everything below on the background (until our next interrupt at 119) according to this variable
        move_bkg(0,0);

    // if the gameboy is drawing line 125
    }else{

        // The interrupt should next trigger at line 0
        LYC_REG=0;

        // Move everything below on the background (until our next interrupt at 0) back to the starting position
        move_bkg(scrollValue,0);
    }

}


uint8_t Start_StartScreenGameState(){

    // We're gonna use interrupts to achieve parallax scrolling
    // Set the LYC register at 0, where we will start the scrolling logic
    // From there we will move diferent chunks of the background different amounts
    STAT_REG|=0x40; //enable LYC=LY interrupt
    LYC_REG=0;
    disable_interrupts();
    add_LCD(HandleBackgroundScrolling);
    set_interrupts(LCD_IFLAG|VBL_IFLAG);
    enable_interrupts();

    HIDE_WIN;
    move_bkg(0,0);
    set_bkg_data(0,StartScreen_TILE_COUNT,StartScreen_tiles);
    set_bkg_palette(0,5,StartScreen_palettes);


    VBK_REG=1;set_bkg_tiles(0,0,32,18,StartScreen_map_attributes);
    VBK_REG=0;set_bkg_tiles(0,0,32,18,StartScreen_map);

    set_sprite_data(0,Year_TILE_COUNT,Year_tiles);
    set_sprite_palette(0,1,Year_palettes);
    
    

    uint8_t n = move_metasprite(Year_metasprites[0],0,0,64,120);

    return TRUE;
}
uint8_t Update_StartScreenGameState(){
    
    scrollValue+=10;
    if((joypadCurrent & J_A) ||(joypadCurrent& J_START))return MENUSCREEN_GAMESTATE;
    return STARTSCREEN_GAMESTATE;
}
uint8_t End_StartScreenGameState(){
    disable_interrupts();
    STAT_REG=0;
    return TRUE;
}
