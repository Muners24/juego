#include "C:\raylib\raylib\src\raylib.h"

#define RANCHO 1280
#define RALTO 720
#define CAMX 360
#define CAMY 640

#define ALTOP 60
#define ANCHOP 50
#define SUELO 650

#define G 0.1
#define GD 0.25

#define VX 3
#define VS -11
//blank transparente

typedef Rectangle Tplat;

typedef Rectangle Tplayer;

/*
typedef struct _jugador
{
    int y;
    int x;
    int y0;
    float v0;
}Tplayer;
*/

float velocidad(float v0,float time);
int ColisionPlat(Tplat player,Tplat plat);

//devuelve 0
int Reposo(float &time,float &v0,int &y0,int y);

int Salto(float &time,float &v0,int &y0,int y);

//y0+v0*time+GD*time*time;
int Posicion(int y0,float v0,float time,int g);

int main()
{
    SetTargetFPS(60);  
    InitWindow(RANCHO,RALTO,"juego");
    
    //Inicializacion Plataformas
    Tplat plat[2];
    plat[0].y=400;
    plat[0].x=400;
    plat[0].width=350;
    plat[0].height=40;

    plat[1].y=200;
    plat[1].x=200;
    plat[1].width=350;
    plat[1].height=40;

    Tplayer player;
    //Inicializa la posicion
    player.x=400;  //Posicion incial
    player.y=SUELO;    //""
    player.height=ALTOP;
    player.width=ANCHOP;

    Camera2D camara = { 0 };
    camara.target = (Vector2){ CAMX, CAMY };
    camara.offset = (Vector2){ CAMX, CAMY };
    camara.rotation = 0.0f;
    camara.zoom = 1.0f;

    int y0=player.y;    //velocidad inicial  
    float v0=0;        //Posicion inicial para calcular la posicion
    int y0Cam;

    float time=0;     //contador
    int c=0;
    int igncolision=0;
    int bsuelo=0;   //bandera de tocar el suelo
    int bplat1=0;   //bandera de tocar plataforma1
    int bplat2=0;   //bandera de tocar plataforma2
    int bdown=0;    //bandera de presionar abajo

    while(!WindowShouldClose())
    {

        

        time+=1.3;
        igncolision++;

        //caluclar posicion y
        if(!bsuelo) //si no esta en el suelo, calcula la poscion 
        {
            if(bdown)   //Si presionarion abajo // **caida mas rapida**
            {  
                if(++c==1)    //solo inicializa 1 vez
                {
                    if(velocidad(v0,time)>0) //si esta cayendo 
                    {
                        v0=velocidad(v0,time); //velocidad inicial igual a velocidad actual
                        y0=player.y; 
                        time=1.3;
                    }
                    else  
                    {
                        Reposo(time,v0,y0,player.y); //inicializa caida
                    }
                }

                if(player.y<30)
                {
                    camara.target.y=Posicion(y0-30,v0,time*0.2,bdown)+CAMY; //y=y0+v0*t+G*t^2 
                }
                else 
                {
                    camara.target.y=CAMY;
                }

                player.y=Posicion(y0,v0,time,bdown); //y=y0+v0*t+G*t^2    //caida acelerada
            }
            else    //caida normal
            { 
                if(player.y<30)
                {
                    y0Cam=y0;
                    camara.target.y=Posicion(y0Cam,-11.5,time,bdown)+CAMY; 
                }
                else 
                {
                    camara.target.y=CAMY;
                }
                player.y=Posicion(y0,v0,time,bdown); //y=y0+v0*t+G*t^2   
            }
        }

        //v=v0*2*G*t derivada de la posicion=velocidad
        if(velocidad(v0,time)>0)   //Si esta cayendo == si la velocidad es menor a 0, en este caso mayor porque esta invertido y
        {
            if(player.y>=SUELO-ALTOP)    //si la posicion esta por debajo del suelo
            {
                player.y=SUELO-ALTOP;    //ajusta la posicion exacta con el suelo
                bsuelo=!Reposo(time,v0,y0,player.y);
            }
            else
            {
                if(igncolision>16) //ignora colisiones hasta bajar de la plataforma
                {
                    if(ColisionPlat(player,plat[0]))  //Si esta tocando el lado derecho de la plataforma n
                    {
                
                        player.y=plat[0].y-ALTOP;  //ajusta la posicion sobre la plataforma n
                        bplat1=!Reposo(time,v0,y0,player.y);
                        bdown=0;
                        c=0;                //habilita bajar de plataforma
                    }
                        
                        
                    if(ColisionPlat(player,plat[1]))    //lo mismo de arriba para otra plataforma
                    {
                        
                        player.y=plat[1].y-ALTOP;  //ajusta la posicion sobre la plataforma n
                        bdown=0;
                        bplat2=!Reposo(time,v0,y0,player.y);           //esta tocando la plataforma 1
                        c=0;                //habilita bajar de plataforma
                    }
                }
            }
        }

        if(IsKeyPressed(KEY_UP))
        {
            if(bsuelo)      //esta tocando el suelo
            {
                bsuelo=Salto(time,v0,y0,player.y);    
                bdown=0;
                c=0;  
            }
            else
            {
                if(bplat1)  //bandera de plataforma n
                {
                    bplat1=Salto(time,v0,y0,player.y);   
                    bdown=0;
                    c=0;   
                }
                else
                {
                    if(bplat2)  
                    {
                        bplat2=Salto(time,v0,y0,player.y); 
                        bdown=0;
                        c=0;  
                    }
                }
            }
        }
        else
        {
            if(c<10)    //Solo permite dar abajo 1 vez
            {
                if(IsKeyPressed(KEY_DOWN))  
                {
                    
                    if(!bplat1) 
                    {
                        if(!bplat2)
                        {
                            bdown=1;    //bandera de bajar rapido
                        }
                        else
                        {
                            bplat2=Reposo(time,v0,y0,player.y); //inicializa caida
                            igncolision=0;
                            bdown=0;        //evita que caiga rapido de la plataforma  
                        }
                    }
                    else
                    {
                        bplat1=Reposo(time,v0,y0,player.y);
                        igncolision=0;
                        bdown=0;
                    }
                }
            }
        }

        if(IsKeyDown(KEY_RIGHT))
        {
            
            if((player.x+ANCHOP)<1280)    //Si no toca el borde derecho 
            {
                player.x+=VX;
            }
            else
            {
                player.x=1280-ANCHOP;  //Si se paso de la pantalla reajusta su posicion
            }
        }
        else
        {
            if(IsKeyDown(KEY_LEFT))
            {
                
                if(player.x>=0)    //Si no toca el borde izquirdo
                {
                    player.x-=VX;
                }
                else
                {
                    player.x=0;    //Si se paso de la pantalla reajusta su posicion
                }
            }
        }
        //EndMode2D();
        
        
        BeginDrawing();
            BeginMode2D(camara);
            ClearBackground(BLACK);
            DrawRectangle(0,SUELO,1280,70,GREEN);
            DrawRectangleRec(plat[0],GREEN);
            DrawRectangleRec(plat[1],GREEN);
            DrawRectangle(player.x,player.y,ANCHOP,ALTOP,BLUE);
            EndMode2D();
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}

float velocidad(float v0,float time)
{
    return (v0+2*G*time);
}

int ColisionPlat(Tplat player,Tplat plat)
{
    if(player.x<=plat.x+plat.width)  //Si esta tocando el lado derecho de la plataforma n
    {
        if(plat.x<=player.x+ANCHOP)   //si esta tocando el lado izquierdo de la platforma n
        {
            if(player.y+player.height<=(plat.y+30))
            {
                if(player.y+player.height>=plat.y)
                { 
                    return 1;
                }
            }            
       }
    }
    return 0;                   
}

int Reposo(float &time,float &v0,int &y0,int y)
{  
    time=0;         
    v0=0;
    y0=y;
    return 0;
}

int Salto(float &time,float &v0,int &y0,int y)
{  
    time=0;  
    y0=y;
    v0=VS;     
    return 0;
}

int Posicion(int y0,float v0,float time,int g)
{
    if(g)
    {
        return (y0+v0*time+GD*time*time);
    }
    else
    {
        return (y0+v0*time+G*time*time);
    }
}