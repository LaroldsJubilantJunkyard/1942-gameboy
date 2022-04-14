#include <gb/gb.h>
#include "common.h"
#include <stdlib.h>
#include <string.h>
#include "graphics/PlaneScreen.h"
#include "graphics/PlayerPlane.h"

uint8_t joypadCurrent,joypadPrevious, timer;

int16_t playerPlaneX, playerPlaneY;

uint8_t drawOnBackground=TRUE;
uint32_t score;
uint16_t backgroundFadeColors[28];
uint16_t spriteFadeColors[20];

uint8_t fadeAmount=0;
uint8_t health=3;

    
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



void DrawNumberWithPalette(uint8_t x,uint8_t y, uint32_t number,uint8_t digits,uint8_t palette){
	
    unsigned char buffer[8]="00000000";

    // Convert the number to a decimal string (stored in the buffer char array)
    uitoa(number, buffer, 10);

    // The background address of the first digit
    uint8_t *vramAddr= get_bkg_xy_addr(x,y);
    if(drawOnBackground==FALSE)vramAddr= get_win_xy_addr(x,y);

    // Get the length of the number so we can add leading zeroes
    uint8_t len =strlen(buffer);

    // Add some leading zeroes
    // uitoa will not do this for us
    // Increase the VRAM address each iteration to move to the next tile
    for(uint8_t i=0;i<digits-len;i++){
        VBK_REG=1 ;
        set_vram_byte(vramAddr,palette);
        VBK_REG=0 ;
        set_vram_byte(vramAddr++,27);
    }
        
    // Draw our number
    // Increase the VRAM address each iteration to move to the next tile
    for(uint8_t i=0;i<len;i++){
        VBK_REG=1 ;
        set_vram_byte(vramAddr,palette);
        VBK_REG=0 ;
        set_vram_byte(vramAddr++,(buffer[i]-'0')+27);
    }


    drawOnBackground=FALSE;
}

void DrawNumber(uint8_t x,uint8_t y, uint32_t number,uint8_t digits){
	
    DrawNumberWithPalette(x,y,number,digits,0);
}

void DrawText(uint8_t x, uint8_t y, unsigned char *text){
    DrawTextWithPalette(x,y,text,255);
}

/*
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

        if(fadeTarget & FADE_BACKGROUND)SetColorPalettesItem(PlaneScreen_palettes,backgroundFadeColors,NUMBER_OF_BACKGROUND_PALETTES);
        if(fadeTarget & FADE_SPRITES)SetColorPalettesItem(PlayerPlane_palettes,spriteFadeColors,NUMBER_OF_SPRITE_PALETTES);
        
        if(fadeTarget & FADE_BACKGROUND)set_bkg_palette(0,NUMBER_OF_BACKGROUND_PALETTES,backgroundFadeColors);    
        if(fadeTarget & FADE_SPRITES)set_sprite_palette(0,NUMBER_OF_SPRITE_PALETTES,spriteFadeColors);    

        wait_vbl_done();  
    }

}

void FadeOut(uint8_t fadeTarget){
    

    while(fadeAmount<=FADE_STEPS){
    
        fadeAmount++;

        if(fadeTarget & FADE_BACKGROUND)SetColorPalettesItem(PlaneScreen_palettes,backgroundFadeColors,NUMBER_OF_BACKGROUND_PALETTES);
        if(fadeTarget & FADE_SPRITES)SetColorPalettesItem(PlayerPlane_palettes,spriteFadeColors,NUMBER_OF_SPRITE_PALETTES);
        
        if(fadeTarget & FADE_BACKGROUND)set_bkg_palette(0,NUMBER_OF_BACKGROUND_PALETTES,backgroundFadeColors);    
        if(fadeTarget & FADE_SPRITES)set_sprite_palette(0,NUMBER_OF_SPRITE_PALETTES,spriteFadeColors);    

        wait_vbl_done();  
    }
}
*/