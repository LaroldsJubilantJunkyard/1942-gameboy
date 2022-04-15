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

extern uint16_t playerDamageTimer;
extern int16_t rolls;
extern int16_t bonus;
extern int8_t playerHealth;
extern int16_t playerPlaneX,playerPlaneY;

void SetupPlayer(){
    

    rolls=0;
    bonus=0;
    playerHealth=3;
    playerPlaneX=80<<4;
    playerPlaneY=80<<4;
    playerDamageTimer=0;
}

uint8_t UpdatePlayer(){
     // Horizontal movement
    if(joypadCurrent&J_LEFT)playerPlaneX-=10;
    else if(joypadCurrent&J_RIGHT)playerPlaneX+=10;

    // Vertical movement
    if(joypadCurrent&J_UP)playerPlaneY-=10;
    else if(joypadCurrent&J_DOWN)playerPlaneY+=10;

    // If A was just pressed
    if((joypadCurrent & J_A)&& !(joypadPrevious & J_A)){

        NR10_REG=0x2A;
        NR11_REG=0x42;
        NR12_REG=0x42;
        NR13_REG=0x73;
        NR14_REG=0x86;

        // 12 (half playersprite width) 
        // moving the bullet up one tile
        SpawnBullet(playerPlaneX,playerPlaneY-(7<<4));
    }

     uint8_t maxSprite = 0;

    if(playerDamageTimer==0){

        maxSprite = move_metasprite(PlayerPlane_metasprites[0],0,0,(playerPlaneX>>4)-4,(playerPlaneY>>4)+8);
    }else if(playerDamageTimer>0){
        if((playerDamageTimer/10)%2!=0){
            maxSprite = move_metasprite(PlayerPlane_metasprites[0],0,0,(playerPlaneX>>4)-4,(playerPlaneY>>4)+8);

        }
        playerDamageTimer--;
    }

    return maxSprite;
}