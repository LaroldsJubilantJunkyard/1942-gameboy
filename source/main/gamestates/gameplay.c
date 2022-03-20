#include <gb/gb.h>
#include <gb/metasprites.h>
#include "common.h"
#include "enemies.h"
#include "bullets.h"
#include "paths.h"
#include "formation.h"
#include "graphics/Font.h"
#include "graphics/WaterBackground.h"
#include "graphics/PlayerPlane.h"
#include "graphics/Bullets.h"
#include "graphics/SmallEnemyPlane.h"
#include "graphics/MediumEnemyPlane.h"
#include "graphics/PlayerPlaneMini.h"


uint8_t currentFormationIndex=0;

Formation* (*currentLevel)[];

const Formation* level1[]={
   &TenGrey_TurnTowardsPlayer_Rightwards,
   &TenGrey_TurnTowardsPlayer_Leftwards,
   &TenGrey_TurnTowardsPlayer_Rightwards,
   &TenGrey_TurnTowardsPlayer_Leftwards,   
   &TenGrey_TurnTowardsPlayer_Rightwards,
   0
};


void HandleWindowCutoff(){

    // If the gameboy is drawing line 0 (the top of the screen)
    if(LYC_REG==0){

        // The interrupt should next trigger at line 63
        LYC_REG=8;

        HIDE_SPRITES;
        HIDE_BKG;
        SHOW_WIN;


    // if the gameboy is drawing line 63
    }else if(LYC_REG==8){

        // The interrupt should next trigger at line 0
        LYC_REG=0;

        SHOW_SPRITES;
        SHOW_BKG;
        HIDE_WIN;
    }

}


const palette_color_t AllWhite[4] = {
	RGB8(255,255, 255),RGB8(255,255, 255),RGB8(255,255, 255),RGB8(255,255, 255)
};

uint8_t Start_GameplayGameState(){

    SHOW_WIN;
    SHOW_SPRITES;

    

    // We're gonna use interrupts to achieve parallax scrolling
    // Set the LYC register at 0, where we will start the scrolling logic
    // From there we will move diferent chunks of the background different amounts
    STAT_REG|=0x40; //enable LYC=LY interrupt
    LYC_REG=0;
    disable_interrupts();
    add_LCD(HandleWindowCutoff);
    set_interrupts(LCD_IFLAG|VBL_IFLAG);
    enable_interrupts();

    set_bkg_data(0,Font_TILE_COUNT,Font_tiles);
    set_bkg_data(Font_TILE_COUNT,WaterBackground_TILE_COUNT,WaterBackground_tiles);
    set_bkg_data(Font_TILE_COUNT+WaterBackground_TILE_COUNT,PlayerPlaneMini_TILE_COUNT,PlayerPlaneMini_tiles);

    
    set_bkg_palette(0,7,Font_palettes);
    set_sprite_palette(0,5,PlayerPlane_palettes);
    set_sprite_palette(7,1,AllWhite);
    set_sprite_data(0,PlayerPlane_TILE_COUNT,PlayerPlane_tiles);
    set_sprite_data(PlayerPlane_TILE_COUNT,SmallEnemyPlane_TILE_COUNT,SmallEnemyPlane_tiles);
    set_sprite_data(SmallEnemyPlane_TILE_COUNT+PlayerPlane_TILE_COUNT,MediumEnemyPlane_TILE_COUNT,MediumEnemyPlane_tiles);
    set_sprite_data(SmallEnemyPlane_TILE_COUNT+PlayerPlane_TILE_COUNT+MediumEnemyPlane_TILE_COUNT,Bullets_TILE_COUNT,Bullets_tiles);


    VBK_REG=1;set_bkg_tiles(0,0,32,32,WaterBackground_map_attributes);
    VBK_REG=0;set_bkg_based_tiles(0,0,32,32,WaterBackground_map,Font_TILE_COUNT);



    VBK_REG=1;fill_win_rect(0,0,32,32,0);
    VBK_REG=1;fill_win_rect(0,0,32,32,0);
    drawOnBackground=FALSE;DrawTextWithPalette(1,0,"1P",1);
    drawOnBackground=FALSE;DrawNumber(3,0,123456,7);
    
    drawOnBackground=FALSE;DrawNumber(12,0,88,2);

    // Show the mini player plane on the UI
    VBK_REG=1;set_win_tile_xy(15,0,5);set_win_tile_xy(16,0,5);
    VBK_REG=0;set_win_tile_xy(15,0,Font_TILE_COUNT+WaterBackground_TILE_COUNT);set_win_tile_xy(16,0,Font_TILE_COUNT+WaterBackground_TILE_COUNT+1);

    // Show the retry icon
    VBK_REG=1;set_win_tile_xy(11,0,1);
    VBK_REG=0;set_win_tile_xy(11,0,41);

    drawOnBackground=FALSE;DrawNumber(17,0,1,2);

    playerPlaneX=80<<4;
    playerPlaneY=80<<4;

    SetupEnemies();
    SetupBullets();

    currentFormationIndex=0;
    currentLevel=&level1;


    return TRUE;
}
uint8_t previousMax=0;
uint8_t Update_GameplayGameState(){

    scroll_bkg(0,-1);

    // Horizontal movement
    if(joypadCurrent&J_LEFT)playerPlaneX-=10;
    else if(joypadCurrent&J_RIGHT)playerPlaneX+=10;

    // Vertical movement
    if(joypadCurrent&J_UP)playerPlaneY-=10;
    else if(joypadCurrent&J_DOWN)playerPlaneY+=10;

    // If A was just pressed
    if((joypadCurrent & J_A)&& !(joypadPrevious & J_A)){

        // 12 (half playersprite width) 
        // moving the bullet up one tile
        SpawnBullet(playerPlaneX+(12<<4),playerPlaneY-(8<<4));
    }

    uint8_t maxSprite = move_metasprite(PlayerPlane_metasprites[0],0,0,(playerPlaneX>>4),(playerPlaneY>>4));
    maxSprite=UpdateAllBullets(maxSprite);
    maxSprite =UpdateAllEnemies(maxSprite);

    uint8_t currentMax=maxSprite;

    if(currentMax<previousMax){
        
        
        for(maxSprite;maxSprite<previousMax;maxSprite++){
            move_sprite(maxSprite,0,0);
        }

    }

    previousMax=currentMax;

    // If enemies on screen is zero
    if(enemiesOnScreen==0){

        //Get which formation to spawn enemies for
        Formation* formation = (*currentLevel)[currentFormationIndex];

        // If we are not on the last formation
        if(formation!=0){

            // Spawn an enemy for each path in theformation
            for(uint8_t i=0;i<formation->count;i++){

                uint8_t path = formation->paths[i].path;
                
                // Spawn a new enemy
                SpawnEnemy( formation->type, path, formation->paths[i].position, formation->paths[i].offsetX, formation->paths[i].offsetY, formation->paths[i].delay);
            }

            // Move on to the next formation
            currentFormationIndex++;
            
        }
    }


    return GAMEPLAY_GAMESTATE;
}
uint8_t End_GameplayGameState(){
    disable_interrupts();
    STAT_REG=0;
    return TRUE;
}