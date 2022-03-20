#include <gb/gb.h>
#include "common.h"
#include "graphics/Dinosaur.h"
#include "graphics/Cactus.h"


void TrySpawnNewCactus(){
     if(activeCatii<2 && DIV_REG>5){

        // Spawn at the right side of the screen
        spawnX=160<<4;

        for(uint8_t i=0;i<MAX_NUMBER_CACTUS;i++){

            if(cactii[i].active){

                // Get the maximum x of the active cactii
                if(cactii[i].x>spawnX)spawnX=cactii[i].x;
            }
        }

        // Move back 64 pixels plus a random amount (max 128)
        spawnX+=(64+(DIV_REG %(128)))<<4;

        for(uint8_t i=0;i<MAX_NUMBER_CACTUS;i++){

            if(!cactii[i].active){

                cactii[i].active=TRUE;
                cactii[i].x=spawnX;
                cactii[i].type=DIV_REG>128?0:1;
                cactii[i].done=FALSE;
                activeCatii++;
            }
        }
    }
}

void ResetGame(){
    frame=0;
    health=3;
    started=FALSE;
    jumpVelocity=0;
    aboveGround=0;
    moveSpeed=0;
    damageBlinker=0;
    activeCatii=0;
    score=0;

    // Hide all other sprites
    for(uint8_t i=DINOSAUR_MAX_NUMBER_OF_SPRITES;i<MAX_HARDWARE_SPRITES;i++){
        move_sprite(i,0,0);
    }
    
    // Set all as inactive
    for(uint8_t j=0;j<MAX_NUMBER_CACTUS;j++){
        cactii[j].active=FALSE;
    }   

}

void DrawScore(){

    DrawNumber(0,0,score>>4,6);
}
void DrawLives(){

    DrawTextWithPalette(11,0,"Lives:");
    DrawNumber(18,0,health,2);
}


uint8_t CactusTryCollision(uint8_t i){

    // If we are horizontally aligned
     if(cactii[i].x>=(DINOSAUR_LEFT-16)<<4&&cactii[i].x<(DINOSAUR_LEFT+32)<<4){

        // How high does the dinosaur need to jump (but negative)
        int16_t clearHeight = cactii[i].type==0?-29 :-19;

        // If the dinosaur isn't high enough
        if((aboveGround>>4)>clearHeight){
            
            cactii[i].done=TRUE;

            // A collision happened
            return TRUE;

        }
    }
    return FALSE;
}

uint8_t UpdateAllCactus(uint8_t startSprite){

    uint8_t notHitPlayer=TRUE;
    

    // For each cactii object
    for(uint8_t i=0;i<MAX_NUMBER_CACTUS;i++){

        // If this cactii is active
        if(cactii[i].active){


            // Move left based on the player's move speed
            cactii[i].x-=moveSpeed+(2<<4);


            if(cactii[i].x<(DINOSAUR_LEFT-16)<<4&&!cactii[i].done){
                score+=60;
                DrawScore();
                cactii[i].done=TRUE;
            }

            // If the cactus is off the right side of the screen
            // Hide it's metasprite
            if(cactii[i].x<=160<<4){

                // Show at the proper position
                startSprite+=move_metasprite(Cactus_metasprites[cactii[i].type+levels[level].obstacleOffset],Dinosaur_TILE_COUNT,startSprite,(cactii[i].x>>4)+8,108);

            }


            if(cactii[i].x<-16<<4){
                cactii[i].active=FALSE;
                
                activeCatii--;
            }else{
               
               if(CactusTryCollision(i)){
                   notHitPlayer= FALSE;
               }
            }
        }
    }

    for(uint8_t j=startSprite;j<40;j++){
        move_sprite(j,0,0);
    }
    return notHitPlayer;
}

uint8_t UpdateDinosaur(){
    uint8_t animateSpeed=5;

    if(aboveGround>=0){
        aboveGround=0;
        jumpVelocity=0;

        // Check the a button and the d-ad
        uint8_t aButtonOrDPadUp = ((joypadCurrent & J_A)&& !(joypadPrevious & J_A)) || ((joypadCurrent & J_UP)&& !(joypadPrevious & J_UP));
        uint8_t bButtonOrDPadDown = (joypadCurrent & J_B)||(joypadCurrent & J_DOWN);

        uint8_t baseFrame=0;
    
        if(aButtonOrDPadUp){
            jumpVelocity=-(45<<4);
            
            aboveGround+=jumpVelocity>>4;
        }else if(bButtonOrDPadDown){
            baseFrame=10;
        }
        
        if(joypadCurrent & J_RIGHT){
            if(moveSpeed<32)moveSpeed+=2;
            animateSpeed=10;
        }else if(moveSpeed>0){
            moveSpeed--;
        }

        frameCounter+=animateSpeed;
        if(frameCounter>>4>=8)frameCounter=0;
        frame=(frameCounter>>4)+baseFrame;
    }else{

        // Frame 9 is for faling
        // Frame 8 is for rising
        if(jumpVelocity>0)frame=9;
        else frame=8;

        // If we are holding A and rising
        if(((joypadCurrent & J_A)||(joypadCurrent & J_UP))&&jumpVelocity<0){

            // Apply a reduced gravity
            jumpVelocity+=22;
        }else{
            
            // Apply a normal gravity
            jumpVelocity+=40;
        }

        // Apply velocity
        aboveGround+=jumpVelocity>>4;
    }

    if(damageBlinker>0)damageBlinker--;

    if(damageBlinker>0&&(damageBlinker/5)%2==0){


        move_metasprite(Dinosaur_metasprites[frame],0,0,180,180);

        return 0;
    }else{
        
        return move_metasprite(Dinosaur_metasprites[frame],0,0,DINOSAUR_LEFT,108+(aboveGround>>4));
    }
}


void UpdateGameplay(){
    startSprite = UpdateDinosaur();
    TrySpawnNewCactus();

    score++;
    DrawScore();

    if(!UpdateAllCactus(startSprite)){

        if(damageBlinker==0){
            damageBlinker=100;
            
            if(health>0){
                health--;
                DrawLives();
            }
            else {
                nextState=GAME_OVER;
            }
        }
    }

    // If the start button was just pressed
    if((joypadCurrent & J_START)&& !(joypadPrevious & J_START)){

        // Clear the windows top row
        ClearWindowTopRow();
        DrawTextWithPalette(5,0,"Game Paused");

        joypadPrevious=J_START;

        while(TRUE){

            // If Select is pressed
            if((joypadCurrent & J_SELECT)&& !(joypadPrevious & J_SELECT)){

                // Were going back to the menu
                nextState=MENU;

                // Fade our the background sprites
                FadeOut(FADE_BACKGROUND|FADE_SPRITES);

                return;
            }

            // Wait until start is pressed again
            if((joypadCurrent & J_START)&& !(joypadPrevious & J_START)){
                break;
            }

            wait_vbl_done();

            joypadPrevious=joypadCurrent;
            joypadCurrent=joypad();
        }

        // Clear the windows top row
        ClearWindowTopRow();

        // Redraw the score
        DrawLives();
        DrawScore();

    }

    scroll_bkg((moveSpeed>>4)+2,0);
}



void SetupGameplay(){

    // Populate vram with dinosaur and obstacles
    set_sprite_data(0,Dinosaur_TILE_COUNT,Dinosaur_tiles);
    set_sprite_data(Dinosaur_TILE_COUNT,Cactus_TILE_COUNT,Cactus_tiles);

    // Reset our game stats
    ResetGame();

    // Draw our lives and score
    DrawLives();
    DrawScore();
}

