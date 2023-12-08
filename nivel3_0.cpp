#include "C:\raylib\raylib\src\raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define RANCHO 1280
#define RALTO 720
#define CAMY 360
#define CAMX 640

#define ALTOP 60
#define ANCHOP 50
#define SUELO 650

#define G 0.1
#define GD 0.15

#define VX 3
#define VS -11
#define VSJ -4
#define VY -15
#define VD 6

//lvl3
#define RECVEHICULO 900

#define MAXTORRE 2
#define TORREASPEED 180
#define TORREVPROYECTIL 10
#define MAXHITTORRE 3

#define MAXAVE 5
#define AVESPEED 7
#define MAXEGG 8
#define MAXCAR 2
#define CARSPEED 9

#define MAXPLAT 4
#define MAXHIT 500
#define VATAQUE 40
#define VATAQUEBUFF 15
#define VPROYECTIL 10.0
//blank transparente

//typedef Rectangle Tplayer;


typedef Rectangle Trec;

typedef struct _velocidad
{
    float vx;
    float vy;
}Tvel;

typedef struct _hit
{
    Trec pos;
    int time;                               //7   0    1
    int status;                             //
    int direccion;//--------------------->  //6   p    2
    Tvel v;                                 //  
}Thit;                                      //5   4    3

typedef struct _plataforma
{
    Trec pos;
    int status;
    int flag;
}Tplat;

typedef struct _vehiculo
{
    Trec pos;
    int status;
}Tpart;

typedef struct _jugador
{
    Trec pos;
    int y0;
    float v0;
    int timeDash;
    int jump;
    int jumpjump;
    int fall;
    int jet;
    int jetc;
    int x0;
    int AtkC;
}Tplayer;

typedef struct _ave
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

typedef struct _car
{
    Trec pos;
    int status;
    int movimiento;
    int time;
}Tcar;

typedef struct _tower
{
    Trec pos;
    int status;
    int direccion;
    int atkC;
    Thit hit[MAXHITTORRE];
}Ttow;

float velocidad(float v0,float time);
int ColisionPlat(Tplayer player,Tplat plat);
//devuelve 0
int Reposo(float &time,float &v0,int &y0,int y);

int Salto(float &time,float &v0,int &y0,int y);

//y0+v0*time+GD*time*time;
int Posicion(int y0,float v0,float time,int g);

void CalculaPosEnemigo(Tave &mob);
int CheckMobColision(Trec mob,Trec hit);
int CheckPlayerColision(Trec player,Trec mob);
//int CheckPiezaColision(Trec player,Trec mob); // duplicado para probar sin daño
void DropEgg(Tave mob,Tegg &egg);
void LimpiaEnemigos(Ttow torre[]);
int JetPack(float &time,float &v0,int &y0,int y,int bdown);
void InicializaProyectil(int L,int R,int Up,int Down,Tplayer player,Thit &hit);
void CalculaComponentesVelocidad(float velocidad,float grados,Tvel &v);
float Radianes(float grados);
void PosicionObieto(float vx,float vy,Trec &pos);
void Direccioniugador(int &L,int &R,int &Up,int &Down,Tplayer player);
float CalculaAngulo(Trec ang,Trec player);

