#pragma bank 1

#include "gb/gb.h"
#include "common.h"
#include "graphics/Font.h"
#include "graphics/PlaneScreen.h"
#include "graphics/StageText.h"

void SetupStageScreen() NONBANKED{
    

    HIDE_WIN;
    HIDE_SPRITES;
    move_bkg(0,0);
    
    uint8_t _previous_bank = _current_bank;

    SWITCH_ROM_MBC1(1);

    set_bkg_palette(0,7,PlaneScreen_palettes);
    set_bkg_data(0,Font_TILE_COUNT,Font_tiles);
    set_bkg_data(Font_TILE_COUNT,PlaneScreen_TILE_COUNT,PlaneScreen_tiles);
    set_bkg_data(Font_TILE_COUNT+PlaneScreen_TILE_COUNT,StageText_TILE_COUNT,StageText_tiles);

    VBK_REG=1;set_bkg_tiles(0,0,20,18,PlaneScreen_map_attributes);
    VBK_REG=0;set_bkg_based_tiles(0,0,20,18,PlaneScreen_map,Font_TILE_COUNT);


    uint8_t digit1=((currentLevel+1)/10)%10;
    uint8_t digit2=(currentLevel+1)%10;

    uint8_t digit1Tiles[4];
    uint8_t digit1TilesAttributes[4];
    uint8_t digit2Tiles[4];
    uint8_t digit2TilesAttributes[4];

    VBK_REG=1;set_win_tiles(0,0,30,2,StageText_map_attributes);
    VBK_REG=0;set_win_based_tiles(0,0,30,2,StageText_map,Font_TILE_COUNT+PlaneScreen_TILE_COUNT);

    SWITCH_ROM_MBC1(_previous_bank);

    VBK_REG=1;

    get_win_tiles(10+digit2*2,0,2,2,digit2TilesAttributes);
    get_win_tiles(10+digit1*2,0,2,2,digit1TilesAttributes);

    VBK_REG=0;
    get_win_tiles(10+digit1*2,0,2,2,digit1Tiles);
    get_win_tiles(10+digit2*2,0,2,2,digit2Tiles);
    
    uint8_t stageText[20];
    uint8_t stageTextAttributes[20];

    VBK_REG=1;get_win_tiles(0,0,10,2,stageTextAttributes);
    VBK_REG=0;get_win_tiles(0,0,10,2,stageText);

    VBK_REG=1; set_bkg_tiles(1,1,10,2,stageTextAttributes);
    VBK_REG=0; set_bkg_tiles(1,1,10,2,stageText);

    VBK_REG=1; set_bkg_tiles(12,1,2,2,digit1TilesAttributes);
    VBK_REG=0; set_bkg_tiles(12,1,2,2,digit1Tiles);

    VBK_REG=1; set_bkg_tiles(14,1,2,2,digit2TilesAttributes);
    VBK_REG=0; set_bkg_tiles(14,1,2,2,digit2Tiles);
}

uint8_t Start_NextLevelGameState(){

    SetupStageScreen();

    
    drawOnBackground=TRUE;DrawText(5,13,"Player 1:");
    drawOnBackground=TRUE;DrawText(5,15,"Get Ready!");
    return TRUE;
}
uint8_t Update_NextLevelGameState(){
    if((joypadCurrent &J_A)&&!(joypadPrevious&J_A))return GAMEPLAY_GAMESTATE;
    if((joypadCurrent &J_START)&&!(joypadPrevious&J_START))return GAMEPLAY_GAMESTATE;
    return NEXTLEVEL_GAMESTATE;
}
uint8_t End_NextLevelGameState(){
    return TRUE;
}