#include "stdio.h"

#include "raylib.h"
#include "paddle.h"
#include "ball.h"
#include "coin.h"
#include "shop.h"
#include "game.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    

    int gameState = 0;
    unsigned char* raw;
    int hiScore = 0;
    unsigned int size = 0;
    int frame = 0;
    int score = 0;
    
    //loading data
    if(FileExists(R"(data/score.g)"))hiScore = static_cast<int>(*LoadFileData("data/score.g",&size));
    if(FileExists(R"(data/coins.g)"))coins = static_cast<int>(*LoadFileData("data/coins.g",&size));
    
    
    bool dead = false;
    bool quit = false;
    Init();
    


    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose() && !quit)    // Detect window close button or ESC key
    {
        

        // Update
        //----------------------------------------------------------------------------------
        switch (gameState)
        {
        case 0:
            titleScreen(frame,gameState, quit);
            break;
        
        case 1:
            gameUpdate(score,frame,dead,gameState);
            break;
        case 2:
            deadUpdate(dead,gameState,score,hiScore,coins);
            break;
        case 3:
            settingsMenu(gameState);
            break;
        case 4:
            shopScreen(gameState);
        }
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
       
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    Exit(hiScore, coins);
    //--------------------------------------------------------------------------------------

    return 0;
}