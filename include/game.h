#define NAME "RUSH"
#include "raylib.h"
#include <direct.h>
struct Button
{
    Vector2 pos;
    Vector2 size;
    Color background;
    char* text;
    Color textColor;
    int fontSize;
    bool active = false;
};
bool buttonPressed(Button &button){
    if(CheckCollisionPointRec(GetMousePosition(),{button.pos.x,button.pos.y,button.size.x,button.size.y})){
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            return true;
        }
        else return false;
    }
    else return false;
}
void drawButton(Button &button){
    DrawRectangle(button.pos.x,button.pos.y,button.size.x,button.size.y,button.background);
    DrawText(button.text,button.pos.x + button.size.x/2 - MeasureText(button.text,button.fontSize)/2,button.pos.y + button.size.y/2 - button.fontSize/2,button.fontSize,button.textColor);

}
Button start;
Button settingsButton;
Button quitButton;
Button settingsReturn;
Button fullscreenToggleButton;
Button shopButton;
Button deathReturn;
Button shopReturn;
void Init(){
    start = {{GetScreenWidth()/2 - 250/2, GetScreenHeight()/2 - 50},{250,100},BLACK,"START",WHITE,50};
    settingsButton = {{GetScreenWidth()/2 - 250/2, GetScreenHeight()/2 + 100},{250,100},BLACK,"SETTINGS",WHITE,40};
    quitButton = {{GetScreenWidth()/2 - 250/2, GetScreenHeight()/2 + 250},{250,100},BLACK,"QUIT",WHITE,55};
    settingsReturn = {{GetScreenWidth()/2 - 250/2, GetScreenHeight() - 150},{250,100},BLACK,"RETURN",WHITE,40};
    fullscreenToggleButton = {{GetScreenWidth()/2 - 300/2, GetScreenHeight()/2 - 50},{300,100},BLACK,"TOGGLE FULLSCREEN",WHITE,25};
    shopButton = {{GetScreenWidth()/2 - 250/2, GetScreenHeight()/2 - 50},{250,100},BLACK,"SHOP",WHITE,50};
    deathReturn = {{GetScreenWidth()/2 - 250/2, GetScreenHeight()/2 + 100},{250,100},BLACK,"MENU",WHITE,50};
    shopReturn = {{GetScreenWidth()/2 - 250/2, GetScreenHeight() - 150},{250,100},BLACK,"RETURN",WHITE,40};
    ball.Reset();
    paddle.Reset();
    coin.pos = {GetRandomValue(50 + coin.rad,GetScreenWidth()-coin.rad),GetRandomValue(coin.rad, GetScreenHeight()-coin.rad )};
}



int coins = 0;
void gameUpdate(int &score,int &frame, bool &dead, int &gameState){
    frame++;
    if(frame > 1000)frame = 0;

     BeginDrawing();

            ClearBackground(BLACK);
            paddle.Update();
            ball.Update(paddle.rect, paddle.top, paddle.middle, paddle.bottom, score, dead,gameState);
            coin.Update(coins,ball.pos,ball.rad);
            DrawText(TextFormat("Score: %i", score), GetScreenWidth()/2 - MeasureText(TextFormat("%i",score), 40)/2 , 25, 40, WHITE);
            DrawText(TextFormat("Coins: %i",coins),0,25,40,WHITE);

    EndDrawing();  
        
        
}        
void deadUpdate(bool &dead, int &gameState, int &score, int &hiScore, int &coins){
    if(GetKeyPressed() != 0){
                if(score > hiScore) hiScore = score;
                dead = false;
                ball.Reset();
                paddle.Reset();
                gameState = 1;
                score = 0;
            }
    if(buttonPressed(deathReturn)) gameState = 0;
    if(buttonPressed(shopButton)) gameState = 4;
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("You Died", GetScreenWidth()/2 - MeasureText("You Died", 80)/2,100,80,BLACK);
        DrawText("Press Any Key To Continue", GetScreenWidth()/2 - MeasureText("Press Any Key To Continue",40)/2,175,40,BLACK);
        DrawText(TextFormat("Score: %i", score),GetScreenWidth()/2 - MeasureText(TextFormat("Score: %i",score), 35)/2, 250,35,BLACK);
        DrawText(TextFormat("High Score: %i", hiScore),GetScreenWidth()/2 - MeasureText(TextFormat("High Score: %i",hiScore), 35)/2, 300,35,BLACK);
        DrawText(TextFormat("Coins: %i", coins),GetScreenWidth()/2 - MeasureText(TextFormat("Coins: %i",coins), 35)/2, 350,35,BLACK);
        drawButton(shopButton);
        drawButton(deathReturn);
    EndDrawing();
}


bool increment = true;

//everything that is relient on screen sizes must be declared here and redelcared in init



void titleScreen(int &frame, int &gameState, bool &quit){
    
    if(increment)frame++;
    if(!increment)frame--;
    if(frame==150)increment = false;
    if(frame==0) increment = true;
    if(buttonPressed(quitButton))quit = true;
    if(buttonPressed(start))gameState = 1;
    if(buttonPressed(settingsButton))gameState = 3;
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawFPS(0,0);
        DrawText(NAME,GetScreenWidth()/2 - MeasureText(NAME,1*(frame/2) + 75)/2,100,1*(frame/2) + 75,BLACK);
        drawButton(start);
        drawButton(settingsButton);
        drawButton(quitButton);
    
    EndDrawing();
}

void settingsMenu(int &gameState){

    if(buttonPressed(settingsReturn)) gameState = 0;
    if(buttonPressed(fullscreenToggleButton)) ToggleFullscreen();
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("SETTINGS", GetScreenWidth()/2 - MeasureText("SETTINGS", 75)/2, 50, 75, BLACK);
        drawButton(settingsReturn);
        drawButton(fullscreenToggleButton);
    EndDrawing();

}
void shopScreen(int &gameState){
    if(buttonPressed(shopReturn))gameState = 2;
    BeginDrawing();
        ClearBackground(RAYWHITE);
        shop.Update();
        drawButton(shopReturn);
    EndDrawing();
}

void Exit(int &hiScore, int&coins){
    if(!DirectoryExists("data"))_mkdir("data");        
    if(SaveFileData(R"(data\score.g)",&hiScore,sizeof(hiScore)))printf("sucsess");
    else printf("failed");
    SaveFileData(R"(data\coins.g)",&coins,sizeof(coins));


}