int main()
{
    SetTargetFPS(60);  
    InitWindow(RANCHO,RALTO,"juego");
    srand(time(NULL));
    int j,i;
    int y0Cam;

    //contadores
    int frameC=0;
    float time=0;     
    int c=0;
    int igncolision=0;
    int hitc=0;
    int platc=0;
    //int caminarc=0;

    //banderas
    int bsuelo=0;   
    int bdown=0;    
    //int caminar=0;
    int lookR=1;
    int lookL=0;
    int lookUp=0;
    int lookDown=0;
    int dash=0;
    
    //auxiliar
    int random;
    Trec aux;
    float grados;

    //Inicializacion ***************************************************************************************
    //Inicializacion Plataformas
    Tplat plat[MAXPLAT];
    for(i=0;i<MAXPLAT;i++)
    {
        plat[i].pos.height=30;
        plat[i].pos.width=300;
        plat[i].status=1;
        plat[i].flag=0;
    }
    plat[0].pos.x=RANCHO-plat[1].pos.width-300;
    plat[0].pos.y=450;
    plat[1].pos.x=100;
    plat[1].pos.y=250;
    plat[2].pos.x=800;
    plat[2].pos.y=-50;
    plat[3].pos.x=250;
    plat[3].pos.y=-400;
    
    //** piezas **********************************************************************************************************************************
    Tpart pieza[3];
    
    for(j=0;j<3;j++)
    {
        pieza[j].status=1;
        pieza[j].pos.height=80;
        pieza[j].pos.width=50;
        pieza[j].pos.x=plat[j+1].pos.x+plat[j+1].pos.width/2-pieza[j].pos.width/2;
        pieza[j].pos.y=-1500;   
    }

    int piezac=0;
    
    //Inicializa la posicion
    Tplayer player;
    player.pos.height=ALTOP;
    player.pos.width=ANCHOP;
    player.pos.x=400;  //Posicion incial
    player.pos.y=SUELO;    //""
    player.y0=player.pos.y;
    player.v0=0;
    player.timeDash=70;
    player.AtkC=0;

    //Inicializacion enemigos
    Ttow torre[MAXTORRE];
    for(j=0;j<MAXTORRE;j++)
    {
        torre[j].status=0;
        torre[0].direccion=0;
        torre[1].direccion=1;
        torre[j].pos.x=2000;
        torre[j].pos.y=800;
        torre[j].pos.height=40;
        torre[j].pos.width=60;
        torre[j].atkC=0;
        for(i=0;i<MAXHITTORRE;i++)
        {
            torre[j].hit[i].status=0;
            torre[j].hit[i].pos.x=0;
            torre[j].hit[i].pos.y=1500;
            torre[j].hit[i].pos.height=20;
            torre[j].hit[i].pos.width=20;
        }
    }
    
    Thit hit[MAXHIT];
    for(i=0;i<MAXHIT;i++)
    {
        hit[i].status=0;
        hit[i].pos.width=RANCHO;
        hit[i].pos.height=10;
        hit[i].pos.x=1280;
        hit[i].pos.y=1500;
    }


    //Inicializacion camara
    Camera2D camara = { 0 };
    camara.target.x=0;
    camara.target.y=0;
    camara.offset.x=0;
    camara.offset.y=0;
    camara.rotation = 0;
    camara.zoom = 1;

    while(!WindowShouldClose())
    {
        /*
        for(j=0;j<MAXPLAT;j++)
        {
            if(plat[j].flag)
            {
                printf("\n%d \n",j);
            }   
        }
        */
        //printf("\n x = %f y = %f ",player.pos.x,player.pos.y);
        //printf("\n jump = %d  jet = %d\n",player.jump,player.jet);
        time+=0.5;
        igncolision+=1;
        frameC++;
        player.timeDash++;
        player.AtkC++;
        torre[0].atkC++;
        torre[1].atkC++;

        //** reajusta posicion x ****************************************************************************************************
        if(player.pos.x<0)
        {
            player.pos.x=0;
        }
        else
        {
            if(player.pos.x>RANCHO-player.pos.width)
            {
                player.pos.x=RANCHO-player.pos.width;
            }
        }
        
        //** reajusta posicion y ***************************************************************************************
        /*
        if(player.pos.y<-900)
        {
            player.pos.y=-900;
        }
        */
        //** pieza **************************************************************************************************************************
        for(j=0;j<3;j++)
        {
            if(CheckPlayerColision(player.pos,pieza[j].pos))
            {
                if(pieza[j].pos.y<SUELO-pieza[j].pos.height-50)
                {
                    pieza[j].status=0;
                    pieza[j].pos.y=SUELO-pieza[j].pos.height;
                    
                    if(piezac<3)
                    {
                        piezac++;
                    }
                    switch (piezac)
                    {
                        case 1:
                            pieza[j].pos.x=50;
                            break;
                        case 2:
                            pieza[j].pos.x=100;
                            break;
                        case 3:
                            pieza[j].pos.x=150;
                            break;
                    }
                }
                else
                {
                    pieza[j].status=1;
                }
                
            }
        }

        //movimiento piezas
        if(piezac<3)
        {
            if(frameC>60)
            {
                if(pieza[0].status)
                {
                    if(pieza[0].pos.y<plat[1].pos.y-pieza[0].pos.height)
                    {
                        pieza[0].pos.y+=4;
                    }
                    else
                    {
                        pieza[0].pos.y=plat[1].pos.y-pieza[0].pos.height;
                    }
                }
                else
                {
                    if(frameC>120)
                    {
                        if(pieza[1].status)
                        {
                            if(pieza[1].pos.y<plat[2].pos.y-pieza[1].pos.height)
                            {
                                pieza[1].pos.y+=4;
                            }
                            else
                            {
                                if(piezac<2)
                                {
                                    pieza[1].pos.y=plat[2].pos.y-pieza[1].pos.height;
                                }
                            }
                            if(frameC>180)
                            {
                                if(pieza[2].status)
                                {
                                    if(pieza[2].pos.y<plat[3].pos.y-pieza[2].pos.height)
                                    {
                                        pieza[2].pos.y+=4;
                                    }
                                    else
                                    {
                                        if(piezac<3)
                                        {
                                            pieza[2].pos.y=plat[3].pos.y-pieza[2].pos.height;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
        //** torreta **************************************************************************************************************************
        for(i=0;i<MAXTORRE;i++)
        {
            if(torre[i].status)
            {
                for(j=0;j<MAXHITTORRE;j++)
                {
                    if(torre[i].atkC>TORREASPEED)
                    {
                        if(torre[i].hit[j].status==0)
                        {
                            if(torre[i].direccion)
                            {
                                torre[i].hit[j].status=1;
                                torre[i].hit[j].pos.x=torre[i].pos.x;
                                torre[i].hit[j].pos.y=torre[i].pos.y;
                                grados=CalculaAngulo(torre[i].hit[j].pos,player.pos);
                                CalculaComponentesVelocidad(TORREVPROYECTIL,CalculaAngulo(torre[i].hit[j].pos,player.pos),torre[i].hit[j].v);
                                torre[i].atkC=0;
                                j=MAXHITTORRE;
                            }
                            else
                            {
                                torre[i].hit[j].status=1;
                                torre[i].hit[j].pos.x=torre[i].pos.x+torre[i].pos.width;
                                torre[i].hit[j].pos.y=torre[i].pos.y;
                                grados=CalculaAngulo(torre[i].hit[j].pos,player.pos);
                                CalculaComponentesVelocidad(TORREVPROYECTIL,CalculaAngulo(torre[i].hit[j].pos,player.pos),torre[i].hit[j].v);
                                torre[i].atkC=0;
                                j=MAXHITTORRE;
                            }
                        }
                    }
                    else
                    {
                        //** ataaque ** movimiento
                        if(torre[i].hit[j].status)
                        {
                            PosicionObieto(torre[i].hit[j].v.vx,torre[i].hit[j].v.vy,torre[i].hit[j].pos);

                            //colision con jugador
                            if(CheckPlayerColision(player.pos,torre[i].hit[j].pos))
                            {
                                player.pos.x=400;  //Posicion incial
                                player.pos.y=SUELO;    //""
                                player.y0=player.pos.y;
                                player.v0=0;
                                player.timeDash=70;
                                LimpiaEnemigos(torre);
                            }

                            //si se paso del borde izquierdo
                            if(torre[i].hit[j].pos.x<0-torre[i].hit[j].pos.width)
                            {
                                torre[i].hit[j].status=0;
                            }
                            else
                            {
                                //si se paso del borde derecho
                                if(torre[i].hit[j].pos.x>RANCHO)
                                {
                                    torre[i].hit[j].status=0;
                                }
                            }

                            
                        }
                    }    
                }

                //Colision con golpe
                for(j=0;j<MAXHIT;j++)
                {
                    if(hit[j].status)
                    {
                        if(CheckMobColision(torre[i].pos,hit[j].pos))
                        {
                            torre[i].status=0;
                        }
                    }
                }
                

                //Colision con jugador
                if(torre[i].status)
                {
                    if(CheckPlayerColision(player.pos,torre[i].pos))
                    {
                        player.pos.x=400;  //Posicion incial
                        player.pos.y=SUELO;    //""
                        player.y0=player.pos.y;
                        player.v0=0;
                        player.timeDash=70;
                        LimpiaEnemigos(torre);
                    }
                }
            }
            else
            {
                //generacion
                random=(rand()%300)+1;
                if(random==1)
                {
                    if(torre[i].direccion)
                    {   
                        torre[i].status=1;
                        torre[i].pos.x=RANCHO-torre[i].pos.width-10;
                        torre[i].pos.y=50;
                    }
                    else
                    {
                        torre[i].status=1;
                        torre[i].pos.x=10;
                        torre[i].pos.y=50;
                    }
                }
            }
        }
        
        
        
        //** caluclar posicion y ********************************************************************************************************************************
        if(player.fall)
        {    
            player.jetc++;
            if(bdown)
            {
                if(velocidad(player.v0,time)>0)
                {
                    if(++c==1)
                    {
                        player.v0=velocidad(player.v0,time); //velocidad inicial igual a velocidad actual
                        player.y0=player.pos.y; 
                        time=1;
                    }
                   
                }
                else
                {
                    Reposo(time,player.v0,player.y0,player.pos.y);
                }

                //jetpack *******************
                if(!player.jet)    //si no esta usando el jetpack calcula caida
                {
                    player.pos.y=Posicion(player.y0,player.v0,time,bdown); //y=y0+v0*t+G*t^2  caida acelerada  
                }
                else
                {
                    player.jet=JetPack(time,player.v0,player.y0,player.pos.y,bdown);   //inicializa un minisalto cuando se suelte abajo
                                                            //hace mas comodo el uso del jetpack
                    player.pos.y+=VY;   //sube con velocidad constante
                    bdown=0;
                }
            }
            else
            {
                
                //jetpack***********
                if(!player.jet)        //si no esta usando el jetpack calcula caida
                {
                    player.pos.y=Posicion(player.y0,player.v0,time,bdown); //y=y0+v0*t+G*t^2   //calcula caida
                }
                else
                {

                    player.jet=JetPack(time,player.v0,player.y0,player.pos.y,bdown);   //inicializa un minisalto cuando se suelte abajo
                                                            //hace mas comodo el uso del jetpack
                    player.pos.y+=VY;   //sube con velocidad constante

                }
            }
        }

        //** colisiones ********************************************************************************************************************************
        //v=v0*2*G*t derivada de la posicion=velocidad
        //suelo
        if(player.pos.y+player.pos.height>SUELO)
        {
            player.pos.y=SUELO-player.pos.height;
            Reposo(time,player.v0,player.y0,player.pos.y);
            player.fall=0;
            bsuelo=1;
            player.jump=1;
            player.jumpjump=0;
            player.jet=0;
        }

        //plataformas
        if(igncolision>35)
        {
            //plataforma cuando cae
            if(velocidad(player.v0,time)>0)
            {
                for(j=0;j<MAXPLAT;j++)
                {
                    if(plat[j].status)
                    {
                        if(ColisionPlat(player,plat[j]))
                        {
                            player.pos.y=plat[j].pos.y-player.pos.height;
                            Reposo(time,player.v0,player.y0,player.pos.y);
                            player.fall=0;
                            plat[j].flag=1;
                            player.jump=1;
                            player.jumpjump=0;
                            bdown=0;
                            player.jet=0;
                        }
                    }
                }
            }
        }

        //si salio de la paltaforma
        for(j=0;j<MAXPLAT;j++)
        {
            if(plat[j].status)
            {
                if(plat[j].flag)
                {
                    if(!ColisionPlat(player,plat[j]))
                    {
                        Reposo(time,player.v0,player.y0,player.pos.y);
                        player.fall=1;
                        plat[j].flag=0;
                        player.jump=0;
                        player.jumpjump=0;
                        bdown=0;
                        player.jet=0;
                    }
                }
            }
        }   


        //** golpe ********************************************************************************************************************************
        for(i=0;i<MAXHIT;i++)
        {
            //** movimiento del disparo ***********************************************************************************
            if(hit[i].status)
            {
                //** Eliminacion del proyectil *******************************************************************************
                hit[i].time++;
                if(hit[i].time<15)
                {
                    hit[i].pos.y=player.pos.y+player.pos.height/4;
                    if(hit[i].direccion)
                    {
                        hit[i].pos.x=player.pos.x+player.pos.width/2;
                    }
                    else
                    {
                        hit[i].pos.x=player.pos.x+player.pos.width/2-RANCHO;
                    }
                }
                else
                {
                    hit[i].status=0;
                    hit[i].time=0;
                    hit[i].pos.x=1500;
                    hit[i].pos.y=-300;
                }
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
                player.jump==0;
                player.fall=1;
                dash=Reposo(time,player.v0,player.y0,player.pos.y);
            }
        }

        //** camara ********************************************************************************************************************************
        camara.target.y=player.pos.y;
        if(player.pos.y>100)
        {
            camara.target.y=CAMY;
            camara.offset.y=CAMY;
        }
        else
        {
            camara.offset.y=RANCHO/12.5;
        }
        
        //** intput ********************************************************************************************************************************
        if(!dash) //right left
        {
            if(IsKeyDown(KEY_RIGHT))
            {
                if(player.pos.x<1280)
                {
                    player.x0=player.pos.x;
                    player.pos.x+=VX;
                    lookR=1;
                    lookL=0;
                }
            }
            else
            {
                if(IsKeyDown(KEY_LEFT))
                {
                    if(player.pos.x>plat[platc-1].pos.x-610)
                    {
                        player.x0=player.pos.x;
                        player.pos.x-=VX;
                        lookR=0;
                        lookL=1;
                    }
                }
            }
        }
        
        if(!dash) //up down
        {
            if(IsKeyDown(KEY_UP))
            {
                if(player.jump)
                {
                    Reposo(time,player.v0,player.y0,player.pos.y);
                    Salto(time,player.v0,player.y0,player.pos.y);
                    player.fall=1;
                    if(player.jumpjump)//!doblesalto
                    {
                        player.jump=1;
                        player.jumpjump=0;
                    }
                    else
                    {
                        player.jump=0;
                    }
                    for(j=0;j<MAXPLAT;j++)
                    {
                        if(plat[j].status)
                        {
                            plat[j].flag=0; 
                        }
                    }
                    player.jetc=0;
                    bsuelo=0;
                    bdown=0;
                }
                else
                {
                    if(player.jetc>60)
                    {
                        player.jet=1;     //esta usando jetpack
                        c=0;           //habilita bajar rapido
                    }
                }
            }
            else
            {
                if(IsKeyPressed(KEY_DOWN))
                {
                    for(j=0;j<MAXPLAT;j++)
                    {
                        if(plat[j].flag)
                        {
                            //if(IsKeyPressedRepeat(KEY_DOWN))
                            {
                                player.fall=1;
                                igncolision=0;
                                bdown=0;
                            }
                        }
                        else
                        {
                            
                            bdown=1;
                            player.fall=1;
                            c=0;
                            
                        }
                    }
                }
            }
        }

        //hit
        if(IsKeyPressed(KEY_X))
        {
            for(i=0;i<MAXHIT;i++)
            {
                Direccioniugador(lookL,lookR,lookUp,lookDown,player);
                if(/*Buff*/1) //** Meiora ******************************************************************************************************
                {
                    if(player.AtkC>VATAQUE)
                    {
                        if(!hit[i].status)
                        {
                            hit[i].pos.y=player.pos.y+player.pos.height/4;
                            Direccioniugador(lookL,lookR,lookL,lookDown,player);
                            if(lookR)
                            {
                                hit[i].direccion=1;
                                hit[i].pos.x=player.pos.x+player.pos.width/2;
                            }
                            else
                            {
                                if(lookL)
                                {
                                    hit[i].direccion=0;
                                    hit[i].pos.x=player.pos.x+player.pos.width/2-RANCHO;
                                }
                            }
                            hit[i].status=1;
                            hit[i].time=0;
                            player.AtkC=0;
                            i=MAXHIT;
                        }
                    }
                }
                else
                {
                    if(player.AtkC>VATAQUEBUFF)
                    {
                        if(!hit[i].status)
                        {
                            hit[i].pos.y=player.pos.y+player.pos.height/4;
                            hit[i].pos.x=player.pos.x+player.pos.width/2;
                            Direccioniugador(lookL,lookR,lookL,lookDown,player);
                            if(lookR)
                            {
                                hit[i].direccion=1;
                            }
                            else
                            {
                                if(lookL)
                                {
                                    hit[i].direccion=0;
                                }
                            }
                            hit[i].status=1;
                            hit[i].time=0;
                            player.AtkC=0;
                            i=MAXHIT;
                        }
                    }
                }
            }
        }  

        //dash KEY C
        if(player.pos.x<1250)
        {
            if(player.pos.x>plat[platc-1].pos.x-590)
            {
                if(player.timeDash>80) 
                {
                    if(!dash)
                    {
                        if(IsKeyPressed(KEY_C))
                        {
                            dash=1;
                            player.timeDash=0;
                            Reposo(time,player.v0,player.y0,player.pos.y);
                            player.fall=0;
                            player.jump=0;
                            player.jumpjump=0;
                        }
                    }
                }
            }
        }
        
        BeginDrawing();
            BeginMode2D(camara);
            ClearBackground(BLACK);

            DrawRectangleRec(player.pos,BLUE);      
            //suelo    
            DrawRectangle(0,SUELO,1280,70,DARKGREEN);

            //plataformas
            for(j=0;j<MAXPLAT;j++)
            {
                DrawRectangleRec(plat[j].pos,DARKGREEN);
            }
            //enemigos
            for(j=0;j<MAXTORRE;j++)
            {
                if(torre[j].status)
                {
                    for(i=0;i<MAXHITTORRE;i++)
                    {
                        if(torre[j].hit[i].status)
                        {
                            DrawRectangleRec(torre[j].hit[i].pos,RED);
                        }
                    }
                    DrawRectangleRec(torre[j].pos,GRAY);
                }
            }
            
            //piezas
            for(j=0;j<3;j++)
            {
                //if(pieza[j].status)
                {
                    DrawRectangleRec(pieza[j].pos,ORANGE);
                }
            }
            //golpe
            for(i=0;i<MAXHIT;i++)
            {
                if(hit[i].status)
                {
                    DrawRectangleRec(hit[i].pos,RED);
                }
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
    if(player.pos.x<=plat.pos.x+plat.pos.width)  //Si esta tocando el lado derecho de la plataforma n
    {
        if(plat.pos.x<=player.pos.x+ANCHOP)   //si esta tocando el lado izquierdo de la platforma n
        {
            if(player.pos.y+player.pos.height<=(plat.pos.y+30))
            {
                if(player.pos.y+player.pos.height>=plat.pos.y)
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

int CheckPlayerColision(Trec player,Trec mob)
{
    if(player.x<(mob.x+mob.width))
    {
        if((player.x+player.width)>mob.x)
        {
            if(player.y<(mob.y+mob.height))
            {
                if((player.y+player.height)>mob.y)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}
/*
int CheckPiezaColision(Trec player,Trec mob) //duplicado para probar sin daño
{
    
    if(player.x<(mob.x+mob.width))
    {
        if((player.x+player.width)>mob.x)
        {
            if(player.y<(mob.y+mob.height))
            {
                if((player.y+player.height)>mob.y)
                {
                    return 1;
                }
            }
        }
    }
    
    return 0;
}
*/
int CheckMobColision(Trec mob,Trec hit)
{
    if(mob.x<(hit.x+hit.width))
    {
        if((mob.x + mob.width) > hit.x)
        {
            if(mob.y < (hit.y + hit.height))
            {
                if((mob.y + mob.height) > hit.y)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
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

void LimpiaEnemigos(Ttow torre[])
{
    int j,i;
    for(j=0;j<MAXTORRE;j++)
    {
        torre[j].status=0;
        for(i=0;i<MAXHITTORRE;i++)
        {
            torre[j].hit[j].status=0;
        }
    }
    
}

int JetPack(float &time,float &v0,int &y0,int y,int bdown)
{
    if(!bdown)
    {
        time=0;
        v0=VSJ;
        y0=y;
    }
    else
    {
        Reposo(time,v0,y0,y);
    }
    return 0;
}

float Radianes(float grados)
{
    return (grados*M_PI/180);
}

void CalculaComponentesVelocidad(float velocidad,float grados,Tvel &v)
{
    if(grados>=360)
    {
        grados-=360;
    }

    v.vy=velocidad*sin(Radianes(grados));
    v.vx=sqrt((pow(velocidad,2)-pow(v.vy,2)));
    if(grados<=90)
    {
        v.vy=-v.vy;
    }
    else
    {
        if(grados<=180)
        {
            v.vx=-v.vx;
            v.vy=-v.vy;
        }
        else
        {
            if(grados<=270)
            {
                v.vx=-v.vx;
                v.vy=-v.vy;
            }      
            else
            {
                v.vy=-v.vy;
            }
        }
    }
}

void PosicionObieto(float vx,float vy,Trec &pos)
{
    pos.x+=vx;
    pos.y+=vy;
}

void Direccioniugador(int &L,int &R,int &Up,int &Down,Tplayer player)
{
    if(IsKeyDown(KEY_RIGHT))
    {
        if(IsKeyDown(KEY_UP))
        {
            R=1;
            Up=1;
            Down=0;
            L=0;
        }
        else
        {
            if(IsKeyDown(KEY_DOWN))
            {
                R=1;
                Up=0;
                Down=1;
                L=0;
            }
            else
            {
                R=1;
                Up=0;
                Down=0;
                L=0;
            }
        }
    }
    else
    {
        if(IsKeyDown(KEY_LEFT))
        {
            if(IsKeyDown(KEY_UP))
            {
                R=0;
                Up=1;
                Down=0;
                L=1;
            }
            else
            {
                if (IsKeyDown(KEY_DOWN))
                {
                    R=0;
                    Up=0;
                    Down=1;
                    L=1;
                }
                else
                {
                    R=0;
                    Up=0;
                    Down=0;
                    L=1;
                }
            }
        }
        else
        {
            if(IsKeyDown(KEY_UP))
            {
                R=0;
                Up=1;
                Down=0;
                L=0;
            }
            else
            {
                if(IsKeyDown(KEY_DOWN))
                {
                    R=0;
                    Up=0;
                    Down=1;
                    L=0;
                }
                else
                {
                    if(player.x0<=player.pos.x)
                    {
                        R=1;
                        Up=0;
                        Down=0;
                        L=0;
                    }
                    else
                    {
                        R=0;
                        Up=0;
                        Down=0;
                        L=1;
                    }
                }
            }
        }
    }
}

void InicializaProyectil(int L,int R,int Up,int Down,Tplayer player,Thit &hit)
{
    hit.pos.y=player.pos.y+player.pos.height/4;
    hit.pos.x=player.pos.x+player.pos.width/2;
    if(R)
    {
        if(Up)
        {
            hit.direccion=1;
        }
        else
        {
            if(Down)
            {
                hit.direccion=7;
            }
            else
            {
                hit.direccion=0;
            }
        }
    }
    else
    {
        if(L)
        {
            if(Up)
            {
                hit.direccion=3;
            }
            else
            {
                if (Down)
                {
                    hit.direccion=5;
                }
                else
                {
                    hit.direccion=4;
                }
            }
        }
        else
        {
            if(Up)
            {
                hit.direccion=2;
            }
            else
            {
                if(Down)
                {
                    hit.direccion=6;
                }
            }
        }
    }
}

float CalculaAngulo(Trec enemigo,Trec player)
{
    float difx=fabs(player.x+player.width/2-enemigo.x+enemigo.width/2);
    float dify=fabs(player.y+player.height/2-enemigo.y+enemigo.height/2);
    float a=atan2(difx,dify);
    a=a*180/M_PI;
    if(player.x>enemigo.x)
    {
        if(player.y>enemigo.y)
        {
            return (270+a);
        }
        else
        {
            return (90-a);
        }
    }
    else
    {
        if(player.y>enemigo.y)
        {
            return (270-a);
        }
        else
        {
            return (90+a);
        }
    }
    return 0;
}