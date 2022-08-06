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
Button start;
int gameState = 0;
int hiScore;
int frame = 0;
int score = 0;
bool dead;