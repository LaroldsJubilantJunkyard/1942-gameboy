#include <gb/gb.h>
#include <gb/metasprites.h>
#include "common.h"
#include "enemies.h"
#include "bullets.h"
#include "graphics/Font.h"
#include "graphics/WaterBackground.h"
#include "graphics/PlayerPlane.h"
#include "graphics/Bullets.h"
#include "graphics/SmallEnemyPlane.h"
#include "graphics/PlayerPlaneMini.h"
#include "graphics/SmallExplosion.h"
#include "graphics/MediumExplosion.h"


uint8_t currentPathIndex=0;
uint8_t previousMax=0,enemySpawnDelay=0;
int16_t rolls;
uint32_t score;
uint32_t distanceTravelled;
uint16_t enemiesShot,playerDamageTimer;
int16_t bonus;
int8_t retries=3;
int8_t playerHealth=3;

uint8_t currentLevel=0;

uint8_t UpdatePlayer();

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

// Used for enemies flashing
const palette_color_t AllWhite[4] = { RGB8(255,255, 255),RGB8(255,255, 255),RGB8(255,255, 255),RGB8(255,255, 255) };

void UpdatePlayerHealth(){
    
    // Show the mini player plane on the UI
    VBK_REG=1;set_win_tile_xy(15,0,5);set_win_tile_xy(16,0,5);
    VBK_REG=0;set_win_tile_xy(15,0,Font_TILE_COUNT+WaterBackground_TILE_COUNT);set_win_tile_xy(16,0,Font_TILE_COUNT+WaterBackground_TILE_COUNT+1);
    drawOnBackground=FALSE;DrawNumber(17,0,playerHealth,2);
}

void UpdateScore(){
    
    drawOnBackground=FALSE;DrawTextWithPalette(1,0,"1P",1);
    drawOnBackground=FALSE;DrawNumber(3,0,score,7);
}

uint8_t Start_GameplayGameState(){

    SHOW_WIN;
    SHOW_SPRITES;


    enemiesShot=0;
    distanceTravelled=0;
    enemySpawnDelay=0;
    

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
    set_sprite_palette(0,6,PlayerPlane_palettes);
    set_sprite_palette(7,1,AllWhite);
    set_sprite_data(0,PlayerPlane_TILE_COUNT,PlayerPlane_tiles);
    set_sprite_data(PlayerPlane_TILE_COUNT,SmallEnemyPlane_TILE_COUNT,SmallEnemyPlane_tiles);
    set_sprite_data(BULLETS_START,Bullets_TILE_COUNT,Bullets_tiles);
    set_sprite_data(SMALL_EXPLOSION_TILES_START,SmallExplosion_TILE_COUNT,SmallExplosion_tiles);
    set_sprite_data(MEDIUM_EXPLOSION_TILES_START,MediumExplosion_TILE_COUNT,MediumExplosion_tiles);


    VBK_REG=1;set_bkg_tiles(0,0,32,32,WaterBackground_map_attributes);
    VBK_REG=0;set_bkg_based_tiles(0,0,32,32,WaterBackground_map,Font_TILE_COUNT);



    VBK_REG=1;fill_win_rect(0,0,32,32,0);
    VBK_REG=0;fill_win_rect(0,0,32,32,0);
    drawOnBackground=FALSE;DrawNumber(12,0,retries,2);

    UpdatePlayerHealth();
    UpdateScore();

    // Show the retry icon
    VBK_REG=1;set_win_tile_xy(11,0,1);
    VBK_REG=0;set_win_tile_xy(11,0,41);

    SetupPlayer();
    SetupEnemies();
    SetupBullets();

    currentPathIndex=0;


    return TRUE;
}
uint8_t Update_GameplayGameState(){

    distanceTravelled++;
    uint8_t completed=distanceTravelled>=(1+currentLevel/5)*3600;

    scroll_bkg(0,-1);

     uint8_t maxSprite = UpdatePlayer();

    maxSprite=UpdateAllBullets(maxSprite);
    maxSprite =UpdateAllEnemies(maxSprite,completed);

    // Save how many sprites we used
    uint8_t currentMax=maxSprite;

    // If used less sprites than the previous time
    if(currentMax<previousMax){
        
        // Move the remainder offscreen
        for(maxSprite;maxSprite<previousMax;maxSprite++){
            move_sprite(maxSprite,0,0);
        }

    }

    previousMax=currentMax;

    // If the player is dead
    // Go to the game over screen
    if(playerHealth<0){
        return GAMEOVER_GAMESTATE;
    }

    // If we are completed, and no enemies remain
    // Go to the results screen
    if(completed&&enemiesOnScreen==0){
        return RESULTS_GAMESTATE;
    }


    return GAMEPLAY_GAMESTATE;
}
uint8_t End_GameplayGameState(){
    disable_interrupts();
    remove_LCD(HandleWindowCutoff);
    STAT_REG=0;

    // Important: re-enable or wait_vbl_done will forever halt
    enable_interrupts();
    return TRUE;
}