#include <gb/gb.h>
#include "enemies.h"
#include "bullets.h"
#include "common.h"
#include "graphics/PlayerPlane.h"
#include "graphics/Bullets.h"
#include "graphics/MediumExplosion.h"
#include "graphics/SmallExplosion.h"
#include "graphics/SmallEnemyPlane.h"

EnemyPlane enemies[MAX_NUMBER_ENEMIES_ON_SCREEN];
uint8_t enemiesOnScreen=0;
uint8_t lastCheck=0;

extern uint8_t currentPathIndex,currentLevel,enemySpawnDelay;


extern uint16_t playerDamageTimer,enemiesShot;
extern uint32_t score;
extern int8_t playerHealth;


const int16_t Horizontal[]={10,10,10,10,10,10,10,10,10,10,10,10,10,9,9,9,9,9,9,9,9,9,9,8,8,8,8,8,8,8,7,7,7,7,7,7,6,6,6,6,6,5,5,5,5,4,4,4,4,4,3,3,3,3,2,2,2,2,1,1,1,1,0,0,0,0,0,-1,-1,-1,-1,-2,-2,-2,-2,-3,-3,-3,-3,-4,-4,-4,-4,-4,-5,-5,-5,-5,-6,-6,-6,-6,-6,-7,-7,-7,-7,-7,-7,-8,-8,-8,-8,-8,-8,-8,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-8,-8,-8,-8,-8,-8,-8,-7,-7,-7,-7,-7,-7,-6,-6,-6,-6,-6,-5,-5,-5,-5,-4,-4,-4,-4,-4,-3,-3,-3,-3,-2,-2,-2,-2,-1,-1,-1,-1,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,4,5,5,5,5,6,6,6,6,6,7,7,7,7,7,7,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10};
const int16_t Vertical[]={0,0,0,-1,-1,-1,-1,-2,-2,-2,-2,-3,-3,-3,-3,-4,-4,-4,-4,-4,-5,-5,-5,-5,-6,-6,-6,-6,-6,-7,-7,-7,-7,-7,-7,-8,-8,-8,-8,-8,-8,-8,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-8,-8,-8,-8,-8,-8,-8,-7,-7,-7,-7,-7,-7,-6,-6,-6,-6,-6,-5,-5,-5,-5,-4,-4,-4,-4,-4,-3,-3,-3,-3,-2,-2,-2,-2,-1,-1,-1,-1,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,4,5,5,5,5,6,6,6,6,6,7,7,7,7,7,7,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,9,9,9,9,9,9,9,9,9,8,8,8,8,8,8,8,7,7,7,7,7,7,6,6,6,6,6,5,5,5,5,4,4,4,4,4,3,3,3,3,2,2,2,2,1,1,1,1,0,0};
const uint8_t Frames[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8};



int16_t baseOffsetDirs[4][2]= {
{0,1},
{1,0},
{0,1},
{1,0},
};

uint16_t baseDirections[4]= {
FACING_RIGHT<<1,
FACING_DOWN<<1,
FACING_LEFT<<1,
FACING_UP<<1
};

int16_t basePositions[4][2]= {
{-8,72},
{80,-8},
{168,72},
{80,152}
};

void UpdateScore();
void UpdatePlayerHealth();

void SetupEnemies(){
    
    for(uint8_t i=0;i<MAX_NUMBER_ENEMIES_ON_SCREEN;i++){
        enemies[i].active=FALSE;
    }
    enemiesOnScreen=0;
}

void SortEnemies(){
    
    EnemyPlane enemiesTemp[MAX_NUMBER_ENEMIES_ON_SCREEN];

    uint8_t i=0,activeCount=0;

    for(i=0;i<MAX_NUMBER_ENEMIES_ON_SCREEN;i++)enemiesTemp[i].active=FALSE;


    for(i=0;i<MAX_NUMBER_ENEMIES_ON_SCREEN;i++){
        if(enemies[i].active){
            enemiesTemp[activeCount++]=enemies[i];
        }
    }

    for(i=0;i<MAX_NUMBER_ENEMIES_ON_SCREEN;i++){
        enemies[i]=enemiesTemp[i];
    }

}

