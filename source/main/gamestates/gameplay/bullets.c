#include <gb/gb.h>
#include <gb/metasprites.h>
#include "graphics/Bullets.h"
#include "graphics/PlayerPlane.h"
#include "graphics/Bullets.h"
#include "graphics/SmallEnemyPlane.h"
#include "graphics/SmallExplosion.h"
#include "graphics/MediumExplosion.h"
#include "graphics/PlayerPlaneMini.h"
#include "bullets.h"
#include "common.h"
#include "enemies.h"

Bullet bullets[MAX_NUMBER_BULLETS];

int16_t minX,minY,maxX,maxY;

uint16_t bulletsFired;
uint16_t bulletsMissed;

void ReSortBullets(){
    
    Bullet bulletsTemp[MAX_NUMBER_BULLETS];

    uint8_t i=0,activeCount=0;

    for(i=0;i<MAX_NUMBER_BULLETS;i++)bulletsTemp[i].active=FALSE;


    for(i=0;i<MAX_NUMBER_BULLETS;i++){
        if(bullets[i].active){
            bulletsTemp[activeCount++]=bullets[i];
        }
    }

    for(i=0;i<MAX_NUMBER_BULLETS;i++){
        bullets[i]=bulletsTemp[i];
    }

}
void SpawnBullet(int16_t x, int16_t y){

    for(uint8_t i=0;i<MAX_NUMBER_BULLETS;i++){
        if(!bullets[i].active){
            bullets[i].x=x;
            bullets[i].y=y;
            bullets[i].explode=-1;
            bullets[i].active=TRUE;
            bulletsFired++;
            break;
        }
    }
}


void SetupBullets(){

    bulletsFired=0;
    bulletsMissed=0;

    for(uint8_t i=0;i<MAX_NUMBER_BULLETS;i++)bullets[i].active=FALSE;
}

uint8_t UpdateBullet(Bullet* bullet, uint8_t startingSprite){
    if(bullet->explode==-1){
            
        bullet->y-=100;
        if(bullet->y<-128){
            bulletsMissed++;
            bullet->active=FALSE;
            return 0;
        }
    
        return move_metasprite(Bullets_metasprites[0],BULLETS_TILES_START,startingSprite,(bullet->x>>4),(bullet->y>>4));
    }else{

        if((bullet->explode>>4)<5){

            uint8_t n= move_metasprite(SmallExplosion_metasprites[bullet->explode>>4],SMALL_EXPLOSION_TILES_START,startingSprite,(bullet->x>>4),(bullet->y>>4)+8);

            bullet->explode+=4;

            return n;
        }else{
            
            bullet->active=FALSE;
            return 0;
        }
        
    }
}

uint8_t UpdateAllBullets(uint8_t startingSprite){

    maxX=0;
    minX=160<<4;
    maxY=0;
    minY=144<4;

    uint8_t resort=FALSE;
    for(uint8_t i=0;i<MAX_NUMBER_BULLETS;i++){

        if(bullets[i].active){
            
            startingSprite+=UpdateBullet(&bullets[i],startingSprite);
            if(!bullets[i].active){
                resort=TRUE;
            }
        }else{
            break;
        }
    }
    if(resort){
        ReSortBullets();
    }
    return startingSprite;
}