#include <gb/gb.h>
#include "enemies.h"
#include "paths.h"
#include "bullets.h"
#include "common.h"
#include "graphics/PlayerPlane.h"
#include "graphics/SmallExplosion.h"
#include "graphics/MediumExplosion.h"
#include "graphics/Bullets.h"
#include "graphics/SmallEnemyPlane.h"

EnemyPlane enemies[MAX_NUMBER_ENEMIES_ON_SCREEN];
uint8_t enemiesOnScreen=0;
uint8_t lastCheck=0;
uint8_t enemySpawnDelay=0;
extern uint16_t playerDamageTimer,enemiesShot;
extern uint8_t currentPathIndex;
extern uint8_t currentLevel;
extern int8_t playerHealth;
extern const LevelData AllLevels[];

void UpdatePlayerHealth();
void UpdateScore();


void SetupEnemies(){
    
    for(uint8_t i=0;i<MAX_NUMBER_ENEMIES_ON_SCREEN;i++){
        enemies[i].active=FALSE;
    }
    enemiesOnScreen=0;
    enemySpawnDelay=0;
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

void SpawnEnemy(uint8_t enemyType,uint8_t path,uint8_t position,int16_t offsetX, int16_t offsetY,uint16_t delay){
    
    for(uint8_t i=0;i<MAX_NUMBER_ENEMIES_ON_SCREEN;i++){

        // IF this enemy isn't active, we will use it
        if(!enemies[i].active){
            enemies[i].active=TRUE;
            enemies[i].path=path;
            enemies[i].enemyType=enemyType;
            enemies[i].delay=delay;
            enemies[i].health=3;
            enemies[i].flash=0;
            enemies[i].explode=0;


            // Increase how many enemies we have on screeen
            enemiesOnScreen++;

            // Call our path's setup function
            AllPaths[path].Setup(&enemies[i],position,offsetX,offsetY);
            
            break;
        }
    }
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
            if(bullets[lastCheck].explode!=-1)continue;
            int16_t yd =bullets[lastCheck].y-enemy->y;
            if(yd>128)continue;
            if(yd<-128)continue;

            int16_t xd =bullets[lastCheck].x-enemy->x;
            if(xd>128)continue;
            if(xd<-128)continue;
            enemy->health--;
            NR41_REG=0x3F;
            NR42_REG=0xA1;
            NR43_REG=0x44;
            NR44_REG=0xC0;
            if(enemy->health<=0){
                alive=FALSE;
                score+=50;
                UpdateScore();
                enemiesShot++;

            }
            enemy->flash=3;
            bullets[lastCheck].explode=0;

        }else{
            lastCheck=0;
            break;
        }
    }
    return alive;
}

uint8_t UpdateSingleEnemy(EnemyPlane* enemy,uint8_t startSprite){

    uint8_t alive = enemy->health>0;

    if(alive){
        
        if(enemy->delay>0){
            enemy->delay--;
            return 0;
        }else{

            // Update according to our path
            alive = AllPaths[enemy->path].Update(enemy);

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
                            enemy->health=-1;
                            
                            UpdatePlayerHealth();
                            playerDamageTimer=90;
                            alive=FALSE;
                        }
                    }
                }

                // Make sure we are aligned horizontally somewhat, and in front of the player
                if(enemy->x>playerPlaneX-248&&enemy->x<playerPlaneX+248&&enemy->y<playerPlaneY){

                    // Check againstbullets
                    alive = CollisionTestAgainstBullets(enemy);

                }
            }
        
            
        }
    }

    
    

    if(!alive){
        if((enemy->explode>>4)<5){
            uint8_t n= move_metasprite(MediumExplosion_metasprites[enemy->explode>>4],MEDIUM_EXPLOSION_TILES_START,startSprite,(enemy->x>>4),(enemy->y>>4)+8);
            enemy->explode+=5;
            return n;
        }else{

            enemy->active=0;
        return 0;
        }
    }else{
        enemy->x+=enemy->velocityX;
        enemy->y+=enemy->velocityY;

        if(enemy->flash>0){
            enemy->flash--;
            return move_metasprite_props(SmallEnemyPlane_metasprites[9+enemy->frame],PlayerPlane_TILE_COUNT,startSprite,(enemy->x>>4),(enemy->y>>4)+8,7);
        }else{

            return move_metasprite(SmallEnemyPlane_metasprites[9+enemy->frame],PlayerPlane_TILE_COUNT,startSprite,(enemy->x>>4),(enemy->y>>4)+8);
        }
    }

}


void HandleEnemySpawning(){
    


    // If enemies on screen is zero
    if(enemiesOnScreen<AllLevels[currentLevel].minEnemiesBeforeSpawnNew){

        if(currentPathIndex!=255){
            currentPathIndex=255;
        }
    }


    enemySpawnDelay++;
    if(enemySpawnDelay<10)return;
    
    if(DIV_REG<20&&currentPathIndex==255&&enemiesOnScreen<AllLevels[currentLevel].minEnemiesBeforeSpawnNew){

        currentPathIndex = DIV_REG%16;

        uint8_t count = DIV_REG%7;
        uint8_t type = DIV_REG%3;
        uint8_t position = (DIV_REG+shadow_OAM[0].x)%3;
        uint8_t offsetX = -24+(DIV_REG+shadow_OAM[0].x+shadow_OAM[0].y)%48;
        uint8_t offsetY = -24+(DIV_REG-shadow_OAM[0].x-shadow_OAM[0].y)%48;
    
        //Get which path to spawn enemies for

        EnemyPath* path = &AllPaths[currentPathIndex];

        // Spawn an enemy for each enemy in the path
        for(uint8_t i=0;i<count;i++){


            uint8_t delay = i*30;
            
            // Spawn a new enemy
            SpawnEnemy( type, currentPathIndex, position, offsetX,offsetY, delay);
        }

        enemySpawnDelay=0;

    }else if(enemiesOnScreen<AllLevels[currentLevel].minEnemiesBeforeSpawnNew){

        uint8_t enemyType = DIV_REG%3;
        int8_t offsetX = 24-(DIV_REG%48);
        int8_t offsetY = -(DIV_REG%24);
                
        // Spawn a new enemy
        SpawnEnemy( enemyType, 3, MIDDLE, offsetX, offsetY, 0);

        enemySpawnDelay=0;
        
    }

}

uint8_t UpdateAllEnemies(uint8_t startingSprite, uint8_t completed){

    //Spawn the next path
    if(!completed)HandleEnemySpawning();
    
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