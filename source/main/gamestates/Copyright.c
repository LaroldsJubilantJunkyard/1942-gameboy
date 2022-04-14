#pragma bank 1

#include "gb/gb.h"
#include "common.h"
#include "graphics/Font.h"


uint8_t Start_CopyrightGameState(){


    move_bkg(0,0);

    
    HIDE_WIN;

    timer=0;


    set_bkg_data(0,Font_TILE_COUNT,Font_tiles);
    set_bkg_palette(0,1,&Font_palettes[12]);
    fill_bkg_rect(0,0,20,18,0);

    
    drawOnBackground=TRUE;DrawText(5,4,"1942 Clone");
    drawOnBackground=TRUE;DrawText(1,5,"Original By Capcom");
    
    drawOnBackground=TRUE;DrawText(2,7,"Free Source Code");
    drawOnBackground=TRUE;DrawText(2,8,"Online on Github");
    
    drawOnBackground=TRUE;DrawText(3,10,"Free Tutorial");
    drawOnBackground=TRUE;DrawText(2,11,"On my Website!");

    drawOnBackground=TRUE;DrawText(6,13,"Larolds");
    drawOnBackground=TRUE;DrawText(1,14,"Jubilant Junkyard");
    return TRUE;
}
uint8_t Update_CopyrightGameState(){


    timer++;
    if(timer>=200)return LAROLDSJUBILANTJUNKYARD_GAMESTATE;

    return COPYRIGHT_GAMESTATE;
}
uint8_t End_CopyrightGameState(){
    return TRUE;
}
