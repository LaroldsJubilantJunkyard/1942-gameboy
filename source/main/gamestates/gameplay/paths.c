#include <gb/gb.h>
#include "enemies.h"
#include "paths.h"
#include "common.h"

 int8_t Horizontal[]={10,10,10,10,10,10,10,10,10,10,10,10,10,9,9,9,9,9,9,9,9,9,9,8,8,8,8,8,8,8,7,7,7,7,7,7,6,6,6,6,6,5,5,5,5,4,4,4,4,4,3,3,3,3,2,2,2,2,1,1,1,1,0,0,0,0,0,-1,-1,-1,-1,-2,-2,-2,-2,-3,-3,-3,-3,-4,-4,-4,-4,-4,-5,-5,-5,-5,-6,-6,-6,-6,-6,-7,-7,-7,-7,-7,-7,-8,-8,-8,-8,-8,-8,-8,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-8,-8,-8,-8,-8,-8,-8,-7,-7,-7,-7,-7,-7,-6,-6,-6,-6,-6,-5,-5,-5,-5,-4,-4,-4,-4,-4,-3,-3,-3,-3,-2,-2,-2,-2,-1,-1,-1,-1,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,4,5,5,5,5,6,6,6,6,6,7,7,7,7,7,7,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10};
 int8_t Vertical[]={0,0,0,-1,-1,-1,-1,-2,-2,-2,-2,-3,-3,-3,-3,-4,-4,-4,-4,-4,-5,-5,-5,-5,-6,-6,-6,-6,-6,-7,-7,-7,-7,-7,-7,-8,-8,-8,-8,-8,-8,-8,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-8,-8,-8,-8,-8,-8,-8,-7,-7,-7,-7,-7,-7,-6,-6,-6,-6,-6,-5,-5,-5,-5,-4,-4,-4,-4,-4,-3,-3,-3,-3,-2,-2,-2,-2,-1,-1,-1,-1,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,4,5,5,5,5,6,6,6,6,6,7,7,7,7,7,7,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,9,9,9,9,9,9,9,9,9,8,8,8,8,8,8,8,7,7,7,7,7,7,6,6,6,6,6,5,5,5,5,4,4,4,4,4,3,3,3,3,2,2,2,2,1,1,1,1,0,0};
 uint8_t Frames[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8};


