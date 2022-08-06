#include "raylib.h"
#include "vector"
#include"cmath"
struct Section
{
    Rectangle rect;
    Color color;
};


class Paddle
{
    public:
    
    int size = 250;
    int posistion = 100;
    Color color = WHITE;
    float speed = GetScreenHeight()/72;
    
    Rectangle rect = {50, posistion, 50, size};
    Section top = {{50, posistion, 50, size/3}, GREEN};
    Section middle = {{50, posistion, 50, size/3 + size/3}, WHITE};
    Section bottom = {{50, posistion, 50, size/3 +  (2 * size/3)}, RED};
    
    void sectionUpdate(Section &section, int order){
        section.rect.height = size/3;
        section.rect.y = posistion + (size/3 * order) ;
    }


    void Update(){

        // Update position
        if(IsKeyDown(KEY_DOWN) && posistion < GetScreenHeight() - 250 + 166){posistion += speed; printf("hit \n");}
        if(IsKeyDown(KEY_UP) && posistion > 0 - 166 )posistion -= speed;

        // Update rectangle
        rect.height = size;
        rect.y = posistion;

        sectionUpdate(top,0);
        sectionUpdate(middle,1);
        sectionUpdate(bottom,2);
        
        DrawRectangleRec(top.rect,top.color);
        DrawRectangleRec(middle.rect,middle.color);
        DrawRectangleRec(bottom.rect,bottom.color);

        

    }

    void Reset(){
        posistion = GetScreenHeight()/2 - 125;
        speed = GetScreenHeight()/72;
        size = 250;
        color = WHITE;
        speed = 10;
        rect = {50, posistion, 50, size};
        
    }
};

Paddle paddle;