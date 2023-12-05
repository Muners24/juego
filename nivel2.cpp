#include "C:\raylib\raylib\src\raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANCHO 1280
#define RALTO 720
#define CAMY 360
#define CAMX 640

#define ALTOP 60
#define ANCHOP 50
#define SUELO 650

#define G 0.1
#define GD 0.2

#define VX 3
#define VS -11
#define VD 10

#define MAXAVE 5
#define MAXEGG 8
#define MAXCAR 2
//blank transparente

typedef Rectangle Tplat;

//typedef Rectangle Tplayer;

typedef Rectangle Thit;

typedef Rectangle Trec;

typedef struct _jugador
{
    Trec pos;
    int y0;
    float v0;
    int timeDash;
}Tplayer;

typedef struct _enemigo
{
    Trec pos;
    int status=0;
    int right=0;
    int left=0;

}Tave;

typedef struct _huevo
{
    Trec pos;
    int status;
    int y0;
    int time;
}Tegg;

typedef struct _carro
{
    Trec pos;
    int status;
}Tcar;

float velocidad(float v0,float time);
int ColisionPlat(Tplayer player,Tplat plat);
//devuelve 0
int Reposo(float &time,float &v0,int &y0,int y);

int Salto(float &time,float &v0,int &y0,int y);

//y0+v0*time+GD*time*time;
int Posicion(int y0,float v0,float time,int g);

void CalculaPosEnemigo(Tave &mob);
void CheckMobColision(Tave &mob,Thit hit);

void DropEgg(Tave mob,Tegg &egg);

