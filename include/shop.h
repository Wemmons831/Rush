class Shop{
    public:
        void Update(){
             DrawText("COMING SOON",GetScreenWidth()/2 - MeasureText("COMING SOON",90)/2,GetScreenHeight()/2 - 45,90,BLACK);
            
        }
};
Shop shop;