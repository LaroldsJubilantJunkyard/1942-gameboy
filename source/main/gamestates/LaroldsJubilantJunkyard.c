#include "gb/gb.h"
#include "gb/metasprites.h"
#include "common.h"
#include "graphics/Font.h"
#include "graphics/Year.h"
#include "graphics/LaroldsJubilantJunkyard.h"


uint8_t Start_LaroldsJubilantJunkyardGameState(){

    move_bkg(0,4);

    
    HIDE_WIN;
    SHOW_BKG;

    timer=0;



    set_bkg_data(0,LaroldsJubilantJunkyard_TILE_COUNT,LaroldsJubilantJunkyard_tiles);
    set_bkg_palette(0,1,LaroldsJubilantJunkyard_palettes);
    fill_bkg_rect(0,0,20,18,0);
    VBK_REG=1;set_bkg_tiles(0,9,20,2,LaroldsJubilantJunkyard_map_attributes);
    VBK_REG=0;set_bkg_tiles(0,9,20,2,LaroldsJubilantJunkyard_map);


    return TRUE;
}
uint8_t Update_LaroldsJubilantJunkyardGameState(){

    timer++;
    if(timer>=200)return STARTSCREEN_GAMESTATE;

    return LAROLDSJUBILANTJUNKYARD_GAMESTATE;
}
uint8_t End_LaroldsJubilantJunkyardGameState(){
    return TRUE;
}