int main()
{
    SetTargetFPS(60);  
    InitWindow(RANCHO,RALTO,"juego");
    unsigned int seed = static_cast<unsigned int>(time(NULL));
    SetRandomSeed(seed);
    srand(time(NULL));
    int j;
    //int y0=player.pos.y;    //velocidad inicial  
    //float v0=0;        //Posicion inicial para calcular la posicion
    int y0Cam;

    int frameC=0;
    float time=0;     //contador
    int c=0;
    int igncolision=0;
    int hitc=0;
    
    //int caminarc=0;

    int bsuelo=0;   //bandera de tocar el suelo
    int bplat1=0;   //bandera de tocar plataforma1
    int bplat2=0;   //bandera de tocar plataforma2
    int bdown=0;    //bandera de presionar abajo
    //int caminar=0;
    int lookR=1;
    int lookL=0;
    int hit=0;
    int dash=0;
    
    int random;

    //Inicializacion ***************************************************************************************
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
    player.pos.x=400;  //Posicion incial
    player.pos.y=SUELO;    //""
    player.pos.height=ALTOP;
    player.pos.width=ANCHOP;
    player.y0=player.pos.y;
    player.v0=0;
    player.timeDash=70;

    Tave ave[MAXAVE];
    for(j=0;j<MAXAVE;j++)
    {
        ave[j].status=0;
        ave[j].right=0;
        ave[j].left=0;
        ave[j].pos.x=2000;
        ave[j].pos.y=800;
        ave[j].pos.height=20;
        ave[j].pos.width=40;
    }

    Tegg egg[MAXEGG];
    for(j=0;j<MAXEGG;j++)
    {
        egg[j].status=0;
        egg[j].pos.height=30;
        egg[j].pos.width=20;
        egg[j].pos.x=0;
        egg[j].pos.y=800;
    }
    Tcar car[MAXCAR];
    Thit hithit;
    hithit.width=90;
    hithit.height=ALTOP+30;
    Camera2D camara = { 0 };
    camara.target.x=player.pos.x+30;
    camara.target.y=player.pos.y;
    camara.offset.x=640;
    camara.offset.y=CAMY;
    camara.rotation = 0;
    camara.zoom = 1;
    while(!WindowShouldClose())
    {
        time+=1;
        igncolision++;
        frameC++;
        player.timeDash++;
        //** enemigo1 ********************************************************************************************************************************
        for(j=0;j<MAXAVE;j++)
        {
            //comportameinto
            if(ave[j].status)
            {           
                //movimiento enemigo **si sale de la pantalla se elimina**
                if(ave[j].right)
                {
                    ave[j].pos.x-=6;
                    if(ave[j].pos.x<=player.pos.x-750-ave[j].pos.width)
                    {
                        ave[j].status=0;
                    }
                }
                else
                {
                    if(ave[j].left)
                    {
                        ave[j].pos.x+=6;
                        if(ave[j].pos.x>=player.pos.x+750)
                        {
                            ave[j].status=0;
                        }
                    }
                }

                //ataque enemigo ***********************************************************************************
                random=GetRandomValue(1,10);
                if(random==1)
                    if(ave[j].pos.x<=player.pos.x+player.pos.width+200)
                    {
                        if(ave[j].pos.x>=player.pos.x-200)
                        {
                            random=rand()%MAXEGG;
                            //reajusta la posicion para lanzar un huevo si no esta activo el huevo
                            DropEgg(ave[j],egg[random]);
                        }
                    }
                //Colision con golpe
                if(hit)
                {
                    CheckMobColision(ave[j],hithit);
                }

            }
            else
            {
                //generacion
                random=GetRandomValue(1,100);
                if(random==1)
                {
                    ave[j].right=rand()%2;
                    if(ave[j].right)
                    {   ave[j].status=1;
                        ave[j].pos.x=player.pos.x+610+player.pos.width;
                        ave[j].pos.y=(rand()%101)+1;
                        ave[j].left=0;
                    }
                    else
                    {
                        ave[j].status=1;
                        ave[j].pos.x=player.pos.x-610;
                        ave[j].pos.y=(rand()%101)+1;
                        ave[j].left=1;
                    }
                }
            }
        }
       
        //** comportamiento huevo ********************************************************************************************************************************
        for(j=0;j<MAXEGG;j++)
        { 
            //elinacion de huevo
            if(egg[j].pos.y-egg[j].pos.height>=SUELO)
            {
                egg[j].status=0;
                egg[j].pos.y=800;
            }
            //caida de huevo
            if(egg[j].status)
            {
                egg[j].time+=1;
                egg[j].pos.y=Posicion(egg[j].y0,0,egg[j].time,0);
            }

        }
        
        //** caluclar posicion y ********************************************************************************************************************************
        if(!bsuelo) //si no esta en el suelo, calcula la poscion 
        {
            if(!dash)
            {
                if(bdown)   //Si presionarion abajo // **caida mas rapida**
                {  
                    if(++c==1)    //solo inicializa 1 vez
                    {
                        if(velocidad(player.v0,time)>0) //si esta cayendo 
                        {
                            player.v0=velocidad(player.v0,time); //velocidad inicial igual a velocidad actual
                            player.y0=player.pos.y; 
                            time=1;
                        }
                        else  
                        {
                            Reposo(time,player.v0,player.y0,player.pos.y); //inicializa caida
                        }
                    }

                    if(player.pos.y<30)
                    {
                        camara.target.y=Posicion(player.y0-30,player.v0,time*1.02,bdown)+CAMY; //y=y0+v0*t+G*t^2 
                    }
                    else 
                    {
                        camara.target.y=CAMY;
                    }

                    player.pos.y=Posicion(player.y0,player.v0,time,bdown); //y=y0+v0*t+G*t^2    //caida acelerada
                }
                else    //caida normal
                { 
                    if(player.pos.y<30)
                    {
                        y0Cam=player.y0;
                        camara.target.y=Posicion(y0Cam,-11.5,time,bdown)+CAMY; 
                    }
                    else 
                    {
                        camara.target.y=CAMY;
                    }
                    player.pos.y=Posicion(player.y0,player.v0,time,bdown); //y=y0+v0*t+G*t^2   
                }
            }
        }

        //** caida ********************************************************************************************************************************
        //v=v0*2*G*t derivada de la posicion=velocidad
        if(velocidad(player.v0,time)>0)   //Si esta cayendo == si la velocidad es menor a 0, en este caso mayor porque esta invertido y
        {
            if(player.pos.y>=SUELO-ALTOP)    //si la posicion esta por debajo del suelo
            {
                player.pos.y=SUELO-ALTOP;    //ajusta la posicion exacta con el suelo
                bsuelo=!Reposo(time,player.v0,player.y0,player.pos.y);
            }
            else
            {
                if(igncolision>20) //ignora colisiones hasta bajar de la plataforma
                {
                    if(ColisionPlat(player,plat[0]))  //Si esta tocando el lado derecho de la plataforma n
                    {
                
                        player.pos.y=plat[0].y-ALTOP;  //ajusta la posicion sobre la plataforma n
                        bplat1=!Reposo(time,player.v0,player.y0,player.pos.y);
                        bdown=0;
                        c=0;                //habilita bajar de plataforma
                    }
                        
                        
                    if(ColisionPlat(player,plat[1]))    //lo mismo de arriba para otra plataforma
                    {
                        
                        player.pos.y=plat[1].y-ALTOP;  //ajusta la posicion sobre la plataforma n
                        bdown=0;
                        bplat2=!Reposo(time,player.v0,player.y0,player.pos.y);           //esta tocando la plataforma 1
                        c=0;                //habilita bajar de plataforma
                    }
                }
            }
        }
        
        //** golpe ********************************************************************************************************************************
        if(hit)
        {
            if(lookR)
            {
                hithit.x=player.pos.x+ANCHOP-20;
                hithit.y=player.pos.y-20;
            }
            else
            {
                if(lookL)
                {
                    hithit.x=player.pos.x-60;
                    hithit.y=player.pos.y-20;
                }
            }
            if(hitc<50)
            {
                hitc++;
            }
            else
            {
                hitc=0;
                hit=0;
            }
        }
        
        //** dash ********************************************************************************************************************************
        if(dash)
        {   
            if(player.timeDash<20)
            {
                if(lookR)
                {
                    player.pos.x+=VD;
                }
                else
                {
                    if(lookL)
                    {
                        player.pos.x-=VD;
                    }
                }
            }
            else
            {
                dash=Reposo(time,player.v0,player.y0,player.pos.y);
            }
        }

        //** camara ********************************************************************************************************************************
        camara.target.y=player.pos.y;
        if(player.pos.y>100)
        {
            camara.target.y=CAMY;
            camara.offset.y=CAMY;
            camara.target.x=player.pos.x+25;
        }
        else
        {
            camara.offset.y=RANCHO/12.5;
            camara.target.x=player.pos.x+25;
        }
       
        //** intput ********************************************************************************************************************************
        if(IsKeyPressed(KEY_UP))
        {
            if(bsuelo)      //esta tocando el suelo
            {
                bsuelo=Salto(time,player.v0,player.y0,player.pos.y);    
                bdown=0;
                c=0;  
            }
            else
            {
                if(bplat1)  //bandera de plataforma n
                {
                    bplat1=Salto(time,player.v0,player.y0,player.pos.y);   
                    bdown=0;
                    c=0;   
                }
                else
                {
                    if(bplat2)  
                    {
                        bplat2=Salto(time,player.v0,player.y0,player.pos.y); 
                        bdown=0;
                        c=0;  
                    }
                    else
                    {
                        if(igncolision<1000)
                        {
                            Salto(time,player.v0,player.y0,player.pos.y); 
                            bdown=0;
                            c=0; 
                            igncolision=1000;
                        }
                    }
                }
            }
            
        }
        else
        {
            if(c<20)    //Solo permite dar abajo 1 vez
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
                            bplat2=Reposo(time,player.v0,player.y0,player.pos.y); //inicializa caida
                            igncolision=0;
                            bdown=0;        //evita que caiga rapido de la plataforma  
                        }
                    }
                    else
                    {
                        bplat1=Reposo(time,player.v0,player.y0,player.pos.y);
                        igncolision=0;
                        bdown=0;
                    }
                }
            }
        }

        if(!dash)
        {
            if(IsKeyDown(KEY_RIGHT))
            {
                //if((player.pos.x+ANCHOP)<1280)    //Si no toca el borde derecho 
                //{
                    player.pos.x+=VX;
                    //caminar=1;
                    lookR=1;
                    lookL=0;
                //}
                //else
                //{
                    //player.pos.x=1280-ANCHOP;  //Si se paso de la pantalla reajusta su posicion
                //}
            }
            else
            {
                if(IsKeyDown(KEY_LEFT))
                {
                    //if(player.pos.x>=0)    //Si no toca el borde izquirdo
                //    {
                        player.pos.x-=VX;
                        //caminar=1;
                        lookL=1;
                        lookR=0;
                //   }
                //    else
                //    {
                
                //    }
                }
            }
        }
        
        
        if(IsKeyPressed(KEY_X))
        {
            hit=1;
            dash=0;
        }    

        if(player.timeDash>80)
        {
            if(!dash)
            {
                if(IsKeyPressed(KEY_C))
                {
                    dash=1;
                    player.timeDash=Reposo(time,player.v0,player.y0,player.pos.y);
                    bplat1=1;
                }
            }
        }

            /*
            if(caminar)
            {
                caminarc++;
                if(caminarc<30)
                {
                    DrawRectangle(player.pos.x,player.pos.y,ANCHOP,ALTOP,RED);
                }
                else
                {
                    if(caminarc<60)
                    {
                        DrawRectangle(player.pos.x,player.pos.y,ANCHOP,ALTOP,GREEN);
                    }
                    else
                    {
                        if(caminarc<90)
                        {
                            DrawRectangle(player.pos.x,player.pos.y,ANCHOP,ALTOP,YELLOW);
                        }
                        else
                        {
                            if(caminarc<120)
                            {
                                DrawRectangle(player.pos.x,player.pos.y,ANCHOP,ALTOP,ORANGE);
                            }
                        }
                    }
                }
                if(caminarc==120)
                {
                    caminarc=0;
                }
                caminar=0;
            }
            else
            {
                */
            //    caminarc=0;
        BeginDrawing();
            BeginMode2D(camara);
            ClearBackground(DARKBLUE);

            DrawRectangleRec(player.pos,BLUE);      
            //suelo    
            DrawRectangle(player.pos.x-640,SUELO,1350,70,DARKGREEN);
            //plataformas
            DrawRectangleRec(plat[0],DARKGREEN);
            DrawRectangleRec(plat[1],DARKGREEN);
            for(j=0;j<MAXAVE;j++)
            {
                if(ave[j].status)
                {
                    DrawRectangleRec(ave[j].pos,BLACK);
                }
            }
            for(j=0;j<MAXEGG;j++)
            {
                if(egg[j].status)
                {
                    DrawRectangleRec(egg[j].pos,YELLOW);
                }
            }
            if(hit)
            {
                DrawRectangleRec(hithit,RED);
            }
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

