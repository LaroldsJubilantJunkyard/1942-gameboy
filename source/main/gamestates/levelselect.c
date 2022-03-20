#include <gb/gb.h>
#include "common.h"
#include "graphics/Font.h"
#include "graphics/Dinosaur.h"

void RedrawLevelSelect(){

        
    set_bkg_data(0,Font_TILE_COUNT,Font_tiles);
    set_bkg_data(Font_TILE_COUNT,levels[level].tileCount,levels[level].tiles);

    ClearWindowTopRow();

    DrawTextWithPalette(7,0,levels[level].name);

    // Draw the arrows
    set_win_tile_xy(0,0,Font_TILE_COUNT-2);
    set_win_tile_xy(19,0,Font_TILE_COUNT-1);

    VBK_REG=1;set_bkg_tiles(0,0,32,18,levels[level].map_attributes);
    VBK_REG=0;set_bkg_based_tiles(0,0,32,18,levels[level].map,Font_TILE_COUNT);
}

void SetupLevelSelect(){

    // Populate vram with dinosaur and obstacles
    set_sprite_data(0,Dinosaur_TILE_COUNT,Dinosaur_tiles);

    
    dinoX=-32<<4;
    
    // Hide all sprites
    for(uint8_t i=0;i<MAX_HARDWARE_SPRITES;i++){
        move_sprite(i,0,0);
    }

    ClearWindowTopRow();
    move_metasprite(Dinosaur_metasprites[0],0,0,192,108);

    RedrawLevelSelect();

    FadeIn(FADE_SPRITES|FADE_BACKGROUND);
}


void DinoRunIn(){
    
    if(dinoX>80<<4){

        while(dinoX>>4>DINOSAUR_LEFT){
            dinoX-=200;
            move_metasprite_vflip(Dinosaur_metasprites[0],0,0,MAX(dinoX>>4,DINOSAUR_LEFT)+32,108);
            wait_vbl_done();
        }
    }else{

        while(dinoX>>4<DINOSAUR_LEFT){
            dinoX+=100;
            move_metasprite(Dinosaur_metasprites[0],0,0,MIN(dinoX>>4,DINOSAUR_LEFT),108);
            wait_vbl_done();
        }
    }
}

void DinoRunOutLeft(){
    

    while(dinoX>>4>-32){
        dinoX-=100;
        move_metasprite_vflip(Dinosaur_metasprites[0],0,0,MAX(dinoX>>4,-32)+32,108);
        wait_vbl_done();
    }
}

void DinoRunOut(){
    

    while(dinoX>>4<192){
        dinoX+=200;
        move_metasprite(Dinosaur_metasprites[0],0,0,MIN(dinoX>>4,192),108);
        wait_vbl_done();
    }
}

void UpdateLevelSelect(){

    DinoRunIn();
    
    if((joypadCurrent & J_LEFT)&& !(joypadPrevious & J_LEFT)){

        DinoRunOutLeft();

        FadeOut(FADE_BACKGROUND);

        if(level==0)level=3;
        else level--;
        
        
        RedrawLevelSelect();

        FadeIn(FADE_BACKGROUND);

        dinoX=192<<4;

    }else if((joypadCurrent & J_RIGHT)&& !(joypadPrevious & J_RIGHT)){

        DinoRunOut();

        FadeOut(FADE_BACKGROUND);

        if(level==3)level=0;
        else level++;
        
        RedrawLevelSelect();

        FadeIn(FADE_BACKGROUND);

        dinoX=-32<<4;


    }else if((joypadCurrent & J_A)&& !(joypadPrevious & J_A)){

        nextState=GAMEPLAY;
        ClearWindowTopRow();
    }
}