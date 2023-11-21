

#include "raylib.h"

    //Texture2D sub=LoadTexture("texturas\\SUB.png");
    //Texture2D nave=LoadTexture("texturas\\navepix2.png");
    //Texture2D car=LoadTexture("texturas\\pixel_car2.png");
    

    //DrawTexture(sub, 190, 200,WHITE);
    //DrawTexture(nave, 500,300,WHITE);
    //DrawTexture(car, 800,300,WHITE);

#define JUGAR 0
#define OPCIONES 1
#define SALIR 2

#define DIFICULTAD 0
#define SONIDO 1
#define REGRESAR 2

int mainMenu(void);
int opMenu(void);

int main(void)
{
    int op;
    int subOp;

    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "window");
    SetTargetFPS(60);        
    
    Texture2D car=LoadTexture("texturas\\pixel_car2.png");
    Texture2D car2=LoadTexture("texturas\\pixel_car.png");
    Texture2D sub=LoadTexture("texturas\\SUB.png");

    while (!WindowShouldClose()) 
    {
       
        //if(!IsWindowFullscreen())
        //{
        //    ToggleFullscreen();
        //}
        Texture2D fondo=LoadTexture("texturas\\menuok.png");
        
        do
        {
            inicio:
                BeginDrawing();
                DrawTexture(fondo,0,0,WHITE);

                op=mainMenu();

                EndDrawing();
        }while(op==-1);
        
        

        switch(op)
        {
            case OPCIONES:
                
                do
                {
                    BeginDrawing();
                    DrawTexture(fondo,0,0,WHITE);
                    subOp=opMenu();
                    EndDrawing();
                }while(subOp!=2);

                goto inicio;
                break;

            case SALIR:
                
                CloseWindow();
                break;
        }
        //Original
        //DrawText("Mecánico Aritmético",400,70,50,WHITE);
        //DrawText("Jugar",510,200,40,WHITE);
        //DrawText("Opciones",510,300,40,WHITE);
        //DrawText("Salir",510,400,40,WHITE);
        
    }
    CloseWindow();       

    return 0;
}

int mainMenu(void)
{
    
    static int op=0;

    if(IsKeyPressed(KEY_UP))
    {
        switch(op)
        {
            case OPCIONES:
                op=JUGAR;
                break;
            case SALIR:
                op=OPCIONES;
                break;
        }
    }
    else
    {
        if(IsKeyPressed(KEY_DOWN))
        {
            switch(op)
            {
                case JUGAR:
                    op=OPCIONES;
                    break;
                case OPCIONES:
                    op=SALIR;
                    break;
            }
        }
    }

    switch(op)
    {
        case JUGAR:
            DrawText("Mecánico Aritmético",265,65,70,WHITE);
            DrawText("Jugar",510,200,60,WHITE);
            DrawText("Opciones",510,300,40,WHITE);
            DrawText("Salir",510,400,40,WHITE);
            break;
        case OPCIONES:
            DrawText("Mecánico Aritmético",265,65,70,WHITE);
            DrawText("Jugar",510,200,40,WHITE);
            DrawText("Opciones",510,300,60,WHITE);
            DrawText("Salir",510,400,40,WHITE);
            break;
        case SALIR:
            DrawText("Mecánico Aritmético",265,65,70,WHITE);
            DrawText("Jugar",510,200,40,WHITE);
            DrawText("Opciones",510,300,40,WHITE);
            DrawText("Salir",510,400,60,WHITE);
            break;
    }

    if(IsKeyPressed(KEY_ENTER))
    {
        return op;
    }

    return -1;
}

int opMenu(void)
{
    static int op=0;

    if(IsKeyPressed(KEY_UP))
    {
        switch(op)
        {
            case SONIDO:
                op=DIFICULTAD;
                break;
            case REGRESAR:
                op=SONIDO;
                break;
        }
    }
    else
    {
        if(IsKeyPressed(KEY_DOWN))
        {
            switch(op)
            {
                case DIFICULTAD:
                    op=SONIDO;
                    break;
                case SONIDO:
                    op=REGRESAR;
                    break;
            }
        }
    }

    switch(op)
    {
        case JUGAR:
            DrawText("Opciones",450,65,70,WHITE);
            DrawText("Dificultad",510,200,60,WHITE);
            DrawText("Sonido",510,350,40,WHITE);
            DrawText("Regresar",510,500,40,WHITE);
            break;
        case OPCIONES:
            DrawText("Opciones",450,65,70,WHITE);
            DrawText("Dificultad",510,200,40,WHITE);
            DrawText("Sonido",510,350,60,WHITE);
            DrawText("Regresar",510,500,40,WHITE);
            break;
        case SALIR:
            DrawText("Opciones",450,65,70,WHITE);
            DrawText("Dificultad",510,200,40,WHITE);
            DrawText("Sonido",510,350,40,WHITE);
            DrawText("Regresar",510,500,60,WHITE);
            break;
    }

    if(IsKeyPressed(KEY_ENTER))
    {
        return op;
    }

    return -1;
}