#include "raylib.h"
#include "stdio.h"
class Ball{
    public:
        Vector2 pos = {0,0};
        int rad = 25;
        Color color = BLUE;

        int speed = 720 / 36;
        Vector2 force = {-speed, 0}; //start backwards

        
        void Update(Rectangle paddle, Section top, Section middle,Section bottom, int &score, bool &dead, int &gameState){
            if(CheckCollisionCircleRec(pos,rad,paddle)){
                force.x = speed;
                if(CheckCollisionCircleRec(pos,rad,top.rect))force.y = GetRandomValue(GetScreenHeight()/-96,GetScreenHeight()/-288);
                else if(CheckCollisionCircleRec(pos,rad,middle.rect))force.y = GetRandomValue(GetScreenHeight()/-288,GetScreenHeight()/288);
                else if(CheckCollisionCircleRec(pos,rad,bottom.rect))force.y = GetRandomValue(GetScreenHeight()/288,GetScreenHeight()/96);

                score +=1;
                if(score % 5 == 0)speed += 2;
            }

            if(pos.y < 0 || pos.y > GetScreenHeight()) force.y = force.y * -1;
            if(pos.x > GetScreenWidth())force.x = force.x * -1;
            if(pos.x < -25){ 
                dead = true;
                gameState = 2;
            }

            pos.x += force.x;
            pos.y += force.y;

            DrawCircle(pos.x,pos.y,rad,color);
        }

        void Reset(){
            pos = {GetScreenWidth()/2,GetScreenHeight()/2};
            rad = 25;
            color = BLUE;
            speed = GetScreenHeight()/36;
            force = {-speed, 0};
        }
};

Ball ball;