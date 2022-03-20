#include "gb/gb.h"
#include "common.h"


<<<<<<< HEAD


uint8_t Start_CopyrightGameState();uint8_t Update_CopyrightGameState();uint8_t End_CopyrightGameState();
uint8_t Start_LaroldsJubilantJunkyardGameState();uint8_t Update_LaroldsJubilantJunkyardGameState();uint8_t End_LaroldsJubilantJunkyardGameState();
uint8_t Start_StartScreenGameState();uint8_t Update_StartScreenGameState();uint8_t End_StartScreenGameState();
uint8_t Start_MenuScreenGameState();uint8_t Update_MenuScreenGameState();uint8_t End_MenuScreenGameState();
uint8_t Start_NextLevelGameState();uint8_t Update_NextLevelGameState();uint8_t End_NextLevelGameState();
uint8_t Start_GameplayGameState();uint8_t Update_GameplayGameState();uint8_t End_GameplayGameState();
uint8_t Start_ResultsGameState();uint8_t Update_ResultsGameState();uint8_t End_ResultsGameState();
uint8_t Start_OptionsGameState();uint8_t Update_OptionsGameState();uint8_t End_OptionsGameState();
uint8_t Start_PasswordGameState();uint8_t Update_PasswordGameState();uint8_t End_PasswordGameState();


const uint8_t (*AllGameStates[][3])(void)={
    {0,0,0},
    {&Start_CopyrightGameState,&Update_CopyrightGameState,&End_CopyrightGameState},
    {&Start_LaroldsJubilantJunkyardGameState,&Update_LaroldsJubilantJunkyardGameState,&End_LaroldsJubilantJunkyardGameState},
    {&Start_StartScreenGameState,&Update_StartScreenGameState,&End_StartScreenGameState},
    {&Start_MenuScreenGameState,&Update_MenuScreenGameState,&End_MenuScreenGameState},
    {&Start_NextLevelGameState,&Update_NextLevelGameState,&End_NextLevelGameState},
    {&Start_GameplayGameState,&Update_GameplayGameState,&End_GameplayGameState},
    {&Start_ResultsGameState,&Update_ResultsGameState,&End_ResultsGameState},
    {&Start_OptionsGameState,&Update_OptionsGameState,&End_OptionsGameState},
    {&Start_PasswordGameState,&Update_PasswordGameState,&End_PasswordGameState}
};

void main(void){

    DISPLAY_ON;
    SHOW_BKG;
    SHOW_SPRITES;
    SPRITES_8x16;
    SHOW_WIN;


    uint8_t currenGameState=GAMEFIRSTLOAD;
    uint8_t nextGameState=GAMEPLAY_GAMESTATE;

    while(TRUE){

        joypadPrevious=joypadCurrent;
        joypadCurrent=joypad();

        // If we should change gamestate
        if(currenGameState!=nextGameState){
            
            // Call our game state's end function
            if(currenGameState!=GAMEFIRSTLOAD)AllGameStates[currenGameState][2]();

            currenGameState=nextGameState;
            
            // Call our new game states start function
            AllGameStates[currenGameState][0]();
        }

        // Update our gamestate
        nextGameState = AllGameStates[currenGameState][1]();

        wait_vbl_done();
    }
=======
void SetupMenu();
void SetupLevelSelect();
void SetupGameplay();
void SetupGameOver();

void UpdateMenu();
void UpdateLevelSelect();
void UpdateGameplay();
void UpdateGameOver();

void main(){

    SHOW_BKG;
    SHOW_WIN;
    SHOW_SPRITES;
    SPRITES_8x16;

    level=0;

    fadeAmount=FADE_STEPS;
    
    UpdateColorPalettes();  

    move_win(7,128);

    // Fill our window with all white
    VBK_REG=1;fill_win_rect(0,0,32,32,FONT_PALETTE_INDEX);
    VBK_REG=0;fill_win_rect(0,0,32,32,0);

    state=GAME_FIRST_LOAD;
    nextState=MENU;

    // Loop infinitely
    while(TRUE){

        counter++;

        // Get the latest joypad state
        // Save the current joypad state also
        joypadPrevious=joypadCurrent;
        joypadCurrent=joypad();

        // If we are changing game states
        if(state!=nextState){

            state=nextState;

            // Call our new states' setup logic
            switch(state){
                case MENU:SetupMenu();break;
                case LEVEL_SELECT: SetupLevelSelect();break;
                case GAMEPLAY:SetupGameplay();break;
                case GAME_OVER:SetupGameOver();break;
                default:break;
            }

            joypadCurrent=0;
        }

        // Call our game state's update logic
        switch(state){

            case MENU: UpdateMenu(); break;
            case LEVEL_SELECT: UpdateLevelSelect(); break;
            case GAMEPLAY: UpdateGameplay(); break;
            case GAME_OVER: UpdateGameOver(); break;
            default:break;
        }


        wait_vbl_done();


    }

>>>>>>> f56a82457c94c5a3aa9ff8d031aa867438501f7a
}