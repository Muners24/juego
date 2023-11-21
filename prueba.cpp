

#include "raylib.h"

    //Texture2D sub=LoadTexture("texturas\\SUB.png");
    //Texture2D nave=LoadTexture("texturas\\navepix2.png");
    //Texture2D car=LoadTexture("texturas\\pixel_car.png");
    

    //DrawTexture(sub, 190, 200,WHITE);
    //DrawTexture(nave, 500,300,WHITE);
    //DrawTexture(car, 800,300,WHITE);

#define JUGAR 0
#define OPCIONES 1
#define SALIR 2

int main(void)
{
    int optionmenu=0;
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "window");
    SetTargetFPS(60);        
    
    Texture2D menu=LoadTexture("texturas\\menuok.png");

    if(IsKeyUp)
    {
        switch(optionmenu)
        {
            case JUGAR:
                optionmenu=JUGAR;
                break;
            case OPCIONES:
                optionmenu=JUGAR;
                break;
            case SALIR:
                optionmenu=OPCIONES;
                break;

        }
    }
    else
    {
        if(IsKeyDown)
        {
            switch(optionmenu)
            {
                case JUGAR:
                    optionmenu=OPCIONES;
                    break;

            }
        }
    }
    while (!WindowShouldClose()) 
    {
       
        BeginDrawing();

            DrawTexture(menu,0,0,WHITE);

            
            //Original
            //DrawText("Mecánico Aritmético",400,70,50,WHITE);
            //DrawText("Jugar",510,200,40,WHITE);
            //DrawText("Opciones",510,300,40,WHITE);
            //DrawText("Salir",510,400,40,WHITE);
        
            
            DrawText("Mecánico Aritmético",400,70,50,WHITE);
            DrawText("Jugar",510,200,40,WHITE);
            DrawText("Opciones",510,300,40,WHITE);
            DrawText("Salir",510,400,40,WHITE);
            
        EndDrawing();
    }
    CloseWindow();       

    return 0;
}