int ColisionPlat(Tplayer player,Tplat plat)
{
    if(player.pos.x<=plat.x+plat.width)  //Si esta tocando el lado derecho de la plataforma n
    {
        if(plat.x<=player.pos.x+ANCHOP)   //si esta tocando el lado izquierdo de la platforma n
        {
            if(player.pos.y+player.pos.height<=(plat.y+30))
            {
                if(player.pos.y+player.pos.height>=plat.y)
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
    return (y0+v0*time+(g ? GD : G)*time*time);
}

void CalculaPosEnemigo(Tave &mob)
{
    if(mob.right)
    {
        mob.pos.x-=6;
    }
    else
    {
        if(mob.left)
        {
            mob.pos.x+=6;
        }
    }
}

void CheckMobColision(Tave &mob,Thit hit)
{
    if(mob.pos.x<=hit.x+hit.width)
    {
        if(mob.pos.x>=hit.x)
        {
            if(mob.pos.y>=hit.y)
            {
                if(mob.pos.y<=hit.y+hit.height)
                {
                    mob.status=0;
                }
            }
        }
    }
}

void DropEgg(Tave mob,Tegg &egg)
{
    if(!egg.status)
    {
        egg.time=0;         
        egg.y0=mob.pos.y;
        egg.pos.y=mob.pos.y;
        egg.pos.x=mob.pos.x+14;
        egg.status=1;
    }
}