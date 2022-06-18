#include <gb/gb.h>
#include <gb/metasprites.h>
#include "graphics/Bullets.h"
#include "graphics/PlayerPlane.h"
#include "graphics/Bullets.h"
#include "graphics/SmallEnemyPlane.h"
#include "graphics/PlayerPlaneMini.h"
#include "graphics/SmallExplosion.h"
#include "graphics/MediumExplosion.h"
#include "bullets.h"
#include "common.h"
#include "enemies.h"

Bullet bullets[MAX_NUMBER_BULLETS];
Bullet* firstBullet=0;
Bullet* lastBullet=0;

int16_t minX,minY,maxX,maxY;

uint16_t bulletsFired;
uint16_t bulletsMissed;


void SpawnBullet(int16_t x, int16_t y){

    for(uint8_t i=0;i<MAX_NUMBER_BULLETS;i++){
        if(!bullets[i].active){
            bullets[i].x=x;
            bullets[i].y=y;
            bullets[i].explode=-1;
            bullets[i].active=TRUE;
            bullets[i].next=0;
            bulletsFired++;

            // IF we don't have a first bullet
            if(firstBullet==0){

                // We are first
                firstBullet=&bullets[i];
            }

            // If we have any active bullets
            else if(lastBullet!=0){

                // We are next
                lastBullet->next=&bullets[i];
            }

            // Update our last bullet
            lastBullet=&bullets[i];
            break;
        }
    }
}


void SetupBullets(){

    bulletsFired=0;
    bulletsMissed=0;

    lastBullet=0;
    firstBullet=0;

    for(uint8_t i=0;i<MAX_NUMBER_BULLETS;i++){
        bullets[i].next=0;
        bullets[i].active=FALSE;
    }
}

void RecycleBullet(Bullet* bullet){

    if(firstBullet==bullet){
        firstBullet=bullet->next;
    }

    //Clear the last bullet
    // We'll change it in the next for loop if necccssary
    if(lastBullet==bullet)lastBullet=0;

    
    Bullet* updateBullet = firstBullet;

    while (updateBullet!=0)
    {
         if(updateBullet->next==bullet){

            // Pass on to the next one
            updateBullet->next=bullet->next;

            // If we are the lasst bullt
            if(lastBullet==bullet){

                // Use the one before us
                lastBullet=updateBullet;
            }

            break;
         }
        
        updateBullet=updateBullet->next;
    }

    bullet->active=FALSE;
    bullet->next=0;

   
}

uint8_t UpdateBullet(Bullet* bullet, uint8_t startingSprite){
    if(bullet->explode==-1){
        bullet->y-=100;
        if(bullet->y<-128){
            bulletsMissed++;
            RecycleBullet(bullet);
            return 0;
        }
    }
    if(bullet->explode>=0){
        bullet->explode+=6;
        if(bullet->explode>>4>=5){
            RecycleBullet(bullet);
            return 0;
        }
        return move_metasprite(SmallExplosion_metasprites[bullet->explode>>4],SMALL_EXPLOSION_TILES_START,startingSprite,(bullet->x>>4)+4,(bullet->y>>4)+12);

    }else{

        return move_metasprite(Bullets_metasprites[0],BULLETS_START,startingSprite,(bullet->x>>4)+4,(bullet->y>>4)+12);
    }
}

uint8_t UpdateAllBullets(uint8_t startingSprite){

    maxX=0;
    minX=160<<4;
    maxY=0;
    minY=144<4;

    Bullet* updateBullet = firstBullet;

    while (updateBullet!=0)
    {
         
        startingSprite+=UpdateBullet(updateBullet,startingSprite);
        
        updateBullet=updateBullet->next;
    }
    
    return startingSprite;
}