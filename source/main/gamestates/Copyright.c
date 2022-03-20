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

    DrawText(5,4,"1942 Clone");
    DrawText(1,5,"Original By Capcom");
    
    DrawText(2,7,"Free Source Code");
    DrawText(2,8,"Online on Github");

    
    DrawText(3,10,"Free Tutorial");
    DrawText(2,11,"On my Website!");

    DrawText(6,13,"Larolds");
    DrawText(1,14,"Jubilant Junkyard");
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
