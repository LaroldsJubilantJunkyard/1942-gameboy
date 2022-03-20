<<<<<<< HEAD
#include <gb/gb.h>
#include "common.h"
#include <stdlib.h>
#include <string.h>

uint8_t joypadCurrent,joypadPrevious, timer;

int16_t playerPlaneX, playerPlaneY;

uint8_t drawOnBackground=TRUE;
    
void DrawTextWithPalette(uint8_t x, uint8_t y, unsigned char *text,uint8_t palette ){

    uint8_t i=0;

    // The VRAM address of the first character
    // After setting a tile, we'll increase the VRAM address each iteration to move to the next tile
    VBK_REG=0;
    uint8_t *vramAddr= get_bkg_xy_addr(x,y);
    if(drawOnBackground==FALSE)vramAddr= get_win_xy_addr(x,y);

    while(text[i]!='\0'){
    VBK_REG=0;

        // Map our alphabet characters to only use uppercase letters
        // From the SpaceInvadersFont.png/aseprite
        if(text[i]>='A'&&text[i]<='Z')set_vram_byte(vramAddr++,1+(text[i]-'A'));
        else if(text[i]>='a'&&text[i]<='z')set_vram_byte(vramAddr++,1+(text[i]-'a'));
        else if(text[i]>='0'&&text[i]<='9')set_vram_byte(vramAddr++,27+(text[i]-'0'));

        else {

            // Map our special characters manually
            // From the SpaceInvadersFont.png/aseprite
            switch(text[i]){
                case ':': set_vram_byte(vramAddr++,37); break;
                case '!': set_vram_byte(vramAddr++,38); break;
                case '%': set_vram_byte(vramAddr++,39);break;
                case '.': set_vram_byte(vramAddr++,40);break;
                default: vramAddr++; break;
            }
        }

        if(palette!=255){
            VBK_REG=1;
            if(drawOnBackground==FALSE)set_win_tile_xy(x+i,y,palette);
            else set_bkg_tile_xy(x+i,y,palette);
        }

        i++;
    }
    VBK_REG=0;

    drawOnBackground=FALSE;
}

=======
#include "gb/gb.h"
#include "common.h"
#include <stdlib.h>
#include <string.h>
#include "gb/metasprites.h"
#include "graphics/Dinosaur.h"
#include "graphics/Cactus.h"
#include "graphics/TitleScreen.h"
#include "graphics/ArcticBackground.h"
#include "graphics/DesertBackground.h"
#include "graphics/ForestBackground.h"
#include "graphics/VolcanoesBackground.h"
#include "graphics/Buttons.h"
#include "graphics/Font.h"



Obstacle cactii[MAX_NUMBER_CACTUS];

uint32_t score=0;
uint32_t highScore=0;

int16_t moveSpeed=1;
int16_t jumpVelocity=0;
int16_t aboveGround=0;
int16_t dinoX=DINOSAUR_LEFT;

uint16_t damageBlinker=0;
uint16_t spawnX=0;
uint16_t counter=0;
uint16_t frameCounter=0;
uint16_t backgroundFadeColors[28];
uint16_t spriteFadeColors[20];

uint8_t fadeAmount=0;
uint8_t health=3;
uint8_t activeCatii=0;
uint8_t joypadCurrent,joypadPrevious;
uint8_t started=0;
uint8_t frame = 0;
uint8_t level =0;
uint8_t state = 255, nextState = MENU;
uint8_t startSprite=0;


const Level levels[]={
    {DesertBackground_tiles,DesertBackground_TILE_COUNT,0,DesertBackground_map,DesertBackground_map_attributes,"Desert"},
    {ForestBackground_tiles,ForestBackground_TILE_COUNT,2,ForestBackground_map,ForestBackground_map_attributes,"Forest"},
    {ArcticBackground_tiles,ArcticBackground_TILE_COUNT,4,ArcticBackground_map,ArcticBackground_map_attributes,"Arctic"},
    {VolcanoesBackground_tiles,VolcanoesBackground_TILE_COUNT,6,VolcanoesBackground_map,VolcanoesBackground_map_attributes,"Volcanoes"}
};