void AlignHorizontally(EnemyPlane* enemy,int8_t amount){

    if(enemy->x<playerPlaneX-128)enemy->velocityX = amount;
    if(enemy->x>playerPlaneX+128)enemy->velocityX = -amount;
}
void AlignVertially(EnemyPlane* enemy,int8_t amount){

    if(enemy->y<playerPlaneY-128)enemy->velocityY = amount;
    if(enemy->y>playerPlaneY+128)enemy->velocityY = -amount;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t FlyStraight(EnemyPlane* enemy){

    if(enemy->velocityX>0&&enemy->x>(168<<4))return FALSE;
    if(enemy->velocityX<0&&enemy->x<-(8<<4))return FALSE;
    if(enemy->velocityY>0&&enemy->y>(152<<4))return FALSE;
    if(enemy->velocityY<0&&enemy->y<-(8<<4))return FALSE;
    
    return TRUE;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t FlyTowardsPlayer_Upwards(EnemyPlane* enemy){


    enemy->enemyDirection=FACING_UP<<1;
    enemy->velocityY=-10;
    if(enemy->y>playerPlaneY)AlignHorizontally(enemy,5);
    enemy->frame=Frames[enemy->enemyDirection>>1];

    return enemy->x>-8<<4;
}

uint8_t FlyTowardsPlayer_Downwards(EnemyPlane* enemy){


    enemy->enemyDirection=FACING_DOWN<<1;
    enemy->velocityY=10;
    if(enemy->y<playerPlaneY)AlignHorizontally(enemy,5);
    enemy->frame=Frames[enemy->enemyDirection>>1];

    return enemy->y<152<<4;
}

uint8_t FlyTowardsPlayer_Rightwards(EnemyPlane* enemy){


    enemy->enemyDirection=FACING_RIGHT<<1;
    enemy->velocityX=10;
    if(enemy->x<playerPlaneX)AlignVertially(enemy,5);
    enemy->frame=Frames[enemy->enemyDirection>>1];

    return enemy->x<168<<4;
}

uint8_t FlyTowardsPlayer_Leftwards(EnemyPlane* enemy){


    enemy->enemyDirection=FACING_LEFT<<1;
    enemy->velocityX=-10;
    if(enemy->x>playerPlaneX)AlignVertially(enemy,5);
    enemy->frame=Frames[enemy->enemyDirection>>1];

    return enemy->x>-8<<4;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////



uint8_t Delayed_FlyTowardsPlayer_Upwards(EnemyPlane* enemy){


    enemy->enemyDirection=FACING_UP<<1;
    enemy->frame=Frames[enemy->enemyDirection>>1];
    enemy->velocityY=-10;
    if(enemy->y<playerPlaneY+(48<<4)){
        if(enemy->y>playerPlaneY)AlignHorizontally(enemy,5);
    }

    return enemy->x>-8<<4;
}

uint8_t Delayed_FlyTowardsPlayer_Downwards(EnemyPlane* enemy){


    enemy->enemyDirection=FACING_DOWN<<1;
    enemy->frame=Frames[enemy->enemyDirection>>1];
    enemy->velocityY=10;
    if(enemy->y>playerPlaneY-(48<<4)){
        if(enemy->y<playerPlaneY)AlignHorizontally(enemy,5);
    }

    return enemy->y<152<<4;
}

uint8_t Delayed_FlyTowardsPlayer_Rightwards(EnemyPlane* enemy){


    enemy->enemyDirection=FACING_RIGHT<<1;
    enemy->frame=Frames[enemy->enemyDirection>>1];
    enemy->velocityX=10;
    if(enemy->x>playerPlaneX-(48<<4)){
        if(enemy->x<playerPlaneX)AlignVertially(enemy,5);        
    }

    return enemy->x<168<<4;
}

uint8_t Delayed_FlyTowardsPlayer_Leftwards(EnemyPlane* enemy){


    enemy->enemyDirection=FACING_LEFT<<1;
    enemy->frame=Frames[enemy->enemyDirection>>1];
    enemy->velocityX=-10;
    if(enemy->x<playerPlaneX+(48<<4)){
        if(enemy->x>playerPlaneX)AlignVertially(enemy,5);
    }

    return enemy->x>-8<<4;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t TurnTowardsPlayerHorizontally(EnemyPlane* enemy,uint8_t leftwards){
    int8_t dir = leftwards?-1:1;


    // If we are on the bottom side of the player
    if(enemy->y>playerPlaneY+64){

        // Rotate based on which direction are coming from
        // Make sure this doesn't wrap around
        enemy->enemyDirection+=dir;
        if((enemy->enemyDirection>>1)>255)enemy->enemyDirection=0;
        
        // Move in the direction we face
        enemy->velocityX=Horizontal[enemy->enemyDirection>>1];
        enemy->velocityY=Vertical[enemy->enemyDirection>>1];

    // If we are on the top side of thep layer
    }else if(enemy->y<playerPlaneY-64){

        // Rotate based on which direction are coming from
        // Make sure this doesn't wrap around
        enemy->enemyDirection-=dir;
        if((enemy->enemyDirection>>1)>255)enemy->enemyDirection=255<<1;
        
        // Move in the direction we face
        enemy->velocityX=Horizontal[enemy->enemyDirection>>1];
        enemy->velocityY=Vertical[enemy->enemyDirection>>1];
    }else{
        
        // Change to the fly straight path now
        enemy->path=0;
        if(enemy->velocityY>0)enemy->velocityY=10;
        else enemy->velocityY=-10;
        enemy->velocityX=0;
        enemy->enemyDirection = ((enemy->velocityY>0)?FACING_DOWN:FACING_UP)<<1;

    }

    // Show the proper frame
    enemy->frame=Frames[enemy->enemyDirection>>1];

    // Return if we haven't gone out of the screen according to velocity direction
    return enemy->velocityX<0 ? (enemy->x>-(8<<4)) : (enemy->x<152<<4);
}


uint8_t TurnTowardsPlayerVertically(EnemyPlane* enemy,uint8_t upwards){
    int8_t dir = upwards?1:-1;


    // If we are on the right side of the player
    if(enemy->x>playerPlaneX+64){

        // Rotate based on which direction are coming from
        // Make sure this doesn't wrap around
        if(((enemy->enemyDirection+dir)>>1)<=255)enemy->enemyDirection+=dir;
        
        // Move in the direction we face
        enemy->velocityX=Horizontal[enemy->enemyDirection>>1];
        enemy->velocityY=Vertical[enemy->enemyDirection>>1];

    // If we are on the left side of thep layer
    }else if(enemy->x<playerPlaneX-64){

        // Rotate based on which direction are coming from
        // Make sure this doesn't wrap around
        if(((enemy->enemyDirection-dir)>>1)<=255)enemy->enemyDirection-=dir;
        
        // Move in the direction we face
        enemy->velocityX=Horizontal[enemy->enemyDirection>>1];
        enemy->velocityY=Vertical[enemy->enemyDirection>>1];
    }else{
        
        // Change to the fly straight path now
        enemy->path=0;
        if(enemy->velocityX>0)enemy->velocityX=10;
        else enemy->velocityX=-10;
        enemy->velocityY=0;
        enemy->enemyDirection = ((enemy->velocityX>0)?FACING_RIGHT:FACING_LEFT)<1;
    }

    // Show the proper frame
    enemy->frame=Frames[enemy->enemyDirection>>1];

    // Return if we haven't gone out of the screen according to velocity direction
    return enemy->velocityY<0 ? (enemy->y>-8<<4) : (enemy->y<168<<4);
}

uint8_t TurnTowardsPlayer_Upwards(EnemyPlane* enemy){
    return TurnTowardsPlayerVertically(enemy,TRUE);
}
uint8_t TurnTowardsPlayer_Downwards(EnemyPlane* enemy){
    return TurnTowardsPlayerVertically(enemy,FALSE);

}

uint8_t TurnTowardsPlayer_Leftwards(EnemyPlane* enemy){
    return TurnTowardsPlayerHorizontally(enemy,TRUE);
}
uint8_t TurnTowardsPlayer_Rightwards(EnemyPlane* enemy){
    return TurnTowardsPlayerHorizontally(enemy,FALSE);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t GetYPosition(uint8_t pos){
    if(pos==TOP_OR_LEFT)return 144/3;
    if(pos==MIDDLE)return 144/2;
    return (144/3)*2;
}

uint8_t GetXPosition(uint8_t pos){
    if(pos==TOP_OR_LEFT)return 160/3;
    if(pos==MIDDLE)return 160/2;
    return (160/3)*2;
}

void Setup_Bottom(EnemyPlane* enemy,uint8_t position,int16_t offsetX, int16_t offsetY){

    enemy->y=((144+offsetY)<<4)+8;
    enemy->x=((GetXPosition(position)+offsetX)<<4)+16;
    enemy->enemyDirection=FACING_UP<<1;
    enemy->frame=Frames[enemy->enemyDirection>>1];

    // Move in the direction we face
    enemy->velocityX=Horizontal[enemy->enemyDirection>>1];
    enemy->velocityY=Vertical[enemy->enemyDirection>>1];
}

void Setup_Top(EnemyPlane* enemy,uint8_t position,int16_t offsetX, int16_t offsetY){

    enemy->y=((offsetY)<<4)+8;
    enemy->x=((GetXPosition(position)+offsetX)<<4)+16;
    enemy->enemyDirection=FACING_DOWN<<1;
    enemy->frame=Frames[enemy->enemyDirection>>1];

    // Move in the direction we face
    enemy->velocityX=Horizontal[enemy->enemyDirection>>1];
    enemy->velocityY=Vertical[enemy->enemyDirection>>1];
}

void Setup_Left(EnemyPlane* enemy,uint8_t position,int16_t offsetX, int16_t offsetY){

    enemy->x=((offsetX)<<4)+8;
    enemy->y=((GetYPosition(position)+offsetY)<<4)+16;
    enemy->enemyDirection=FACING_RIGHT<<1;
    enemy->frame=Frames[enemy->enemyDirection>>1];
    

    // Move in the direction we face
    enemy->velocityX=Horizontal[enemy->enemyDirection>>1];
    enemy->velocityY=Vertical[enemy->enemyDirection>>1];
}

void Setup_Right(EnemyPlane* enemy,uint8_t position,int16_t offsetX, int16_t offsetY){

    enemy->x=((160+offsetX)<<4)+8;
    enemy->y=((GetYPosition(position)+offsetY)<<4)+16;
    enemy->enemyDirection=FACING_LEFT<<1;
    enemy->frame=Frames[enemy->enemyDirection>>1];

    // Move in the direction we face
    enemy->velocityX=Horizontal[enemy->enemyDirection>>1];
    enemy->velocityY=Vertical[enemy->enemyDirection>>1];
}

  EnemyPath AllPaths[]={

    {&Setup_Left,&FlyStraight},
    {&Setup_Bottom,&FlyStraight},
    {&Setup_Right,&FlyStraight},
    {&Setup_Top,&FlyStraight},

    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    {&Setup_Left,&FlyTowardsPlayer_Rightwards},
    {&Setup_Bottom,&FlyTowardsPlayer_Upwards},
    {&Setup_Right,&FlyTowardsPlayer_Leftwards},
    {&Setup_Top,&FlyTowardsPlayer_Downwards},

    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    {&Setup_Left,&Delayed_FlyTowardsPlayer_Rightwards},
    {&Setup_Bottom,&Delayed_FlyTowardsPlayer_Upwards},
    {&Setup_Right,&Delayed_FlyTowardsPlayer_Leftwards},
    {&Setup_Top,&Delayed_FlyTowardsPlayer_Downwards},

    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    {&Setup_Left,&TurnTowardsPlayer_Rightwards},
    {&Setup_Bottom,&TurnTowardsPlayer_Upwards},
    {&Setup_Right,&TurnTowardsPlayer_Leftwards},
    {&Setup_Top,&TurnTowardsPlayer_Downwards},
};
