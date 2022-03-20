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


void DrawNumber(uint8_t x,uint8_t y, uint32_t number,uint8_t digits){
	
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
}