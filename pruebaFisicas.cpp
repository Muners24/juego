
#include "C:\raylib\raylib\src\raylib.h"
#include <math.h>
#include <stdlib.h>

#define RANCHO 1280
#define RALTO 720
#define ALTURAP 60
#define ANCHOP 50
#define SUELO 650

//blank transparente

int main()
{
    SetTargetFPS(60);  
    InitWindow(RANCHO,RALTO,"juego");
    //posicion inicial
    int xposP=600;
    int yposP=SUELO-ALTURAP;
    int frameCount=0;
    int saltoFlag=0;
    int saltoTime=0;

    while(!WindowShouldClose())
    {

        BeginDrawing;
        ClearBackground(WHITE);
        DrawRectangle(0,SUELO,1280,70,GREEN);
        DrawRectangle(xposP,yposP,ANCHOP,ALTURAP,BLUE);
        int y0;
        frameCount++;

        if(IsKeyDown(KEY_RIGHT))
        {
            //Si no topa el borde derecho
            if((xposP+ANCHOP)!=1280)
            {
                xposP+=3;
            }
        }
        else
        {
            if(IsKeyDown(KEY_LEFT))
            {
                //Si no topa el borde izquirdo
                if(xposP!=0)
                {
                    xposP-=3;
                }
            }
        }

        if(IsKeyPressed(KEY_UP))
        {
            saltoTime=0;
            saltoFlag=1;    
            y0=yposP;
        }
        
        if(saltoFlag)
        {  
            saltoTime++;    

            yposP=(pow((saltoTime),2))*0.7407/20-saltoTime*6.66666+y0;
            if(saltoTime==180)
            {
                saltoFlag=0;
                yposP=y0;
                //free(&y0);
            }
            else
            {
                if((yposP-ALTURAP)==SUELO)
                {
                    saltoFlag=0;
                    yposP=y0;
                    //free(&y0);
                }
            }
        }

        
        if(frameCount=600)
        {
            frameCount=0;
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}