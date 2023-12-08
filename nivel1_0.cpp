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
#define VSi -4
#define VY 3
#define VD 7.5

#define MAXANGUILA 3
#define ANGUILASPEED 6
#define MAXSHARK 2
#define SHARKSPEED 9
#define MAXTORTUGA 2
#define TORTUGASPEED 3

#define MAXPLAT 3

#define MAXHIT 500
#define VATAQUE 40
#define VATAQUEBUFF 30
#define VPROYECTIL 10

typedef Rectangle Trec;
//blank transparente

//typedef Rectangle Tplayer;

typedef struct _velocidad
{
    float vx;
    float vy;
}Tvel;

typedef struct _shark
{
    Trec pos;
    int status=0;
    int right=0;
    int left=0;
    Tvel v;
}Tshark;

typedef struct _tortuga
{
    Trec pos;
    int status=0;
    int right=0;
    int left=0;
}Ttortu;

typedef struct _anghit
{
    Trec pos;
    int status;
    int time;
}Tanghit;

typedef struct _anguila
{
    Trec pos;
    int status=0;
    int right=0;
    int left=0;
    Tvel v;
    Tanghit hit;
}Tangui;


typedef struct _hit
{
    Trec pos;                               //7   0    1
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

typedef struct _iugador
{
    Trec pos;
    int timeDash;
    int dash;
    int x0;
    int AtkC;
}Tplayer;

void Direccioniugador(int &l,int &r,int &up,int &down,Tplayer player);
void InicializaProyectil(int l,int r,int up,int down,Tplayer player,Thit &hit);
void CalculaComponentesVelocidad(float velocidad,float grados,Tvel &v);
float Radianes(float grados);
void PosicionObieto(float vx,float vy,Trec &pos);
int CheckMobColision(Trec mob,Thit hit);
int CheckPlayerColision(Trec player,Trec mob);
void LimpiaEnemigos(/*Tave ave[],Tcar car[]*/Tshark shark[],Ttortu tort[],Tangui ang[]);
float CalculaAnguloAnguila(Trec ang,Trec player);
void AngElectro(Tangui &ang);

int main()
{
    float VDDIAGONAL=VD*sin(45)/sin(90);
    SetTargetFPS(60);  
    InitWindow(RANCHO,RALTO,"iuego");
    srand(time(NULL));
    int i,j;
    Tplayer player;
    player.pos.height=ALTOP;
    player.pos.width=ANCHOP;
    player.pos.x=RANCHO/2;
    player.pos.y=SUELO-player.pos.height;
    player.dash=0;
    player.timeDash=0;
    player.x0=player.pos.x;
    player.AtkC=0;
    int lookR=1;
    int lookL=0;
    int lookUp=0;
    int lookDown=0;

    int random;
    float randomM[2];
    Thit hit[MAXHIT];
    for(i=0;i<MAXHIT;i++)
    {
        hit[i].status=0;
        hit[i].pos.width=20;
        hit[i].pos.height=20;
        hit[i].pos.x=1280;
        hit[i].pos.y=1500;
    }

    //** plataformas **************************************************************************************************************************
    Trec plat[MAXPLAT];
    for(i=0;i<MAXPLAT;i++)
    {
        plat[i].height=30;
        plat[i].width=200;
    }
    plat[0].x=100;
    plat[0].y=200;
    plat[1].x=RANCHO/2-plat[1].width/2;
    plat[1].y=400;
    plat[2].x=RANCHO-100-plat[2].width;
    plat[2].y=200;

    //** piezas **********************************************************************************************************************************
    Tpart pieza[3];
    int piezac=0;
    int time=0;
    for(j=0;j<3;j++)
    {
        pieza[j].status=0;
        pieza[j].pos.height=80;
        pieza[j].pos.width=50;
        pieza[j].status=1;
        pieza[j].pos.x=plat[j].x+plat[j].width/2-pieza[j].pos.width/2;
        pieza[j].pos.y=-300;
    }
    
    
    //** enemigos **********************************************************************************************************************************
    Tshark shark[MAXSHARK];
    for(i=0;i<MAXSHARK;i++)
    {
        shark[i].status=0;
        shark[i].right=0;
        shark[i].left=0;
        shark[i].pos.x=2000;
        shark[i].pos.y=800;
        shark[i].pos.height=60;
        shark[i].pos.width=120;
    }

    Ttortu tort[MAXTORTUGA];
    for(i=0;i<MAXSHARK;i++)
    {
        tort[i].status=0;
        tort[i].right=0;
        tort[i].left=0;
        tort[i].pos.x=2000;
        tort[i].pos.y=800;
        tort[i].pos.height=60;
        tort[i].pos.width=80;
    }

    Tangui ang[MAXANGUILA];
    for(i=0;i<MAXANGUILA;i++)
    {
        ang[i].status=0;
        ang[i].right=0;
        ang[i].left=0;
        ang[i].pos.x=2000;
        ang[i].pos.y=800;
        ang[i].pos.height=20;
        ang[i].pos.width=85;
        ang[i].hit.pos.height=ang[0].pos.height*3;
        ang[i].hit.pos.width=ang[0].pos.width*1.5;
        ang[i].hit.pos.y=800;
        ang[i].hit.pos.x=2000;
        ang[i].hit.status=0;
        ang[i].hit.time=0;
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
        //printf("x = %f y = %f\n",player.pos.x,player.pos.y);
        player.timeDash++;
        player.AtkC++;
        time++;
        //reaiusta posicion si sale de limites *********************************************************************************************
        if(player.pos.y<25)
        {
            player.pos.y=25;
        }
        else
        {
            if(player.pos.y>SUELO-player.pos.height)
            {
                player.pos.y=SUELO-player.pos.height;
            }
            else
            {
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
            }
        }

        //** piezas ****************************************************************************************************************************
        for(j=0;j<3;j++)
        {   
            //recolleccion
            if(CheckPlayerColision(player.pos,pieza[j].pos))
            {
                pieza[j].status=0;
                pieza[j].pos.y=SUELO-pieza[j].pos.height;
                piezac++;
                switch (piezac)
                {
                    case 1:
                        pieza[j].pos.x=900;
                        break;
                    case 2:
                        pieza[j].pos.x=950;
                        break;
                    case 3:
                        pieza[j].pos.x=990;
                        break;
                }
            }
            
            //drop
            if(!pieza[j].status)
            {
                if(CheckPlayerColision(player.pos,pieza[j].pos))
                {
                    pieza[j].status=1;
                }
            }
        }

        //movimiento
        if(time>600)
        {
            if(pieza[0].pos.y<plat[0].y-pieza[0].pos.height)
            {
                pieza[0].pos.y+=4;
            }
            else
            {
                if(piezac<1)
                {
                    pieza[0].pos.y=plat[0].y-pieza[0].pos.height;
                }
            }
            if(time>1200)
            {
                if(pieza[1].pos.y<plat[1].y-pieza[1].pos.height)
                {
                    pieza[1].pos.y+=4;
                }
                else
                {
                    if(piezac<2)
                    {
                        pieza[1].pos.y=plat[1].y-pieza[1].pos.height;
                    }
                }
                if(time>1800)
                {
                    if(pieza[2].pos.y<plat[2].y-pieza[2].pos.height)
                    {
                        pieza[2].pos.y+=4;
                    }
                    else
                    {
                        if(piezac<3)
                        {
                            pieza[2].pos.y=plat[2].y-pieza[2].pos.height;
                        }
                    }
                }
            }
            
        }
        //** enemigos **
        //** tiburones ******************************************************************************************************************************
        for(i=0;i<MAXSHARK;i++)
        {
            //comportameinto
            if(shark[i].status)
            {           
                //movimiento enemigo **si sale de la pantalla se elimina**
                if(shark[i].right)
                {   //movimiento
                    if(shark[i].pos.y<75)
                    {
                        shark[i].pos.x-=SHARKSPEED;
                    }
                    else
                    {
                        if(shark[i].pos.y>SUELO-50-shark[i].pos.height)
                        {
                            shark[i].pos.x-=SHARKSPEED;
                        }
                        else
                        {
                            PosicionObieto(shark[i].v.vx,shark[i].v.vy,shark[i].pos);
                        }
                    }

                    //eliminacion
                    if(shark[i].pos.x<0-shark[i].pos.width)
                    {
                        shark[i].status=0;
                    }
                }
                else
                {
                    if(shark[i].left)
                    {   //movimiento
                        if(shark[i].pos.y<75)
                        {
                            shark[i].pos.x+=SHARKSPEED;
                        }
                        else
                        {
                            if(shark[i].pos.y>SUELO-50-shark[i].pos.height)
                            {
                                shark[i].pos.x+=SHARKSPEED;
                            }
                            else
                            {
                                PosicionObieto(shark[i].v.vx,shark[i].v.vy,shark[i].pos);
                            }
                        }
                        //eliminacion
                        if(shark[i].pos.x>RANCHO+shark[i].pos.width)
                        {
                            shark[i].status=0;
                        }
                    }
                }
                
                //Colision con golpe
                if(hit)
                {
                    for(j=0;j<MAXHIT;j++)
                    {
                        if(CheckMobColision(shark[i].pos,hit[j]))
                        {
                            shark[i].status=0;
                        }
                    }
                }
                //Colision con iugador
                if(shark[i].status)
                {
                    if(CheckPlayerColision(player.pos,shark[i].pos))
                    {
                        player.pos.x=400;  //Posicion incial
                        player.pos.y=SUELO;    //""
                        player.timeDash=70;
                        LimpiaEnemigos(shark,tort,ang);
                    }
                }

            }
            else
            {
                //generacion
                random=(rand()%50)+1;
                if(random==1)
                {
                    shark[i].right=rand()%2;
                    random=rand()%30;
                    if(shark[i].right)
                    {   
                        shark[i].status=1;
                        CalculaComponentesVelocidad(SHARKSPEED,float(random+165),shark[i].v);
                        shark[i].pos.x=RANCHO;
                        shark[i].pos.y=(rand()%550)+50;
                        shark[i].left=0;
                    }
                    else
                    {
                        shark[i].status=1;
                        CalculaComponentesVelocidad(SHARKSPEED,float(random+345),shark[i].v);
                        shark[i].pos.x=0-shark[i].pos.width;
                        shark[i].pos.y=(rand()%550)+50;
                        shark[i].left=1;
                    }
                }
            }
        }

        //** tortugas ******************************************************************************************************************************
        for(i=0;i<MAXTORTUGA;i++)
        {
            //comportameinto
            if(tort[i].status)
            {           
                //movimiento enemigo **si sale de la pantalla se elimina**
                if(tort[i].right)
                {   //movimiento
                    tort[i].pos.x-=TORTUGASPEED;
                    if(tort[i].pos.x<=0-tort[i].pos.height)
                    {
                        tort[i].status=0;
                    }
                }
                else
                {
                    if(tort[i].left)
                    {   //movimiento
                        tort[i].pos.x+=TORTUGASPEED;
                        //eliminacion
                        if(tort[i].pos.x>RANCHO+tort[i].pos.width)
                        {
                            tort[i].status=0;
                        }
                    }
                }
                
                //Colision con golpe
                if(hit)
                {
                    for(j=0;j<MAXHIT;j++)
                    {
                        if(CheckMobColision(tort[i].pos,hit[j]))
                        {
                            tort[i].status=0;
                        }
                    }
                }
                //Colision con iugador
                if(tort[i].status)
                {
                    if(CheckPlayerColision(player.pos,tort[i].pos))
                    {
                        player.pos.x=400;  //Posicion incial
                        player.pos.y=SUELO;    //""
                        player.timeDash=70;
                        LimpiaEnemigos(shark,tort,ang);
                    }
                }

            }
            else
            {
                //generacion
                random=(rand()%100)+1;
                if(random==1)
                {
                    tort[i].right=rand()%2;
                    if(tort[i].right)
                    {   
                        tort[i].status=1;
                        tort[i].pos.x=RANCHO;
                        tort[i].pos.y=(rand()%550)+50;
                        tort[i].left=0;
                    }
                    else
                    {
                        tort[i].status=1;
                        tort[i].pos.x=0-tort[i].pos.width;
                        tort[i].pos.y=(rand()%550)+50;
                        tort[i].left=1;
                    }
                }
            }
        }
        
        //** anguilas *********************************************************************************************************************************
        for(i=0;i<MAXANGUILA;i++)
        {
            //comportameinto
            if(ang[i].status)
            {           
                //movimiento enemigo **si sale de la pantalla se elimina**
                if(ang[i].right)
                {   //movimiento
                    if(ang[i].pos.y<75)
                    {
                        ang[i].pos.x-=ANGUILASPEED;
                    }
                    else
                    {
                        if(ang[i].pos.y>SUELO-50-ang[i].pos.height)
                        {
                            ang[i].pos.x-=ANGUILASPEED;
                        }
                        else
                        {
                            PosicionObieto(ang[i].v.vx,ang[i].v.vy,ang[i].pos);
                        }
                    }

                    //eliminacion
                    if(ang[i].pos.x<0-ang[i].pos.width)
                    {
                        ang[i].status=0;
                        ang[i].hit.status=0;
                    }

                    //** generacion ataque enemigo ************************************************************************************************
                    random=(rand()%20)+1;
                    if(random==1)
                    {
                        if(!ang[i].hit.status)
                        {
                            if(ang[i].pos.x<=player.pos.x+player.pos.width+200)
                            {
                                if(ang[i].pos.x>=player.pos.x-200)
                                {
                                    if(ang[i].pos.y<=player.pos.y+player.pos.height+200)
                                    {
                                        if(ang[i].pos.y>=player.pos.y-200)
                                        {
                                            //random=rand()%MAXANGUILAHIT;
                                            AngElectro(ang[i]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    
                    //** comporamiento descarga electrica ************************************************************************************
                    if(ang[i].status)
                    {
                        if(ang[i].hit.status)
                        {
                            if(ang[i].hit.time<120)
                            {
                                ang[i].hit.pos.y=ang[i].pos.y-ang[i].pos.height;
                                ang[i].hit.pos.x=ang[i].pos.x-21;
                                ang[i].hit.time++;

                                //colision con jugador
                                if(CheckPlayerColision(player.pos,ang[i].hit.pos))
                                {
                                    player.pos.x=400;  //Posicion incial
                                    player.pos.y=SUELO;    //""
                                    player.timeDash=70;
                                    LimpiaEnemigos(shark,tort,ang);
                                }
                            }
                            else
                            {
                                ang[i].hit.status=0;
                            }
                        }
                    }
                    

                }
                else
                {
                    if(ang[i].left)
                    {   //movimiento
                        if(ang[i].pos.y<75)
                        {
                            ang[i].pos.x+=ANGUILASPEED;
                        }
                        else
                        {
                            if(ang[i].pos.y>SUELO-50-ang[i].pos.height)
                            {
                                ang[i].pos.x+=ANGUILASPEED;
                            }
                            else
                            {
                                PosicionObieto(ang[i].v.vx,ang[i].v.vy,ang[i].pos);
                            }
                        }
                        //eliminacion
                        if(ang[i].pos.x>RANCHO+ang[i].pos.width)
                        {
                            ang[i].status=0;
                        }
                    }
                }
                
                //Colision con golpe
                if(hit)
                {
                    for(j=0;j<MAXHIT;j++)
                    {
                        if(CheckMobColision(ang[i].pos,hit[j]))
                        {
                            ang[i].status=0;
                        }
                    }
                }
                
                //Colision con iugador
                if(ang[i].status)
                {
                    if(CheckPlayerColision(player.pos,ang[i].pos))
                    {
                        player.pos.x=400;  //Posicion incial
                        player.pos.y=SUELO;    //""
                        player.timeDash=70;
                        LimpiaEnemigos(shark,tort,ang);
                    }
                }

            }
            else
            {
                //generacion
                random=(rand()%50)+1;
                if(random==1)
                {
                    ang[i].right=rand()%2;
                    if(ang[i].right)
                    {   
                        ang[i].status=1;
                        ang[i].pos.x=RANCHO;
                        ang[i].pos.y=(rand()%550)+60;
                        CalculaComponentesVelocidad(ANGUILASPEED,CalculaAnguloAnguila(ang[i].pos,player.pos),ang[i].v);
                        ang[i].left=0;
                    }
                    else
                    {
                        ang[i].status=1;
                        ang[i].pos.x=0-ang[i].pos.width;
                        ang[i].pos.y=(rand()%550)+60;
                        CalculaComponentesVelocidad(ANGUILASPEED,CalculaAnguloAnguila(ang[i].pos,player.pos),ang[i].v);
                        ang[i].left=1;
                    }
                }
            }
        }

        //** dash **************************************************************************************************************************
        if(player.dash)
        {   
            if(player.timeDash<20)
            {
                if(lookR)
                {
                    if(lookUp)
                    {
                        player.pos.x+=VDDIAGONAL;
                        player.pos.y-=VDDIAGONAL;
                    }
                    else
                    {
                        if(lookDown)
                        {
                            player.pos.x+=VDDIAGONAL;
                            player.pos.y+=VDDIAGONAL;
                        }
                        else
                        {
                            player.pos.x+=VD;   
                        }
                    }
                }
                else
                {
                    if(lookL)
                    {
                        if(lookUp)
                        {
                            player.pos.x-=VDDIAGONAL;
                            player.pos.y-=VDDIAGONAL;
                        }
                        else
                        {
                            if(lookDown)
                            {
                                player.pos.x-=VDDIAGONAL;
                                player.pos.y+=VDDIAGONAL;
                            }
                            else
                            {
                                player.pos.x-=VD;   
                            }
                        }
                    }
                    else
                    {
                        if(lookUp)
                        {
                            player.pos.y-=VD;
                        }
                        else
                        {
                            if(lookDown)
                            {
                                player.pos.y+=VD;
                            }
                        }
                    }
                }  
            }
            else
            {
                lookDown=0;
                lookUp=0;
                player.dash=0;
            }
        }

        //** hit ********************************************************************************************************************************
        for(i=0;i<MAXHIT;i++)
        {
            //** movimiento del disparo ***********************************************************************************
            if(hit[i].status)
            {
                PosicionObieto(hit[i].v.vx,hit[i].v.vy,hit[i].pos);

                //** Eliminacion del proyectil *******************************************************************************
                //si se paso del borde izquierdo
                if(hit[i].pos.x<0-hit[i].pos.width)
                {
                    hit[i].status=0;
                }
                else
                {
                    //si se paso del borde derecho
                    if(hit[i].pos.x>RANCHO)
                    {
                        hit[i].status=0;
                    }
                }

                if(hit[i].pos.y<0)
                {
                    hit[i].status=0;
                }
                else
                {
                    if(hit[i].pos.y>RALTO)
                    {
                        hit[i].status=0;
                    }
                }
            }
        }

        //** input *****************************************************************************************************************************
        if(!player.dash) //right left
        {
            if(IsKeyDown(KEY_RIGHT))
            {
                player.x0=player.pos.x;
                player.pos.x+=VX;
                lookR=1;
                lookL=0;
            }
            else
            {
                if(IsKeyDown(KEY_LEFT))
                {
                    player.x0=player.pos.x;
                    player.pos.x-=VX;
                    lookR=1;
                    lookL=0;
                }
            }
        }
        

        if(!player.dash) //up down
        {
            if(IsKeyDown(KEY_UP))
            {
                player.pos.y-=VY;
            }
            else
            {
                if(IsKeyDown(KEY_DOWN))
                {
                    player.pos.y+=VY;
                }
            }
        }

        //dash KEY C
        if(player.timeDash>80) 
        {
            if(!player.dash)
            {
                if(IsKeyPressed(KEY_C))
                {
                    Direccioniugador(lookL,lookR,lookUp,lookDown,player);
                    player.dash=1;
                    player.timeDash=0;
                }
            }
        }

        //hit
        if(IsKeyDown(KEY_X))
        {
            for(i=0;i<MAXHIT;i++)
            {
                Direccioniugador(lookL,lookR,lookUp,lookDown,player);
                if(/*Buff*/1) //** Meiora ******************************************************************************************************
                {
                    if(player.AtkC>VATAQUE)
                    {
                        if(hit[i].status==0)
                        {
                            hit[i].status=1;
                            player.AtkC=0;
                            InicializaProyectil(lookL,lookR,lookUp,lookDown,player,hit[i]);
                            CalculaComponentesVelocidad(VPROYECTIL,45*hit[i].direccion,hit[i].v);
                            //printf("Direccion = %d l = %d r = %d up = %d down = %d \n",hit[i].direccion,lookL,lookR,lookUp,lookDown);
                            i=MAXHIT;
                        }
                    }
                }
                else
                {
                    if(player.AtkC>VATAQUEBUFF)
                    {
                        if(hit[i].status==0)
                        {
                            hit[i].status=1;
                            player.AtkC=0;
                            InicializaProyectil(lookL,lookR,lookUp,lookDown,player,hit[i]);
                            CalculaComponentesVelocidad(VPROYECTIL,45*hit[i].direccion,hit[i].v);
                            //printf("Direccion = %d l = %d r = %d up = %d down = %d \n",hit[i].direccion,lookL,lookR,lookUp,lookDown);
                            i=MAXHIT;
                        }
                    }
                }
            }
        }  

        BeginDrawing();
            BeginMode2D(camara);
            ClearBackground(SKYBLUE);
            DrawRectangle(0,50,RANCHO,RALTO,BLUE);
            DrawRectangleRec(player.pos,DARKBLUE);    
            for(i=0;i<MAXHIT;i++)
            {
                if(hit[i].status)
                {
                    DrawRectangleRec(hit[i].pos,RED);
                }
            }
            //suelo    
            DrawRectangle(0,SUELO,1280,70,DARKGREEN);
            
            //enemigos
            for(i=0;i<MAXSHARK;i++)
            {
                if(shark[i].status)
                {
                    DrawRectangleRec(shark[i].pos,GRAY);
                }
            }
            for(i=0;i<MAXTORTUGA;i++)
            {
                if(tort[i].status)
                {
                    DrawRectangleRec(tort[i].pos,GREEN);
                }
            }
            for(i=0;i<MAXANGUILA;i++)
            {
                if(ang[i].status)
                {
                    if(ang[i].hit.status)
                    {
                        DrawRectangleRec(ang[i].hit.pos,YELLOW);
                    }
                    DrawRectangleRec(ang[i].pos,DARKGRAY);
                }
            }
            //piezas
            for(i=0;i<3;i++)
            {
                if(pieza[i].status)
                {
                    DrawRectangleRec(pieza[i].pos,ORANGE);
                }
            }
            //plataformas
            for(i=0;i<MAXPLAT;i++)
            {
                DrawRectangleRec(plat[i],DARKGREEN);
            }
            EndMode2D();
        EndDrawing();

    }

    CloseWindow();
    return 0;
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

float Radianes(float grados)
{
    return (grados*M_PI/180);
}

void PosicionObieto(float vx,float vy,Trec &pos)
{
    pos.x+=vx;
    pos.y+=vy;
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
int CheckMobColision(Trec mob,Thit hit)
{
    if(mob.x<(hit.pos.x+hit.pos.width))
    {
        if((mob.x + mob.width) > hit.pos.x)
        {
            if(mob.y < (hit.pos.y + hit.pos.height))
            {
                if((mob.y + mob.height) > hit.pos.y)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void LimpiaEnemigos(/*Tave ave[],Tcar car[]*/Tshark shark[],Ttortu tort[],Tangui ang[])
{
    int i;
    /*
    for(i=0;i<MAXAVE;i++)
    {
        ave[i].status=0;
    }
    for(i=0;i<MAXCAR;i++)
    {
        car[i].status=0;
    }
    */
    for(i=0;i<MAXSHARK;i++)
    {
        shark[i].status=0;
    }
    for(i=0;i<MAXTORTUGA;i++)
    {
        tort[i].status=0;
    }
    for(i=0;i<MAXANGUILA;i++)
    {
        ang[i].status=0;
        ang[i].hit.status=0;
    }
    
}

float CalculaAnguloAnguila(Trec ang,Trec player)
{
    float difx=fabs(player.x+player.width/2-ang.x);
    float dify=fabs(player.y+player.height/2-ang.y);
    float a=atan2(difx,dify);
    a=a*180/M_PI;
    if(player.x>ang.x)
    {
        if(player.y>ang.y)
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
        if(player.y>ang.y)
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

void AngElectro(Tangui &ang)
{
    ang.hit.pos.y=ang.pos.y-ang.pos.height;
    ang.hit.pos.x=ang.pos.x-21;
    ang.hit.status=1;
    ang.hit.time=0;
}