EnemyPlane* SpawnEnemy(){
    
    for(uint8_t i=0;i<MAX_NUMBER_ENEMIES_ON_SCREEN;i++){

        // IF this enemy isn't active, we will use it
        if(!enemies[i].active){
            enemies[i].active=TRUE;
            enemies[i].health=3;
            enemies[i].flash=0;


            // Increase how many enemies we have on screeen
            enemiesOnScreen++;

            
            return &enemies[i];
        }
    }

    return 0;
}

uint8_t move_metasprite_props(const metasprite_t* current, uint8_t base_tile, uint8_t base_sprite, uint8_t x, uint8_t y,uint8_t props) {
    metasprite_t temp[8];


    for(uint8_t i=0;i<8;i++){
    
        // Retain sprite position, and tile
        temp[i].dy=current->dy;
        temp[i].dx=current->dx;
        temp[i].dtile=current->dtile;
        temp[i].props=current->props;

        // If we should blink for damage
        // Change the properties, but retain the flip
        temp[i].props= props | current->props;
        current++;
    }

    const metasprite_t *tempPtr=temp;

    // hide or show the metasprites
    return move_metasprite(tempPtr,base_tile,base_sprite,x,y);
}

uint8_t CollisionTestAgainstBullets(EnemyPlane* enemy){
     uint8_t n=lastCheck+3;

    uint8_t alive = 1;

    for(lastCheck;lastCheck<n;lastCheck++){
        if(bullets[lastCheck].active){
            if(bullets[lastCheck].explode>=0)continue;
            int16_t yd =bullets[lastCheck].y-enemy->y;
            if(yd>128)continue;
            if(yd<-128)continue;

            int16_t xd =bullets[lastCheck].x-enemy->x;
            if(xd>128)continue;
            if(xd<-128)continue;
            enemy->health--;
            if(enemy->health==0){
                enemiesShot++;
            }
            enemy->flash=3;
            bullets[lastCheck].explode=0;
            score+=50;
            UpdateScore();

        }else{
            lastCheck=0;
            break;
        }
    }
    return 1;
}


uint8_t UpdateSingleEnemy(EnemyPlane* enemy,uint8_t startSprite){

    uint8_t alive = enemy->health>-(5<<4);
    
    if(enemy->delay>0){
        enemy->delay--;
        return 0;
    }else if(enemy->health>0){

        // Update according to our path
        if(enemy->velocityY>0)alive= enemy->y<160<<4;
        else if(enemy->velocityY<0)alive= enemy->y>-34<<4;
        else if(enemy->velocityX>0)alive= enemy->x<160<<4;
        else if(enemy->velocityX<0)alive= enemy->x>-34<<4;

        if(alive){
            
                
            if(playerDamageTimer==0){

                int16_t xd = (enemy->x)-(playerPlaneX);

                if(xd<0)xd=-xd;

                if(xd<(16<<4)){
                    int16_t yd = (enemy->y)-(playerPlaneY);

                    if(yd<0)yd=-yd;

                    if(yd<(14<<4)){
                        NR41_REG=0x3F;
                        NR42_REG=0xA1;
                        NR43_REG=0x44;
                        NR44_REG=0xC0;
                        playerHealth--;
                        enemy->health=0;
                        
                        UpdatePlayerHealth();
                        playerDamageTimer=90;
                    }
                }
            }

            // Make sure we are aligned horizontally somewhat, and in front of the player
            if(enemy->x>playerPlaneX-248&&enemy->x<playerPlaneX+248&&enemy->y<playerPlaneY){

                // Check againstbullets
                alive = CollisionTestAgainstBullets(enemy);

            }
        }
        enemy->x+=enemy->velocityX;
        enemy->y+=enemy->velocityY;
    }

    
    

    if(!alive){
        enemy->active=0;
        return 0;
    }else if(enemy->health<=0){

        uint8_t frame = (-enemy->health)>>4;

        enemy->health-=8;

        return move_metasprite(MediumExplosion_metasprites[frame],MEDIUM_EXPLOSION_TILES_START,startSprite,(enemy->x>>4),(enemy->y>>4)+8);
    }else{

        if(enemy->flash>0){
            enemy->flash--;
            return move_metasprite_props(SmallEnemyPlane_metasprites[9+enemy->frame],PlayerPlane_TILE_COUNT,startSprite,(enemy->x>>4),(enemy->y>>4)+8,7);
        }else{

            return move_metasprite(SmallEnemyPlane_metasprites[9+enemy->frame],PlayerPlane_TILE_COUNT,startSprite,(enemy->x>>4),(enemy->y>>4)+8);
        }
    }

}

