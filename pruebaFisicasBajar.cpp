#include "C:\raylib\raylib\src\raylib.h"

#define RANCHO 1280
#define RALTO 720
#define ALTURAP 60
#define ANCHOP 50
#define SUELO 650

#define G 0.0981
#define GD 0.35
//blank transparente

int main()
{
    SetTargetFPS(60);  
    InitWindow(RANCHO,RALTO,"juego");
    //Inicializa la posicion
    int xposP=400;  //Posicion incial
    int yposP=0;    //""
    int y0=yposP;   //Posicion inicial para calcular la posicion
    float time=0;     //contador
    int c=0;
    int bsuelo=0;   //bandera de tocar el suelo
    int bplat1=0;   //bandera de tocar plataforma1
    int bplat2=0;   //bandera de tocar plataforma2
    int v0=0;       //velocidad inicial
    int bdown=0;
    int bdownPlat=0;
    while(!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangle(0,SUELO,1280,70,GREEN);
        DrawRectangle(400,400,350,40,GREEN);
        DrawRectangle(200,200,350,40,GREEN);

        time+=1.4;
        

        //caluclar posicion y
        if(!bsuelo) //si no esta en el suelo, calcula la poscion 
        {
            if(bdown)   //Si presionarion abajo // **caida mas rapida**
            {  
                if(++c==1)    
                {
                    if(v0+2*G*time>0) //si esta cayendo 
                    {
                        y0=yposP;   
                        v0=v0+2*G*time; //velocidad inicial igual a velocidad actual
                        time=0;
                    }
                    else  
                    {
                        y0=yposP;   //inicializa caida
                        v0=0;
                        time=0;
                    }
                }
                yposP=y0+v0*time+GD*time*time; //y=y0+v0*t+G*t^2    //caida acelerada
            }
            else
            {
                yposP=y0+v0*time+G*time*time; //y=y0+v0*t+G*t^2     
            }
        }

        //v=v0*2*G*t derivada de la posicion=velocidad
        if(v0+2*G*time>0)   //Si esta cayendo == si la velocidad es menor a 0, en este caso mayor porque esta invertido y
        {
            if(yposP>=SUELO-ALTURAP)    //si la posicion esta por debajo del suelo
            {
                time=0;                 
                yposP=SUELO-ALTURAP;    //ajusta la posicion exacta con el suelo
                y0=yposP;               //la posicion inicial es el suelo
                v0=0;                   //velocidad inicial = 0
                bsuelo=1;               //esta tocando el suelo
                bdownPlat=0;
                c=0;
            }
            else
            {
                if(!bdownPlat)
                {
                    if(xposP<=750)  //Si esta tocando el lado derecho de la plataforma n
                    {
                        if(400<=xposP+ANCHOP)   //si esta tocando el lado izquierdo de la platforma n
                        {
                            if(yposP>=(400-ALTURAP))    //si esta tocando la altura de la plataforma n
                            {
                                //if(yposP<=(405-ALTURAP))  //Si esta dentro de la plataforma n
                                {   
                                    
                                            time=0;
                                            yposP=400-ALTURAP;  //ajusta la posicion sobre la plataforma n
                                            y0=yposP;           //posicion inicial sobfe la plataforma n
                                            v0=0;               //velocidad inicial = 0
                                            bplat1=1;           //esta tocando la plataforma 1
                                            c=0;
                                }
                            }
                        }
                    }
                }
                    
                if(yposP>=(200-ALTURAP))    //lo mismo de arriba para otra plataforma
                {
                    if(yposP<=(205-ALTURAP))   
                    {
                        if(xposP<=550)
                        {
                            if(200<=xposP+ANCHOP)
                            {
                                time=0;
                                yposP=200-ALTURAP;
                                y0=yposP;
                                v0=0;
                                bplat2=1;
                                c=0;
                            }
                        }
                    }
                }
                
                
            }
        }

        

        if(IsKeyPressed(KEY_UP))
        {
            if(bsuelo)      //si esta tocando el suelo
            {
                v0=-11;     //inicializa los valores para el salto
                y0=yposP;
                time=0;     
                bsuelo=0;   //cambia su bandera a 0
                bdown=0;
                c=0;
            }
            else
            {
                if(bplat1)  //bandera de plataforma n
                {
                    v0=-11;     //a
                    y0=yposP;   //inicializa los valores para el salto
                    time=0;
                    bplat1=0;   //cambia la bandera de la plataforma n a 0
                    bdown=0;    
                    c=0;        
                }
                else
                {
                    if(bplat2)  
                    {
                        v0=-11;
                        y0=yposP;
                        time=0;
                        bplat2=0;
                        bdown=0;
                        c=0;
                    }
                }
            }
        }
        else
        {
            if(c==0)    //evita que se mueva raro
            {
                if(IsKeyPressed(KEY_DOWN))  
                {
                    
                    if(!bplat1)
                    {
                        if(!bplat2)
                        {
                            bdown=1;
                        }
                        else
                        {
                            time=0;
                            v0=0;
                            y0=yposP+1;
                            bdownPlat=1;
                            bplat2=0;
                        }
                    }
                    else
                    {
                        time=0;
                        v0=0;
                        y0=yposP;
                        bdownPlat=1;
                        bplat1=0;
                    }
                }

            
            }
        }

        if(IsKeyDown(KEY_RIGHT))
        {
            
            if((xposP+ANCHOP)<1280)    //Si no toca el borde derecho 
            {
                xposP+=3;
            }
            else
            {
                xposP=1280-ANCHOP;  //Si se paso de la pantalla reajusta su posicion
            }
        }
        else
        {
            if(IsKeyDown(KEY_LEFT))
            {
                
                if(xposP>=0)    //Si no toca el borde izquirdo
                {
                    xposP-=3;
                }
                else
                {
                    xposP=0;    //Si se paso de la pantalla reajusta su posicion
                }
            }
        }

        DrawRectangle(xposP,yposP,ANCHOP,ALTURAP,BLUE); //Se muestra el personaje al final para realizar los ajustes primero
    
        EndDrawing();
    }
    CloseWindow();
    return 0;
}