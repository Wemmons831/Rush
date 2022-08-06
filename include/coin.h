#include "raylib.h"

class Coin{
    public:
        int rad = 20;
        Vector2 pos; 

        void Update(int &coins, Vector2 ballPos, int ballRad){
            DrawCircle(pos.x,pos.y,rad,YELLOW);

            if(CheckCollisionCircles(pos,rad,ballPos,ballRad)){
                coins++;
                pos = {GetRandomValue(50 + rad,GetScreenWidth()-rad),GetRandomValue(rad, GetScreenHeight()-rad )};
            }

        }


};
Coin coin;