void SpawnNextFormation(){

    uint8_t minEnemiesBeforeSpawnNew=3+currentLevel/15;

    // If enemies on screen is zero
    if(enemiesOnScreen<minEnemiesBeforeSpawnNew){

        if(currentPathIndex!=255){
            currentPathIndex=255;
        }
    }


    enemySpawnDelay++;
    if(enemySpawnDelay<15-currentLevel/5)return;
    
    if(enemiesOnScreen<minEnemiesBeforeSpawnNew){

        uint8_t spawnMultiple = (DIV_REG<20&&currentPathIndex==255);

        if(spawnMultiple){
            currentPathIndex = DIV_REG%16;
        }

        uint8_t count = spawnMultiple ? 1+DIV_REG%7 : 1;
        uint8_t type = DIV_REG%3;

        // Start at: left = 0, top = 1, right = 2, bottom = 3
        uint8_t position = spawnMultiple ? (DIV_REG+shadow_OAM[0].x)%4 : 1;
        int8_t offsetX = -60+(DIV_REG+shadow_OAM[0].x+shadow_OAM[0].y+shadow_OAM[1].x+shadow_OAM[1].y)%120;


        // Spawn an enemy for each enemy in the path
        for(uint8_t i=0;i<count;i++){
            
            // Spawn a new enemy
            EnemyPlane* e = SpawnEnemy();

            // Stop here if 0 is returned
            if(e==0)break;

            e->enemyType=type;
            e->x =(basePositions[position][0]+offsetX*baseOffsetDirs[position][0])<<4;
            e->y =(basePositions[position][1]+offsetX*baseOffsetDirs[position][1])<<4;
            e->enemyDirection=baseDirections[position];
            e->delay = i*35;
            e->frame=Frames[e->enemyDirection>>1];

            // Move in the direction we face
            e->velocityX=Horizontal[e->enemyDirection>>1];
            e->velocityY=Vertical[e->enemyDirection>>1];

            e->velocityX = (e->velocityX/3)*4;
            e->velocityY = (e->velocityY/3)*4;

        }

        enemySpawnDelay=0;

    }

}

uint8_t UpdateAllEnemies(uint8_t startingSprite,uint8_t completed){


    if(!completed){

        //Spawn the next formation
        SpawnNextFormation();
    }
    
    enemiesOnScreen=0;
    
    uint8_t resort=FALSE;

    for(uint8_t i=0;i<MAX_NUMBER_ENEMIES_ON_SCREEN;i++){

        // If this enemy is active
        if(enemies[i].active){

            // Update the enemy and the starting sprite
            startingSprite+=UpdateSingleEnemy(&enemies[i],startingSprite);

            // If this enemy is no longer active
            // We need to resort the array
            if(!enemies[i].active){
                resort=TRUE;
            }else{
                
                // Increase our count of enemies on screen
                enemiesOnScreen++;
            }
        }else{
            break;
        }
    }
    if(resort){
        SortEnemies();
    }
    return startingSprite;
}