void ClearWindowTopRow(){
    
    VBK_REG=1;fill_win_rect(0,0,32,1,FONT_PALETTE_INDEX);
    VBK_REG=0;fill_win_rect(0,0,32,1,0);
}

void SetColorPalettesItem(uint16_t* original,uint16_t* palette,uint8_t count){

    for(uint8_t i=0;i<count;i++){


        for(uint8_t j=0;j<4;j++){

            uint8_t index = i*4+j;
            
            //#define RGB(r, g, b) ((((uint16_t)(b) & 0x1f) << 10) | (((uint16_t)(g) & 0x1f) << 5) | (((uint16_t)(r) & 0x1f) << 0))

            // The colors are respresented with 5 bit numbers
            // All bitwise-ORed into a single 16 value
            // The remaining bit is at the front, and is ignored
            // Bit 15 (ignored), Bits 14-10 (blue), Bits 9-5 (green), Bits 4-0 (red) 
            // To get blue, we shift to the right 10 bits, and bitwise-OR the result with 31 (whose binary value is 11111)
            // To get green, we shift to the right 5 bits, and bitwise-OR the result with 31 (whose binary value is 11111)
            // To get red, we bitwise-OR the value with 31 (whose binary value is 11111)
            // We'll multiply by 8 to getthe value ranging from 0-255
            uint16_t red = (original[index] & 31)*8;
            uint16_t green =(( original[index]>>5)&31)*8;
            uint16_t blue = ((original[index]>>10) & 31)*8;

            // How much each color should fade per step
            // Some colors have lower values and should fade more
            // If red has an original value of 3, and blue has an original value of 30:
            // Over 3 steps, red should fade by 1 each step, and blue should fade by 10
            uint16_t blueFadeAmount = (255-blue)/FADE_STEPS;
            uint16_t redFadeAmount = (255-red)/FADE_STEPS;
            uint16_t greenFadeAmount = (255-green)/FADE_STEPS;

            // Get the new value but cap at 255 or some problems may occur
            blue = MIN(blue+blueFadeAmount*fadeAmount,255);
            green = MIN(green+greenFadeAmount*fadeAmount,255);
            red = MIN(red+redFadeAmount*fadeAmount,255);

            // Set our color in the array for later use with set_<sprite|bkg>_palette
            palette[index]=RGB8(red,green,blue);

        }

        
    }
}

void FadeIn(uint8_t fadeTarget){
    

    while(fadeAmount>=1){
    
        fadeAmount--;

        if(fadeTarget & FADE_BACKGROUND)SetColorPalettesItem(DesertBackground_palettes,backgroundFadeColors,NUMBER_OF_BACKGROUND_PALETTES);
        if(fadeTarget & FADE_SPRITES)SetColorPalettesItem(Dinosaur_palettes,spriteFadeColors,NUMBER_OF_SPRITE_PALETTES);
        
        if(fadeTarget & FADE_BACKGROUND)set_bkg_palette(0,NUMBER_OF_BACKGROUND_PALETTES,backgroundFadeColors);    
        if(fadeTarget & FADE_SPRITES)set_sprite_palette(0,NUMBER_OF_SPRITE_PALETTES,spriteFadeColors);    

        wait_vbl_done();  
    }

}

void FadeOut(uint8_t fadeTarget){
    

    while(fadeAmount<=FADE_STEPS){
    
        fadeAmount++;

        if(fadeTarget & FADE_BACKGROUND)SetColorPalettesItem(DesertBackground_palettes,backgroundFadeColors,NUMBER_OF_BACKGROUND_PALETTES);
        if(fadeTarget & FADE_SPRITES)SetColorPalettesItem(Dinosaur_palettes,spriteFadeColors,NUMBER_OF_SPRITE_PALETTES);
        
        if(fadeTarget & FADE_BACKGROUND)set_bkg_palette(0,NUMBER_OF_BACKGROUND_PALETTES,backgroundFadeColors);    
        if(fadeTarget & FADE_SPRITES)set_sprite_palette(0,NUMBER_OF_SPRITE_PALETTES,spriteFadeColors);    

        wait_vbl_done();  
    }
}
>>>>>>> f56a82457c94c5a3aa9ff8d031aa867438501f7a

