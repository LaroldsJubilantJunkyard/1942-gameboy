#include "gb/gb.h"
#include "common.h"
#include "graphics/Font.h"
#include "graphics/MenuScreen.h"


uint8_t Start_MenuScreenGameState(){
    HIDE_WIN;
    HIDE_SPRITES;
    move_bkg(0,0);
    set_bkg_data(0,Font_TILE_COUNT,Font_tiles);
    set_bkg_data(Font_TILE_COUNT,MenuScreen_TILE_COUNT,MenuScreen_tiles);
    set_bkg_palette(0,7,MenuScreen_palettes);

    VBK_REG=1;set_bkg_based_tiles(0,0,20,18,MenuScreen_map_attributes,0);
    VBK_REG=0;set_bkg_based_tiles(0,0,20,18,MenuScreen_map,Font_TILE_COUNT);

    DrawTextWithPalette(6,10,"1 Player",2);
    DrawTextWithPalette(6,12,"Options",2);
    DrawTextWithPalette(6,14,"Password",2);

    return TRUE;
}
uint8_t Update_MenuScreenGameState(){
    return MENUSCREEN_GAMESTATE;
}
uint8_t End_MenuScreenGameState(){
    return TRUE;
}