void DrawNumber(uint8_t x,uint8_t y, uint32_t number,uint8_t digits){
	
    unsigned char buffer[8]="00000000";

    // Convert the number to a decimal string (stored in the buffer char array)
    uitoa(number, buffer, 10);

    // The background address of the first digit
<<<<<<< HEAD
    uint8_t *vramAddr= get_bkg_xy_addr(x,y);
    if(drawOnBackground==FALSE)vramAddr= get_win_xy_addr(x,y);
=======
    uint8_t *vramAddr= get_win_xy_addr(x,y);
>>>>>>> f56a82457c94c5a3aa9ff8d031aa867438501f7a

    // Get the length of the number so we can add leading zeroes
    uint8_t len =strlen(buffer);

    // Add some leading zeroes
    // uitoa will not do this for us
    // Increase the VRAM address each iteration to move to the next tile
<<<<<<< HEAD
    for(uint8_t i=0;i<digits-len;i++)        
        set_vram_byte(vramAddr++,27);
        
    // Draw our number
    // Increase the VRAM address each iteration to move to the next tile
    for(uint8_t i=0;i<len;i++)        
        set_vram_byte(vramAddr++,(buffer[i]-'0')+27);


    drawOnBackground=FALSE;
}
void DrawText(uint8_t x, uint8_t y, unsigned char *text){
    DrawTextWithPalette(x,y,text,255);
=======
    for(uint8_t i=0;i<digits-len;i++){
        
        VBK_REG=1;set_vram_byte(vramAddr,FONT_PALETTE_INDEX); 
        VBK_REG=0; set_vram_byte(vramAddr++,27);
    }
        
    // Draw our number
    // Increase the VRAM address each iteration to move to the next tile
    for(uint8_t i=0;i<len;i++) {   
        VBK_REG=1;set_vram_byte(vramAddr,FONT_PALETTE_INDEX);  
        VBK_REG=0;set_vram_byte(vramAddr++,(buffer[i]-'0')+27);
    }


}

void DrawTextWithPalette(uint8_t x, uint8_t y, unsigned char *text ){

    uint8_t i=0;

    // The VRAM address of the first character
    // After setting a tile, we'll increase the VRAM address each iteration to move to the next tile
    uint8_t *vramAddr= get_win_xy_addr(x,y);

    while(text[i]!='\0'){

        VBK_REG=1;set_vram_byte(vramAddr,FONT_PALETTE_INDEX); 
        VBK_REG=0;
        // Map our alphabet characters to only use uppercase letters
        // From the SpaceInvadersFont.png/aseprite
        if(text[i]>='A'&&text[i]<='Z')set_vram_byte(vramAddr++,1+(text[i]-'A'));
        else if(text[i]>='a'&&text[i]<='z')set_vram_byte(vramAddr++,1+(text[i]-'a'));
        else if(text[i]>='0'&&text[i]<='9')set_vram_byte(vramAddr++,27+(text[i]-'0'));

        else {

            // Map our special characters manually
            // From the SpaceInvadersFont.png/aseprite
            switch(text[i]){
                case '!': set_vram_byte(vramAddr++,37); break;
                case ':': set_vram_byte(vramAddr++,38);break;
                case '?': set_vram_byte(vramAddr++,39); break;
                case '/': set_vram_byte(vramAddr++,40);break;
                case '=': set_vram_byte(vramAddr++,41);break;
                case ',': set_vram_byte(vramAddr++,42);break;
                case '.': set_vram_byte(vramAddr++,43);break;
                default: vramAddr++; break;
            }
        }

        i++;
    }

}


void UpdateColorPalettes(){
    SetColorPalettesItem(DesertBackground_palettes,backgroundFadeColors,NUMBER_OF_BACKGROUND_PALETTES);
    SetColorPalettesItem(Dinosaur_palettes,spriteFadeColors,NUMBER_OF_SPRITE_PALETTES);

    set_bkg_palette(0,NUMBER_OF_BACKGROUND_PALETTES,backgroundFadeColors);    
    set_sprite_palette(0,NUMBER_OF_SPRITE_PALETTES,spriteFadeColors);  
>>>>>>> f56a82457c94c5a3aa9ff8d031aa867438501f7a
}