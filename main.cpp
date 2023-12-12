#include "C:\raylib\raylib\src\raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//menu

#define JUGAR 0
#define OPCIONES 1
#define SALIR 2

#define DIFICULTAD 0
#define SONIDO 1
#define REGRESAR 2

#define NEWP 0
#define SALIRJ 1

//** NIVEL 1 **********************************************************************************************************************
#define COLUMNAS1 3
#define RENGLONES1 3

#define RANCHO 1280
#define RALTO 720
#define CAMY 360
#define CAMX 640

#define ALTOP 85
#define ANCHOP 50
#define SUELO 650
#define MAXVIDA 3
#define INVULERABILIDAD 120

// DROPS
#define MAXDROPVIDA 10
#define DESPAWNTIME 600
#define MAXDROPASPEED 10
#define DURACIONBUFF 600

#define VX1 3
#define VY1 3
#define VD1 7.5

#define MAXANGUILA 3
#define ANGUILASPEED 5
#define MAXSHARK 2
#define SHARKSPEED 7
#define MAXTORTUGA 2
#define TORTUGASPEED 3

#define MAXPLAT1 3

#define MAXHIT1 500
#define VATAQUE1 50
#define VATAQUEBUFF1 20
#define VPROYECTIL1 10

//nivel2
#define G1 0.1
#define GD1 0.2

#define VX 4
#define VS -11
#define VD 10

#define MAXAVE 5
#define AVESPEED 7
#define MAXEGG 8
#define MAXCAR 2
#define CARSPEED 9

#define MAXPLAT 30

//nivel 3
#define G3 0.1
#define GD3 0.15

#define VX3 3
#define VS3 -11
#define VSJ3 -4
#define VY3 -3
#define VD3 6

#define MAXTORRE 2
#define TORREASPEED 180
#define TORREVPROYECTIL 6
#define MAXHITTORRE 2
#define MAXOVNI 2
#define OVNISPEED 3
#define OVNILONG 150
#define OVNIAMP 15

#define MAXPLAT 4
#define MAXHIT 5
#define VATAQUE 60
#define VATAQUEBUFF 30
#define VPROYECTIL 10.0

#define RECVEHICULO 900
#define MAXPLAT3 4
#define MAXHIT3 5
#define VATAQUE3 60
#define VATAQUEBUFF3 30
#define VPROYECTIL3 10.0

////////////////////////////////////////////// STRUCTS 
//NIVEL 1 ***********************************************************************************************************
typedef Rectangle Trec;

typedef struct _tabla
{
    Trec pos;
    int num;
    char opRight[2];
    char opDown[2];
    int status;
} Ttab;

typedef struct _velocidad
{
    float vx;
    float vy;
} Tvel;

typedef struct _shark
{
    Trec pos;
    int status = 0;
    int right = 0;
    int left = 0;
    Tvel v;
} Tshark;

typedef struct _tortuga
{
    Trec pos;
    int status = 0;
    int right = 0;
    int left = 0;
} Ttortu;

typedef struct _anghit
{
    Trec pos;
    int status;
    int time;
} Tanghit;

typedef struct _anguila
{
    Trec pos;
    int status = 0;
    int right = 0;
    int left = 0;
    Tvel v;
    Tanghit hit;
} Tangui;

typedef struct _hit
{
    Trec pos;      // 7   0    1
    int status;    //
    int direccion; //--------------------->  //6   p    2
    Tvel v;        //
} Thit;            // 5   4    3

typedef struct _plataforma
{
    Trec pos;
    int status;
    int flag;
} Tplat;

typedef struct _vehiculo
{
    Trec pos;
    int status;
    int listo;
} Tpart;

typedef struct _vida
{
    Trec pos;
    int num;
    int time;
} Tvida;

typedef struct _jugador
{
    Trec pos;
    int timeDash;
    int dash;
    int x0;
    int AtkC;
    int buff;
    Tvida vida;
} Tplayer;

typedef struct _ASbuff
{
    Trec pos;
    int statusDraw;
    int statusFun;
    int time;
    int duracion;
} TatkSpeed;

typedef struct _corazon
{
    Trec pos;
    int status;
    int time;
} Tcora;
//niveel 2 *********************************************************************************************************************
typedef struct _plataforma
{
    Trec pos;
    int status;
    int flag;
} Tplat;

typedef struct _jugador
{
    Trec pos;
    int y0;
    float v0;
    int timeDash;
    int jump;
    int jumpjump;
    int fall;
    Tvida vida;
} Tplayer2;

typedef struct _ave
{
    Trec pos;
    int status;
    int right;
    int left;

} Tave;

typedef struct _huevo
{
    Trec pos;
    int status;
    int y0;
    int time;
} Tegg;

typedef struct _car
{
    Trec pos;
    int status;
    int movimiento;
    int time;
} Tcar;

//nivel3***************************************************************************************************
typedef struct _jugador3
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
    int buff = 0;
    Tvida vida;
} Tplayer3;

typedef struct _tower
{
    Trec pos;
    int status;
    int direccion;
    int atkC;
    Thit hit[MAXHITTORRE];
} Ttow;

typedef struct _ovni
{
    Trec pos;
    int direccion;
    int status;
    int time;
} Tovni;

typedef struct _Elaser
{
    Trec pos;
    int status;
    int atkC;
    float grados;
    float altura;
    Trec hit;
    int time;
    int mov;
} Tlaser;

typedef struct _hit3
{
    Trec pos;
    int time;      // 7   0    1
    int status;    //
    int direccion; //--------------------->  //6   p    2
    Tvel v;        //
} Thit3;            // 5   4    3

//portotipos
//nivel 1
void Direccioniugador(int &l, int &r, int &up, int &down, Tplayer player);
void InicializaProyectil(int l, int r, int up, int down, Tplayer player, Thit &hit);
void CalculaComponentesVelocidad(float velocidad, float grados, Tvel &v);
float Radianes3(float grados);
void PosicionObieto3(float vx, float vy, Trec &pos);
int CheckMobColision(Trec mob, Thit hit);
int CheckPlayerColision(Trec player, Trec mob);
void LimpiaEnemigosLvl1(Tshark shark[], Ttortu tort[], Tangui ang[]);
float CalculaAnguloAnguila(Trec ang, Trec player);
void AngElectro(Tangui &ang);
void muerteLvl1(Tplayer &player, Tshark shark[], Ttortu tort[], Tangui ang[], Tpart pieza[], Trec plat[]);
//nivel 2
void nivel2(int diflvl);
float velocidad1(float v0, float time);
int ColisionPlat2(Tplayer2 player, Tplat plat);
int Reposo3(float &time, float &v0, int &y0, int y);
int Salto1(float &time, float &v0, int &y0, int y);
int Posicion1(int y0, float v0, float time, int g);
void CalculaPosEnemigo(Tave &mob);
void DropEgg(Tave mob, Tegg &egg);
void LimpiaEnemigosLvl2(Tave ave[], Tcar car[]);
void muerteLvl2(Tplayer2 &player,Tave ave[],Tcar car[],Tpart pieza[],Tplat plat[],int platc);
//nivel3
int nivel3(int diflvl);
float velocidad3(float v0, float time);
int ColisionPlat3(Tplayer3 player, Tplat plat);
int Reposo3(float &time, float &v0, int &y0, int y);
int Salto1(float &time, float &v0, int &y0, int y);
int Posicion3(int y0, float v0, float time, int g);
int CheckMobColision(Trec mob, Trec hit);
int CheckPlayerColision(Trec player, Trec mob);
void LimpiaEnemigosLvl3(Ttow torre[], Tovni ovni[]);
int JetPack(float &time, float &v0, int &y0, int y, int bdown);
void InicializaProyectil3(int L, int R, int Up, int Down, Tplayer3 player, Thit &hit);
void CalculaComponentesVelocidad(float velocidad, float grados, Tvel &v);
float Radianes3(float grados);
void PosicionObieto3(float vx, float vy, Trec &pos);
void Direccioniugador3(int &L, int &R, int &Up, int &Down, Tplayer3 player);
float CalculaAngulo3(Trec ang, Trec player);
void muerteLvl3(Tplayer3 &player, Ttow torre[], Tovni ovni[], Tpart pieza[], Tplat plat[]);
float velocidad(float v0, float time);

//puzzles
void cinemaPuzleNivel1(int diflvl);
void cinemaPuzleNivel2(int diflvl);
void cinemaPuzleNivel3(int diflvl);

int main(void)
{
    SetTargetFPS(60);

    int op, subOp, opJug;
    int diflvl = 1, vol = 3;
    const int screenWidth = 1280;
    const int screenHeight = 720;

    float scrollingBack = 0.0f;
    float scrollingBigPlanet = 0.0f;
    float scrollingFarPlanet = 0.0f;
    float scrollingRingPlanet = 0.0f;
    float scrollingSpaceStar = 0.0f;

    InitWindow(screenWidth, screenHeight, "window");
    //****************************************************** TEXTURAS ***********************************************************************
    Texture2D volumen[7];
    volumen[0] = LoadTexture("texturas\\vol0.png");
    volumen[1] = LoadTexture("texturas\\vol1.png");
    volumen[2] = LoadTexture("texturas\\vol2.png");
    volumen[3] = LoadTexture("texturas\\vol3.png");
    volumen[4] = LoadTexture("texturas\\vol4.png");
    volumen[5] = LoadTexture("texturas\\vol5.png");
    volumen[6] = LoadTexture("texturas\\vol6.png");

    Texture2D dif[3];
    dif[0] = LoadTexture("texturas\\dif1.png");
    dif[1] = LoadTexture("texturas\\dif2.png");
    dif[2] = LoadTexture("texturas\\dif3.png");

    Texture2D back = LoadTexture("texturas/parallax-space-backgound.png");
    Texture2D bigplanet = LoadTexture("texturas/parallax-space-big-planet.png");
    Texture2D farplanet = LoadTexture("texturas/parallax-space-far-planets.png");
    Texture2D ringplanet = LoadTexture("texturas/parallax-space-ring-planet.png");
    Texture2D stars = LoadTexture("texturas/parallax-space-stars.png");

    //******************************************************* AUDIOS **********************************************************************
    InitAudioDevice();
    Music musica_menu = LoadMusicStream("sonidos/musica.mp3");
    Sound barras = LoadSound("sonidos/beep.mp3");
    Sound seleccion = LoadSound("sonidos/volumen.mp3");

    //************************************************************* LOOP PRINCIPAL ****************************************************************
    while (!WindowShouldClose())
    {
        // Menu principal
        PlayMusicStream(musica_menu);
        do
        {
        menu:
            scrollingBack -= 0.01f;
            scrollingBigPlanet -= 0.025f;
            scrollingFarPlanet -= 0.05f;
            scrollingRingPlanet -= 0.055f;
            scrollingSpaceStar -= 0.01;

            if (scrollingBack <= -back.height)
                scrollingBack = 0;
            if (scrollingBigPlanet <= -bigplanet.height)
                scrollingBigPlanet = 0;
            if (scrollingFarPlanet <= -farplanet.height)
                scrollingFarPlanet = 0;
            if (scrollingRingPlanet <= -ringplanet.height)
                scrollingRingPlanet = 0;
            if (scrollingSpaceStar <= -stars.height)
                scrollingSpaceStar = 0;

            BeginDrawing();
            UpdateMusicStream(musica_menu);

            DrawTextureEx(back, (Vector2){0, scrollingBack}, 0.0f, 1.0f, WHITE);
            DrawTextureEx(back, (Vector2){0, back.height * 2 + scrollingBack}, 0.0f, 1.0f, WHITE);

            DrawTextureEx(bigplanet, (Vector2){900, scrollingBigPlanet}, 0.0f, 1.0f, WHITE);
            DrawTextureEx(bigplanet, (Vector2){900, bigplanet.height * 2 + scrollingBigPlanet}, 0.0f, 1.0f, WHITE);

            DrawTextureEx(farplanet, (Vector2){0, scrollingFarPlanet}, 0.0f, 1.0f, WHITE);
            DrawTextureEx(farplanet, (Vector2){0, farplanet.height * 2 + scrollingFarPlanet}, 0.0f, 1.0f, WHITE);

            DrawTextureEx(ringplanet, (Vector2){0, scrollingRingPlanet}, 0.0f, 1.0f, WHITE);
            DrawTextureEx(ringplanet, (Vector2){0, ringplanet.height * 2 + scrollingRingPlanet}, 0.0f, 1.0f, WHITE);

            DrawTextureEx(stars, (Vector2){0, scrollingSpaceStar}, 0.0f, 1.0f, WHITE);
            DrawTextureEx(stars, (Vector2){0, stars.height * 2 + scrollingSpaceStar}, 0.0f, 1.0f, WHITE);

            op = mainMenu(seleccion);
            EndDrawing();
        } while (op == -1);

        //******************************************** JUGAR ******************************************************************
        switch (op)
        {
        case JUGAR:
            do
            {
                BeginDrawing();
                UpdateMusicStream(musica_menu);
                scrollingBack -= 0.01f;
                scrollingBigPlanet -= 0.025f;
                scrollingFarPlanet -= 0.05f;
                scrollingRingPlanet -= 0.055f;
                scrollingSpaceStar -= 0.01;

                if (scrollingBack <= -back.height)
                    scrollingBack = 0;
                if (scrollingBigPlanet <= -bigplanet.height)
                    scrollingBigPlanet = 0;
                if (scrollingFarPlanet <= -farplanet.height)
                    scrollingFarPlanet = 0;
                if (scrollingRingPlanet <= -ringplanet.height)
                    scrollingRingPlanet = 0;
                if (scrollingSpaceStar <= -stars.height)
                    scrollingSpaceStar = 0;

                BeginDrawing();
                UpdateMusicStream(musica_menu);

                DrawTextureEx(back, (Vector2){0, scrollingBack}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(back, (Vector2){0, back.height * 2 + scrollingBack}, 0.0f, 1.0f, WHITE);

                DrawTextureEx(bigplanet, (Vector2){900, scrollingBigPlanet}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(bigplanet, (Vector2){900, bigplanet.height * 2 + scrollingBigPlanet}, 0.0f, 1.0f, WHITE);

                DrawTextureEx(farplanet, (Vector2){0, scrollingFarPlanet}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(farplanet, (Vector2){0, farplanet.height * 2 + scrollingFarPlanet}, 0.0f, 1.0f, WHITE);

                DrawTextureEx(ringplanet, (Vector2){0, scrollingRingPlanet}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(ringplanet, (Vector2){0, ringplanet.height * 2 + scrollingRingPlanet}, 0.0f, 1.0f, WHITE);

                DrawTextureEx(stars, (Vector2){0, scrollingSpaceStar}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(stars, (Vector2){0, stars.height * 2 + scrollingSpaceStar}, 0.0f, 1.0f, WHITE);

                opJug = juegoMenu(seleccion);
                EndDrawing();
            } while (opJug == -1);

            switch (opJug)
            {
            case NEWP:
                goto juegoL;
                break;
            case REGRESAR:
                UpdateMusicStream(musica_menu);
                goto menu;
                break;
            }
            break;

            //**************************** OPCIONES ******************************************************************
        case OPCIONES:
            UpdateMusicStream(musica_menu);
            do
            {
                BeginDrawing();
                UpdateMusicStream(musica_menu);
                scrollingBack -= 0.01f;
                scrollingBigPlanet -= 0.025f;
                scrollingFarPlanet -= 0.05f;
                scrollingRingPlanet -= 0.055f;
                scrollingSpaceStar -= 0.01;

                if (scrollingBack <= -back.height)
                    scrollingBack = 0;
                if (scrollingBigPlanet <= -bigplanet.height)
                    scrollingBigPlanet = 0;
                if (scrollingFarPlanet <= -farplanet.height)
                    scrollingFarPlanet = 0;
                if (scrollingRingPlanet <= -ringplanet.height)
                    scrollingRingPlanet = 0;
                if (scrollingSpaceStar <= -stars.height)
                    scrollingSpaceStar = 0;

                BeginDrawing();
                UpdateMusicStream(musica_menu);

                DrawTextureEx(back, (Vector2){0, scrollingBack}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(back, (Vector2){0, back.height * 2 + scrollingBack}, 0.0f, 1.0f, WHITE);

                DrawTextureEx(bigplanet, (Vector2){900, scrollingBigPlanet}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(bigplanet, (Vector2){900, bigplanet.height * 2 + scrollingBigPlanet}, 0.0f, 1.0f, WHITE);

                DrawTextureEx(farplanet, (Vector2){0, scrollingFarPlanet}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(farplanet, (Vector2){0, farplanet.height * 2 + scrollingFarPlanet}, 0.0f, 1.0f, WHITE);

                DrawTextureEx(ringplanet, (Vector2){0, scrollingRingPlanet}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(ringplanet, (Vector2){0, ringplanet.height * 2 + scrollingRingPlanet}, 0.0f, 1.0f, WHITE);

                DrawTextureEx(stars, (Vector2){0, scrollingSpaceStar}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(stars, (Vector2){0, stars.height * 2 + scrollingSpaceStar}, 0.0f, 1.0f, WHITE);
                subOp = opMenu(vol, diflvl, volumen[vol], dif[diflvl], seleccion, barras);
                EndDrawing();

            } while (subOp != -1);
            goto menu;
            break;

            //**************************** SALIR ******************************************************************
        case SALIR:
            CloseWindow();
            return 0;
            break;
        }

    juegoL:
        do
        {
            juego(diflvl);
        } while (0);

    continuar:
        do
        {
            juego(diflvl);
        } while (0);
    }

    //*********************************************************** UNLOAD ******************************************************************
    StopMusicStream(musica_menu);
    UnloadTexture(volumen[0]);
    UnloadTexture(volumen[1]);
    UnloadTexture(volumen[2]);
    UnloadTexture(volumen[3]);
    UnloadTexture(volumen[4]);
    UnloadTexture(volumen[5]);
    UnloadTexture(volumen[6]);
    UnloadTexture(dif[0]);
    UnloadTexture(dif[1]);
    UnloadTexture(dif[2]);
    UnloadMusicStream(musica_menu);
    UnloadSound(seleccion);
    CloseAudioDevice();
    CloseWindow();
    //*****************************************************************************************************************************

    return 0;
}

int mainMenu(Sound seleccion)
{
    static int op = 0;
    int sizeTxt[3], j;
    int fontSize[2] = {70, 40};

    char mensajes[4][30] = {"JUGAR", "OPCIONES", "SALIR", "MECANICO ARITMETICO"};
    Rectangle fondo[4];

    fondo[3] = {170, 45, 927, 90};
    DrawRectangleRec(fondo[3], GetColor(0x03D1339));
    DrawText(mensajes[3], 200, 55, 70, WHITE);

    fondo[0] = {500, 293, 200, 50};
    DrawRectangleRec(fondo[0], GetColor(0x03D1339));
    DrawText(mensajes[0], 535, 300, 40, WHITE);

    fondo[1] = {500, 440, 200, 50};
    DrawRectangleRec(fondo[1], GetColor(0x03D1339));
    DrawText(mensajes[1], 507, 450, 37, WHITE);

    fondo[2] = {500, 590, 200, 50};
    DrawRectangleRec(fondo[2], GetColor(0x03D1339));
    DrawText(mensajes[2], 535, 598, 40, WHITE);

    for (j = 0; j < 3; j++)
    {
        if (j == op)
        {
            DrawRectangleRec(fondo[j], GetColor(0x0CB4C11));
            if (j == 0)
            {
                DrawText(mensajes[0], 535, 300, 40, WHITE);
            }
            if (j == 1)
            {
                DrawText(mensajes[1], 507, 450, 37, WHITE);
            }
            if (j == 2)
            {
                DrawText(mensajes[2], 535, 598, 40, WHITE);
            }
        }
        else
        {
            DrawRectangleRec(fondo[j], GetColor(0x03D1339));
            if (j == 0)
            {
                DrawText(mensajes[0], 535, 300, 40, WHITE);
            }
            if (j == 1)
            {
                DrawText(mensajes[1], 507, 450, 37, WHITE);
            }
            if (j == 2)
            {
                DrawText(mensajes[2], 535, 598, 40, WHITE);
            }
        }
    }

    if (IsKeyPressed(KEY_UP))
    {
        if (op != JUGAR)
        {
            op--;
        }
    }
    else
    {
        if (IsKeyPressed(KEY_DOWN))
        {
            if (op != SALIR)
            {
                op++;
            }
        }
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        PlaySound(seleccion);
        return op;
    }

    return -1;
}

int opMenu(int &vol, int &diflvl, Texture2D volumen, Texture2D dif, Sound seleccion, Sound barras)
{
    static int op = 0;
    int sizeTxt[3], j;
    for (j = 0; j < 3; j++)
    {
        if (j == op)
        {
            sizeTxt[j] = 60;
        }
        else
        {
            sizeTxt[j] = 40;
        }
    }

    char mensajes[4][30] = {"DIFICULTAD", "SONIDO", "REGRESAR", "OPCIONES"};
    Rectangle fondo[4];

    fondo[3] = {170, 45, 927, 90};
    DrawRectangleRec(fondo[3], GetColor(0x03D1339));
    DrawText(mensajes[3], 432, 55, 70, WHITE);

    fondo[0] = {500, 293, 200, 50};
    DrawRectangleRec(fondo[0], GetColor(0x03D1339));
    DrawText(mensajes[0], 476, 300, 40, WHITE);

    fondo[1] = {500, 440, 200, 50};
    DrawRectangleRec(fondo[1], GetColor(0x03D1339));
    DrawText(mensajes[1], 529, 450, 37, WHITE);

    fondo[2] = {500, 590, 200, 50};
    DrawRectangleRec(fondo[2], GetColor(0x03D1339));
    DrawText(mensajes[2], 490, 598, 40, WHITE);

    for (j = 0; j < 3; j++)
    {
        if (j == op)
        {
            DrawRectangleRec(fondo[j], GetColor(0x0CB4C11));
            if (j == 0)
            {
                DrawText(mensajes[0], 476, 300, 40, WHITE);
            }
            if (j == 1)
            {
                DrawText(mensajes[1], 529, 450, 37, WHITE);
            }
            if (j == 2)
            {
                DrawText(mensajes[2], 490, 598, 40, WHITE);
            }
        }
        else
        {
            DrawRectangleRec(fondo[j], GetColor(0x03D1339));
            if (j == 0)
            {
                DrawText(mensajes[0], 476, 300, 40, WHITE);
            }
            if (j == 1)
            {
                DrawText(mensajes[1], 529, 450, 37, WHITE);
            }
            if (j == 2)
            {
                DrawText(mensajes[2], 490, 598, 40, WHITE);
            }
        }
    }

    switch (op)
    {
    case DIFICULTAD:
        DrawTexture(dif, 520, -125 + 100, WHITE);

        if (IsKeyPressed(KEY_LEFT))
        {
            if (diflvl != 0)
            {
                diflvl--;
                PlaySound(barras);
            }
        }
        else
        {
            if (IsKeyPressed(KEY_RIGHT))
            {
                if (diflvl != 2)
                {
                    diflvl++;
                    PlaySound(barras);
                }
            }
        }

        switch (diflvl)
        {
        case 0:
            DrawText("FACIL", 862, 100 + 150, 40, WHITE);
            break;
        case 1:
            DrawText("NORMAL", 853, 100 + 150, 40, WHITE);
            break;
        case 2:
            DrawText("DIFICL", 856, 100 + 150, 40, WHITE);
            break;
        }

        break;

    case SONIDO:
        DrawTexture(volumen, 485, 25 + 100, WHITE);

        if (IsKeyPressed(KEY_LEFT))
        {
            if (vol != 0)
            {
                vol--;
                PlaySound(barras);
            }
        }
        else
        {
            if (IsKeyPressed(KEY_RIGHT))
            {
                if (vol != 6)
                {
                    vol++;
                    PlaySound(barras);
                }
            }
        }

        break;

    case REGRESAR:
        if (IsKeyPressed(KEY_ENTER))
        {
            PlaySound(seleccion);
            return -1;
        }
        break;
    }

    if (IsKeyPressed(KEY_UP))
    {
        if (op != DIFICULTAD)
        {
            op--;
        }
    }
    else
    {
        if (IsKeyPressed(KEY_DOWN))
        {
            if (op != REGRESAR)
            {
                op++;
            }
        }
    }

    return op;
}

int juegoMenu(Sound seleccion)
{
    static int op = 0;
    int sizeTxt[3], j;

    char mensajes[3][30] = {"NUEVA PARTIDA", "REGRESAR", "MECANICO ARITMETICO"};
    Rectangle fondo[3];

    fondo[2] = {170, 45, 927, 90};
    DrawRectangleRec(fondo[2], GetColor(0x03D1339));
    DrawText(mensajes[2], 200, 55, 70, WHITE);

    fondo[0] = {500, 293, 200, 50};
    DrawRectangleRec(fondo[0], GetColor(0x03D1339));
    DrawText(mensajes[0], 423, 300, 40, WHITE);

    fondo[1] = {500, 440, 200, 50};
    DrawRectangleRec(fondo[1], GetColor(0x03D1339));
    DrawText(mensajes[1], 490, 450, 40, WHITE);

    for (j = 0; j < 2; j++)
    {
        if (j == op)
        {
            DrawRectangleRec(fondo[j], GetColor(0x0CB4C11));
            if (j == 0)
            {
                DrawText(mensajes[0], 423, 300, 40, WHITE);
            }
            if (j == 1)
            {
                DrawText(mensajes[1], 490, 450, 40, WHITE);
            }
        }
        else
        {
            DrawRectangleRec(fondo[j], GetColor(0x03D1339));
            if (j == 0)
            {
                DrawText(mensajes[0], 423, 300, 40, WHITE);
            }
            if (j == 1)
            {
                DrawText(mensajes[1], 490, 450, 40, WHITE);
            }
        }
    }

    if (IsKeyPressed(KEY_UP))
    {
        if (op != NEWP)
        {
            op--;
        }
    }
    else
    {
        if (IsKeyPressed(KEY_DOWN))
        {
            if (op != SALIRJ)
            {
                op++;
            }
        }
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        PlaySound(seleccion);
        return op;
    }

    return -1;
}

void juego(int diflvl)
{
    nivel1(diflvl);
    nivel2(diflvl);

}

void nivel1(int diflvl)
{
    float VDDIAGONAL = VD1 * sin(45) / sin(90);
    SetTargetFPS(60);
    InitWindow(RANCHO, RALTO, "iuego");
    srand(time(NULL));
    int i, j, k;
    Tplayer player;
    player.pos.height = ALTOP;
    player.pos.width = ANCHOP;
    player.pos.x = RANCHO / 2;
    player.pos.y = SUELO - player.pos.height;
    player.dash = 0;
    player.timeDash = 0;
    player.x0 = player.pos.x;
    player.AtkC = 0;

    // vida
    player.vida.num = MAXVIDA;
    player.vida.pos.width = 25;
    player.vida.pos.height = 25;
    player.vida.pos.x = 25;
    player.vida.pos.y = 25;

    // AtkSpeed
    player.buff = 0;

    int lookR = 1;
    int lookL = 0;
    int lookUp = 0;
    int lookDown = 0;
    int fin = 0;
    int random;
    int disparo=0;
    int framesAutom = 0;
    int framesPersonaje = 0;

    int framesSpeed = 8;

    int currentFrame = 0;
    int currentPersonaje = 0;

    int framesAtaque = 0;
    int currentAtaque = 0;

    int framesSalto=0;
    int currentSalto=0;
    // ********************************** TEXTURAS **************************************************
    Texture2D tortuga = LoadTexture("texturas/tortuga_der1.png");
    Rectangle framesTortuga = {0.0f, 0.0f, (float)tortuga.width / 6, (float)tortuga.height};

    Texture2D tortugaizq = LoadTexture("texturas/tortuga_izq.png");
    Rectangle framesTortugaizq = {0.0f, 0.0f, (float)tortugaizq.width / 6, (float)tortugaizq.height};

    Texture2D anguila = LoadTexture("texturas/anguila.png");
    Rectangle framesAnguila = {0.0f, 0.0f, (float)anguila.width / 6, (float)anguila.height};

    Texture2D anguilaizq = LoadTexture("texturas/anguila_izq.png");
    Rectangle framesAnguilaizq = {0.0f, 0.0f, (float)anguilaizq.width / 6, (float)anguilaizq.height};

    Texture2D ataque_anizq = LoadTexture("texturas/ataqueizq.png");
    Rectangle framesAtaque_anizq = {0.0f, 0.0f, (float)ataque_anizq.width / 6, (float)ataque_anizq.height};

    Texture2D ataque_ani = LoadTexture("texturas/ataqueizq.png");
    Rectangle framesAtaque_ani = {0.0f, 0.0f, (float)ataque_ani.width / 6, (float)ataque_ani.height};

    Texture2D pulpo = LoadTexture("texturas/pulpo.png");
    Rectangle framesPulpo = {0.0f, 0.0f, (float)pulpo.width / 6, (float)pulpo.height};

    Texture2D pulpoizq = LoadTexture("texturas/pulpoizq.png");
    Rectangle framesPulpoizq = {0.0f, 0.0f, (float)pulpoizq.width / 6, (float)pulpoizq.height};

    Texture2D caminar = LoadTexture("texturas/Cyborg_run.png");
    Rectangle framesCaminar = {0.0f, 0.0f, (float)caminar.width / 6, (float)caminar.height};
    Texture2D caminarizq = LoadTexture("texturas/Cyborg_run_left.png");
    Rectangle framesCaminarizq = {0.0f, 0.0f, (float)caminarizq.width / 6, (float)caminarizq.height};
    Texture2D reposo = LoadTexture("texturas/Cyborg_idle.png");
    Rectangle framesReposo = {0.0f, 0.0f, (float)reposo.width / 4, (float)reposo.height};
    Texture2D reposoizq = LoadTexture("texturas/Cyborg_idle_left.png");
    Rectangle framesReposoizq = {0.0f, 0.0f, (float)reposoizq.width / 4, (float)reposoizq.height};
    Texture2D danio = LoadTexture("texturas/Cyborg_hurt.png");
    Rectangle framesDanio = {0.0f, 0.0f, (float)danio.width, (float)danio.height};
    Texture2D salto = LoadTexture("texturas/Cyborg_jump.png");
    Rectangle frameSalto = {0.0f, 0.0f, (float)salto.width / 4, (float)salto.height};
    Texture2D saltoder = LoadTexture("texturas/Cyborg_jumpr.png");
    Rectangle frameSaltoder = {0.0f, 0.0f, (float)saltoder.width / 4, (float)saltoder.height};

    Texture2D back_nv1 = LoadTexture("texturas/back_nv1.png");
    Texture2D backmiddle_nv1 = LoadTexture("texturas/middleback_nv1.png");
    Texture2D middle_nv1 = LoadTexture("texturas/middle_mv1.png");
    Texture2D front_nv1 = LoadTexture("texturas/front_nv1.png");

    Texture2D plataforma_nv1 = LoadTexture("texturas/plataforma_nv1_1.png");

    Texture2D bullet_nv1 = LoadTexture("texturas/bullet_nv1.png");

    Texture2D corazon = LoadTexture("texturas\\corazon.png");
    Texture2D Aspeed=LoadTexture("texturas\\AtkSpeed.png");

    Texture2D ataquesizquierdos[5];
    Texture2D ataquesderechos[5];

    ataquesizquierdos[0] = LoadTexture("texturas/HitL0.png");
    ataquesizquierdos[1] = LoadTexture("texturas/HitL1.png");
    ataquesizquierdos[2] = LoadTexture("texturas/HitL2.png");
    ataquesizquierdos[3] = LoadTexture("texturas/HitL3.png");
    ataquesizquierdos[4] = LoadTexture("texturas/HitL4.png");

    ataquesderechos[0] = LoadTexture("texturas/HitR0.png");
    ataquesderechos[1] = LoadTexture("texturas/HitR1.png");
    ataquesderechos[2] = LoadTexture("texturas/HitR2.png");
    ataquesderechos[3] = LoadTexture("texturas/HitR3.png");
    ataquesderechos[4] = LoadTexture("texturas/HitR4_1.png");

    Texture2D piezas_nv1[3];
    piezas_nv1[0] = LoadTexture("texturas/pieza1_nv1.png");
    piezas_nv1[1] = LoadTexture("texturas/pieza2_nv1.png");
    piezas_nv1[2] = LoadTexture("texturas/pieza3_nv1.png");

    // ************************************************ SONIDOS ********************************************************************

    InitAudioDevice();

    Sound dolor = LoadSound("sonidos/danio.wav");
    Sound brinco = LoadSound("sonidos/salto.mp3");
    Sound paso = LoadSound("sonidos/paso1.wav");
    Sound agarrar = LoadSound("sonidos/pieza.wav");
    Music musica_nv1 = LoadMusicStream("sonidos/nivel1.mp3");
    Sound sdash = LoadSound("sonidos/paso1.wav");
    Sound disparo_nv1 = LoadSound("sonidos/disparo_nv1.wav");
    Sound ludico = LoadSound("sonidos/nivel_completado.wav");
    Sound anguilasound = LoadSound("sonidos/anguilasound.wav");

    SetSoundVolume(disparo_nv1, -0.1f);
    SetSoundVolume(sdash, +10.0f);
    SetMusicVolume(musica_nv1, -1.2f);

    //** proyectil ************************************************************************************************************************
    Thit hit[MAXHIT1];
    for (i = 0; i < MAXHIT1; i++)
    {
        hit[i].status = 0;
        hit[i].pos.width = bullet_nv1.width;
        hit[i].pos.height = bullet_nv1.height;
        hit[i].pos.x = 1280;
        hit[i].pos.y = 1500;
    }

    //** plataformas **************************************************************************************************************************
    Trec plat[MAXPLAT1];
    for (i = 0; i < MAXPLAT1; i++)
    {
        plat[i].height = plataforma_nv1.height;
        plat[i].width = plataforma_nv1.width;
    }
    plat[0].x = 100;
    plat[0].y = 200;
    plat[1].x = RANCHO / 2 - plat[1].width / 2;
    plat[1].y = 400;
    plat[2].x = RANCHO - 100 - plat[2].width;
    plat[2].y = 200;

    //** piezas **********************************************************************************************************************************
    int time = 0;
    Tpart pieza[3];
    int piezac = 0;
    pieza[0].pos.height = piezas_nv1[0].height;
    pieza[0].pos.width = piezas_nv1[0].width;
    pieza[1].pos.height = piezas_nv1[1].height;
    pieza[1].pos.width = piezas_nv1[1].width;
    pieza[2].pos.height = piezas_nv1[2].height;
    pieza[2].pos.width = piezas_nv1[2].width;
    for (j = 0; j < 3; j++)
    {
        pieza[j].status = 0;
        pieza[j].status = 1;
        pieza[j].pos.x = plat[j].x + plat[j].width / 2 - pieza[j].pos.width / 2;
        pieza[j].pos.y = -300;
        pieza[j].listo = 0;
    }

    //** enemigos **********************************************************************************************************************************
    Tshark shark[MAXSHARK];
    for (i = 0; i < MAXSHARK; i++)
    {
        shark[i].status = 0;
        shark[i].right = 0;
        shark[i].left = 0;
        shark[i].pos.x = 2000;
        shark[i].pos.y = 800;
        shark[i].pos.height = 100;
        shark[i].pos.width = 120;
    }

    Ttortu tort[MAXTORTUGA];
    for (i = 0; i < MAXTORTUGA; i++)
    {
        tort[i].status = 0;
        tort[i].pos.x = 2000;
        tort[i].pos.y = 800;
        tort[i].pos.height = tortuga.height - 100;
        tort[i].pos.width = (tortuga.width / 6) - 40;
    }
    tort[0].left = 1;
    tort[0].right = 0;
    tort[1].right = 1;
    tort[1].left = 0;

    Tangui ang[MAXANGUILA];
    for (i = 0; i < MAXANGUILA; i++)
    {
        ang[i].status = 0;
        ang[i].right = 0;
        ang[i].left = 0;
        ang[i].pos.x = 2000;
        ang[i].pos.y = 800;
        ang[i].pos.height = anguila.height - 65;
        ang[i].pos.width = (anguila.width / 6) - 20;
        ang[i].hit.pos.height = ang[0].pos.height * 3;
        ang[i].hit.pos.width = ang[0].pos.width * 1.5;
        ang[i].hit.pos.y = 800;
        ang[i].hit.pos.x = 2000;
        ang[i].hit.status = 0;
        ang[i].hit.time = 0;
    }

    // drop
    Tcora dropVida[MAXDROPVIDA];

    for (i = 0; i < MAXDROPVIDA; i++)
    {
        dropVida[i].pos.width = 30;
        dropVida[i].pos.height = 30;
        dropVida[i].status = 0;
        dropVida[i].time = 0;
    }

    TatkSpeed dropASpeed[MAXDROPASPEED];
    for (i = 0; i < MAXDROPASPEED; i++)
    {
        dropASpeed[i].pos.width = 80;
        dropASpeed[i].pos.height = 60;
        dropASpeed[i].statusDraw = 0;
        dropASpeed[i].statusFun = 0;
        dropASpeed[i].time = 0;
        dropASpeed[i].duracion = DURACIONBUFF;
    }

    // Inicializacion camara
    Camera2D camara = {0};
    camara.target.x = 0;
    camara.target.y = 0;
    camara.offset.x = 0;
    camara.offset.y = 0;
    camara.rotation = 0;
    camara.zoom = 1;

    while (!WindowShouldClose())
    {
        // printf("x = %f y = %f\n",player.pos.x,player.pos.y);
        player.timeDash++;
        player.AtkC++;
        time++;
        player.vida.time++;
        if(player.AtkC>20)
        {
            disparo=0;
        }
        BeginDrawing();

        BeginMode2D(camara);
        DrawRectangleRec(player.pos, DARKBLUE);
        DrawTexture(back_nv1, 0, 0, WHITE);
        DrawTexture(backmiddle_nv1, 0, 0, WHITE);
        DrawTexture(middle_nv1, 0, 0, WHITE);
        DrawTexture(front_nv1, 0, 0, WHITE);

        PlayMusicStream(musica_nv1);
        UpdateMusicStream(musica_nv1);

        //** terminar el nivel ***********************************************************************************
        if (pieza[0].status)
        {
            if (pieza[0].pos.y == SUELO - pieza[0].pos.height)
            {
                if (pieza[1].status)
                {
                    if (pieza[1].pos.y == SUELO - pieza[1].pos.height - 5)
                    {
                        if (pieza[2].status)
                        {
                            if (pieza[2].pos.y == SUELO - pieza[2].pos.height - 8)
                            {
                                if (!fin)
                                {
                                    PlaySound(ludico);
                                    time = 0;
                                }
                                fin = 1;
                                LimpiaEnemigosLvl1(shark, tort, ang);
                                if (time > 300)
                                {
                                    cinemaPuzleNivel1(diflvl);
                                    goto finNivel1;
                                }
                                
                            }
                        }
                    }
                }
            }
        }

        //if (!fin)
        {
            // reaiusta posicion si sale de limites *********************************************************************************************
            if (player.pos.y < 25)
            {
                player.pos.y = 25;
            }
            else
            {
                if (player.pos.y > SUELO - player.pos.height)
                {
                    player.pos.y = SUELO - player.pos.height;
                }
                else
                {
                    if (player.pos.x < 0)
                    {
                        player.pos.x = 0;
                    }
                    else
                    {
                        if (player.pos.x > RANCHO - player.pos.width)
                        {
                            player.pos.x = RANCHO - player.pos.width;
                        }
                    }
                }
            }

            //** piezas ****************************************************************************************************************************
            for (j = 0; j < 3; j++)
            {
                //drop
                if(pieza[j].listo)
                {
                    if(!pieza[j].status)
                    {
                        if(CheckPlayerColision(player.pos,pieza[j].pos))
                        {
                            pieza[j].status=1;
                        }
                    }
                }

                //recolleccion
                if(!pieza[j].listo)
                {
                    if(pieza[j].status)
                    {
                        if(CheckPlayerColision(player.pos,pieza[j].pos))
                        {
                            PlaySound(agarrar);
                            pieza[j].status=0;
                            pieza[j].listo=1;
                            pieza[j].pos.y=SUELO-pieza[j].pos.height;
                            piezac++;
                            switch(j)
                            {
                               case 0:
                                pieza[j].pos.x = 900;
                                break;
                                case 1:
                                    pieza[j].pos.x = 980;
                                    pieza[j].pos.y -= 5;
                                    break;
                                case 2:
                                    pieza[j].pos.x = 1055;
                                    pieza[j].pos.y -= 8;
                                    break;
                            }
                            j=3;
                        }
                    }
                }  
            }

            // movimiento piezas
            if (time > 600)
            {
                if (!pieza[0].listo)
                {
                    if (pieza[0].pos.y < plat[0].y - pieza[0].pos.height)
                    {
                        pieza[0].pos.y += 4;
                    }
                    else
                    {
                        if (piezac < 1)
                        {
                            pieza[0].pos.y = plat[0].y - pieza[0].pos.height;
                        }
                    }
                }
                if (time > 1200)
                {
                    if (!pieza[1].listo)
                    {
                        if (pieza[1].pos.y < plat[1].y - pieza[1].pos.height)
                        {
                            pieza[1].pos.y += 4;
                        }
                        else
                        {
                            if (piezac < 2)
                            {
                                pieza[1].pos.y = plat[1].y - pieza[1].pos.height;
                            }
                        }
                    }

                    if (time > 1800)
                    {
                        if (!pieza[2].listo)
                        {
                            if (pieza[2].pos.y < plat[2].y - pieza[2].pos.height)
                            {
                                pieza[2].pos.y += 4;
                            }
                            else
                            {
                                if (piezac < 3)
                                {
                                    pieza[2].pos.y = plat[2].y - pieza[2].pos.height;
                                }
                            }
                        }
                    }
                }
            }

            //** DROPS ************************************************************************************************************************
            for (i = 0; i < MAXDROPVIDA; i++)
            {
                if (dropVida[i].status)
                {
                    // tiempo
                    dropVida[i].time++;
                    // eliminacion
                    if (dropVida[i].time > DESPAWNTIME)
                    {
                        dropVida[i].status = 0;
                        dropVida[i].time = 0;
                    }

                    // curacion
                    if (CheckPlayerColision(player.pos, dropVida[i].pos))
                    {
                        player.vida.num++;
                        dropVida[i].status = 0;
                        dropVida[i].time = 0;
                    }
                    else
                    {
                        // movimiento
                        if (dropVida[i].pos.y < SUELO - dropVida[i].pos.height)
                        {
                            dropVida[i].pos.y += 2;
                        }
                        else
                        {
                            dropVida[i].pos.y = SUELO - dropVida[i].pos.height;
                        }
                    }
                }
            }

            for (i = 0; i < MAXDROPASPEED; i++)
            {
                if (dropASpeed[i].statusDraw)
                {
                    // tiempo
                    dropASpeed[i].time++;
                    // eliminacion
                    if (!dropASpeed[i].statusFun)
                    {
                        if (dropASpeed[i].time > DESPAWNTIME)
                        {
                            dropASpeed[i].statusDraw = 0;
                            dropASpeed[i].statusFun = 0;
                            dropASpeed[i].time = 0;
                        }
                        if (CheckPlayerColision(player.pos, dropASpeed[i].pos))
                        {
                            player.buff = 1;
                            dropASpeed[i].statusDraw = 0;
                            dropASpeed[i].statusFun = 1;
                            dropASpeed[i].time = 0;
                            dropASpeed[i].duracion = 0;
                        }
                        else
                        {
                            // movimiento
                            if (dropASpeed[i].pos.y < SUELO - dropASpeed[i].pos.height * 3)
                            {
                                dropASpeed[i].pos.y += 1;
                            }
                            else
                            {
                                dropASpeed[i].pos.y = SUELO - dropASpeed[i].pos.height * 3;
                            }
                        }
                    }
                }
                else
                {
                    if (player.buff)
                    {
                        if (dropASpeed[i].statusFun)
                        {
                            if (dropASpeed[i].duracion < DURACIONBUFF)
                            {
                                dropASpeed[i].duracion++;
                            }
                            else
                            {
                                player.buff = 0;
                                dropASpeed[i].statusFun = 0;
                                dropASpeed[i].statusDraw = 0;
                                dropASpeed[i].time = 0;
                                dropASpeed[i].duracion = 0;
                            }
                        }
                    }
                }
            }

            //** enemigos **
            //** tiburones ******************************************************************************************************************************
            for (i = 0; i < MAXSHARK; i++)
            {
                // comportameinto
                if (shark[i].status)
                {
                    // movimiento enemigo **si sale de la pantalla se elimina**
                    if (shark[i].right)
                    { // movimiento
                        if (shark[i].pos.y < 75)
                        {
                            shark[i].pos.x -= SHARKSPEED;
                        }
                        else
                        {
                            if (shark[i].pos.y > SUELO - 50 - shark[i].pos.height)
                            {
                                shark[i].pos.x -= SHARKSPEED;
                            }
                            else
                            {
                                PosicionObieto3(shark[i].v.vx, shark[i].v.vy, shark[i].pos);
                            }
                        }

                        // eliminacion
                        if (shark[i].pos.x < 0 - shark[i].pos.width)
                        {
                            shark[i].status = 0;
                        }
                    }
                    else
                    {
                        if (shark[i].left)
                        { // movimiento
                            if (shark[i].pos.y < 75)
                            {
                                shark[i].pos.x += SHARKSPEED;
                            }
                            else
                            {
                                if (shark[i].pos.y > SUELO - 50 - shark[i].pos.height)
                                {
                                    shark[i].pos.x += SHARKSPEED;
                                }
                                else
                                {
                                    PosicionObieto3(shark[i].v.vx, shark[i].v.vy, shark[i].pos);
                                }
                            }
                            // eliminacion
                            if (shark[i].pos.x > RANCHO + shark[i].pos.width)
                            {
                                shark[i].status = 0;
                            }
                        }
                    }

                    // Colision con golpe
                    if (hit)
                    {
                        for (j = 0; j < MAXHIT1; j++)
                        {
                            if (CheckMobColision(shark[i].pos, hit[j]))
                            {
                                shark[i].status = 0;
                                random = rand() % 10 + 1;
                                if (random <= 4)
                                {
                                    random = rand() % 2;
                                    if (random)
                                    {
                                        for (k = 0; k < MAXDROPVIDA; k++)
                                        {
                                            if (!dropVida[k].status)
                                            {
                                                dropVida[k].status = 1;
                                                dropVida[k].time = 0;
                                                dropVida[k].pos.x = shark[i].pos.x;
                                                dropVida[k].pos.y = shark[i].pos.y;
                                                k = MAXDROPVIDA;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        for (k = 0; k < MAXDROPASPEED; k++)
                                        {
                                            if (!dropASpeed[k].statusDraw)
                                            {
                                                if (!dropASpeed[k].statusFun)
                                                {
                                                    dropASpeed[k].statusDraw = 1;
                                                    dropASpeed[k].statusFun = 0;
                                                    dropASpeed[k].time = 0;
                                                    dropASpeed[k].pos.x = shark[i].pos.x;
                                                    dropASpeed[k].pos.y = shark[i].pos.y;
                                                    k = MAXDROPASPEED;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // Colision con iugador
                    if (shark[i].status)
                    {
                        if (player.vida.time > INVULERABILIDAD)
                        {
                            if (CheckPlayerColision(player.pos, shark[i].pos))
                            {
                                PlaySound(dolor);
                                if (player.vida.num < 1)
                                {
                                    piezac = 0;
                                    time = 0;
                                    muerteLvl1(player, shark, tort, ang, pieza, plat);
                                }
                                else
                                {
                                    player.vida.num--;
                                    player.vida.time = 0;
                                }
                                i = MAXSHARK;
                            }
                        }
                    }
                }
                else
                {
                    // generacion
                    random = (rand() % 50) + 1;
                    if (random == 1)
                    {
                        shark[i].right = rand() % 2;
                        random = rand() % 30;
                        if (shark[i].right)
                        {
                            shark[i].status = 1;
                            CalculaComponentesVelocidad(SHARKSPEED, float(random + 165), shark[i].v);
                            shark[i].pos.x = RANCHO;
                            shark[i].pos.y = (rand() % 550) + 50;
                            shark[i].left = 0;
                        }
                        else
                        {
                            shark[i].status = 1;
                            CalculaComponentesVelocidad(SHARKSPEED, float(random + 345), shark[i].v);
                            shark[i].pos.x = 0 - shark[i].pos.width;
                            shark[i].pos.y = (rand() % 550) + 50;
                            shark[i].left = 1;
                        }
                    }
                }
            }

            //** tortugas ******************************************************************************************************************************
            for (i = 0; i < MAXTORTUGA; i++)
            {
                // comportameinto
                if (tort[i].status)
                {
                    // movimiento enemigo **si sale de la pantalla se elimina**
                    if (tort[i].right)
                    { // movimiento
                        tort[i].pos.x -= TORTUGASPEED;
                        if (tort[i].pos.x <= 0 - tort[i].pos.height)
                        {
                            tort[i].status = 0;
                        }
                    }
                    else
                    {
                        if (tort[i].left)
                        { // movimiento
                            tort[i].pos.x += TORTUGASPEED;
                            // eliminacion
                            if (tort[i].pos.x > RANCHO + tort[i].pos.width)
                            {
                                tort[i].status = 0;
                            }
                        }
                    }

                    // Colision con golpe
                    if (hit)
                    {
                        for (j = 0; j < MAXHIT1; j++)
                        {
                            if (CheckMobColision(tort[i].pos, hit[j]))
                            {
                                tort[i].status = 0;
                                random = rand() % 10 + 1;
                                if (random <= 4)
                                {
                                    random = rand() % 2;
                                    if (random)
                                    {
                                        for (k = 0; k < MAXDROPVIDA; k++)
                                        {
                                            if (!dropVida[k].status)
                                            {
                                                dropVida[k].status = 1;
                                                dropVida[k].time = 0;
                                                dropVida[k].pos.x = tort[i].pos.x;
                                                dropVida[k].pos.y = tort[i].pos.y;
                                                k = MAXDROPVIDA;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        for (k = 0; k < MAXDROPASPEED; k++)
                                        {
                                            if (!dropASpeed[k].statusDraw)
                                            {
                                                if (!dropASpeed[k].statusFun)
                                                {
                                                    dropASpeed[k].statusDraw = 1;
                                                    dropASpeed[k].statusFun = 0;
                                                    dropASpeed[k].time = 0;
                                                    dropASpeed[k].pos.x = tort[i].pos.x;
                                                    dropASpeed[k].pos.y = tort[i].pos.y;
                                                    k = MAXDROPASPEED;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // Colision con iugador
                    if (tort[i].status)
                    {
                        if (player.vida.time > INVULERABILIDAD)
                        {
                            if (CheckPlayerColision(player.pos, tort[i].pos))
                            {
                                PlaySound(dolor);
                                if (player.vida.num < 1)
                                {
                                    piezac = 0;
                                    time = 0;
                                    muerteLvl1(player, shark, tort, ang, pieza, plat);
                                }
                                else
                                {
                                    player.vida.num--;
                                    player.vida.time = 0;
                                }
                                i = MAXTORTUGA;
                            }
                        }
                    }
                }
                else
                {
                    // generacion
                    random = (rand() % 100) + 1;
                    if (random == 1)
                    {
                        if (tort[i].right)
                        {
                            tort[i].status = 1;
                            tort[i].pos.x = RANCHO;
                            tort[i].pos.y = (rand() % 550) + 50;
                        }
                        else
                        {
                            tort[i].status = 1;
                            tort[i].pos.x = 0 - tort[i].pos.width;
                            tort[i].pos.y = (rand() % 550) + 50;
                        }
                    }
                }
            }

            //** anguilas *********************************************************************************************************************************
            for (i = 0; i < MAXANGUILA; i++)
            {
                // comportameinto
                if (ang[i].status)
                {
                    // movimiento enemigo **si sale de la pantalla se elimina**
                    if (ang[i].right)
                    { // movimiento
                        if (ang[i].pos.y < 75)
                        {
                            ang[i].pos.x -= ANGUILASPEED;
                        }
                        else
                        {
                            if (ang[i].pos.y > SUELO - 50 - ang[i].pos.height)
                            {
                                ang[i].pos.x -= ANGUILASPEED;
                            }
                            else
                            {
                                PosicionObieto3(ang[i].v.vx, ang[i].v.vy, ang[i].pos);
                            }
                        }

                        // eliminacion
                        if (ang[i].pos.x < 0 - ang[i].pos.width)
                        {
                            ang[i].status = 0;
                            ang[i].hit.status = 0;
                        }

                        //** generacion ataque enemigo ************************************************************************************************
                        random = (rand() % 20) + 1;
                        if (random == 1)
                        {
                            if (!ang[i].hit.status)
                            {
                                if (ang[i].pos.x <= player.pos.x + player.pos.width + 200)
                                {
                                    if (ang[i].pos.x >= player.pos.x - 200)
                                    {
                                        if (ang[i].pos.y <= player.pos.y + player.pos.height + 200)
                                        {
                                            if (ang[i].pos.y >= player.pos.y - 200)
                                            {
                                                // random=rand()%MAXANGUILAHIT;
                                                AngElectro(ang[i]);
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        //** comporamiento descarga electrica ************************************************************************************
                        if (ang[i].status)
                        {
                            if (ang[i].hit.status)
                            {
                                if (ang[i].hit.time < 120)
                                {
                                    ang[i].hit.pos.y = ang[i].pos.y - ang[i].pos.height;
                                    ang[i].hit.pos.x = ang[i].pos.x - 21;
                                    ang[i].hit.time++;

                                    // colision con jugador
                                    if (player.vida.time > INVULERABILIDAD)
                                    {
                                        if (CheckPlayerColision(player.pos, ang[i].hit.pos))
                                        {
                                            PlaySound(anguilasound);
                                            if (player.vida.num < 1)
                                            {
                                                piezac = 0;
                                                time = 0;
                                                muerteLvl1(player, shark, tort, ang, pieza, plat);
                                                PlaySound(anguilasound);
                                            }
                                            else
                                            {
                                                player.vida.num--;
                                                player.vida.time = 0;
                                            }
                                            i = MAXANGUILA;
                                        }
                                    }
                                }
                                else
                                {
                                    ang[i].hit.status = 0;
                                }
                            }
                        }
                    }
                    else
                    {
                        if (ang[i].left)
                        { // movimiento
                            if (ang[i].pos.y < 75)
                            {
                                ang[i].pos.x += ANGUILASPEED;
                            }
                            else
                            {
                                if (ang[i].pos.y > SUELO - 50 - ang[i].pos.height)
                                {
                                    ang[i].pos.x += ANGUILASPEED;
                                }
                                else
                                {
                                    PosicionObieto3(ang[i].v.vx, ang[i].v.vy, ang[i].pos);
                                }
                            }
                            // eliminacion
                            if (ang[i].pos.x > RANCHO + ang[i].pos.width)
                            {
                                ang[i].status = 0;
                            }
                        }
                    }

                    // Colision con golpe
                    if (hit)
                    {
                        for (j = 0; j < MAXHIT1; j++)
                        {
                            if (CheckMobColision(ang[i].pos, hit[j]))
                            {
                                ang[i].status = 0;
                                ang[i].hit.status = 0;
                                random = rand() % 10 + 1;
                                if (random <= 4)
                                {
                                    random = rand() % 2;
                                    if (random)
                                    {
                                        for (k = 0; k < MAXDROPVIDA; k++)
                                        {
                                            if (!dropVida[k].status)
                                            {
                                                dropVida[k].status = 1;
                                                dropVida[k].time = 0;
                                                dropVida[k].pos.x = ang[i].pos.x;
                                                dropVida[k].pos.y = ang[i].pos.y;
                                                k = MAXDROPVIDA;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        for (k = 0; k < MAXDROPASPEED; k++)
                                        {
                                            if (!dropASpeed[k].statusDraw)
                                            {
                                                if (!dropASpeed[k].statusFun)
                                                {
                                                    dropASpeed[k].statusDraw = 1;
                                                    dropASpeed[k].statusFun = 0;
                                                    dropASpeed[k].time = 0;
                                                    dropASpeed[k].pos.x = ang[i].pos.x;
                                                    dropASpeed[k].pos.y = ang[i].pos.y;
                                                    k = MAXDROPASPEED;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    // Colision con iugador
                    if (ang[i].status)
                    {
                        if (player.vida.time > INVULERABILIDAD)
                        {
                            if (CheckPlayerColision(player.pos, ang[i].pos))
                            {
                                PlaySound(dolor);
                                if (player.vida.num < 1)
                                {
                                    piezac = 0;
                                    time = 0;
                                    muerteLvl1(player, shark, tort, ang, pieza, plat);
                                }
                                else
                                {
                                    player.vida.num--;
                                    player.vida.time = 0;
                                }
                                i = MAXANGUILA;
                            }
                        }
                    }
                }
                else
                {
                    // generacion
                    random = (rand() % 50) + 1;
                    if (random == 1)
                    {
                        ang[i].right = rand() % 2;
                        if (ang[i].right)
                        {
                            ang[i].status = 1;
                            ang[i].pos.x = RANCHO;
                            ang[i].pos.y = (rand() % 550) + 60;
                            CalculaComponentesVelocidad(ANGUILASPEED, CalculaAnguloAnguila(ang[i].pos, player.pos), ang[i].v);
                            ang[i].left = 0;
                        }
                        else
                        {
                            ang[i].status = 1;
                            ang[i].pos.x = 0 - ang[i].pos.width;
                            ang[i].pos.y = (rand() % 550) + 60;
                            CalculaComponentesVelocidad(ANGUILASPEED, CalculaAnguloAnguila(ang[i].pos, player.pos), ang[i].v);
                            ang[i].left = 1;
                        }
                    }
                }
            }

            //** dash **************************************************************************************************************************
            if (player.dash)
            {
                if (player.timeDash < 20)
                {
                    if (lookR)
                    {
                        if (lookUp)
                        {
                            player.pos.x += VDDIAGONAL;
                            player.pos.y -= VDDIAGONAL;
                        }
                        else
                        {
                            if (lookDown)
                            {
                                player.pos.x += VDDIAGONAL;
                                player.pos.y += VDDIAGONAL;
                            }
                            else
                            {
                                player.pos.x += VD1;
                            }
                        }
                    }
                    else
                    {
                        if (lookL)
                        {
                            if (lookUp)
                            {
                                player.pos.x -= VDDIAGONAL;
                                player.pos.y -= VDDIAGONAL;
                            }
                            else
                            {
                                if (lookDown)
                                {
                                    player.pos.x -= VDDIAGONAL;
                                    player.pos.y += VDDIAGONAL;
                                }
                                else
                                {
                                    player.pos.x -= VD1;
                                }
                            }
                        }
                        else
                        {
                            if (lookUp)
                            {
                                player.pos.y -= VD1;
                            }
                            else
                            {
                                if (lookDown)
                                {
                                    player.pos.y += VD1;
                                }
                            }
                        }
                    }
                }
                else
                {
                    lookDown = 0;
                    lookUp = 0;
                    player.dash = 0;
                }
            }

            //** hit ********************************************************************************************************************************
            for (i = 0; i < MAXHIT1; i++)
            {
                //** movimiento del disparo ***********************************************************************************
                if (hit[i].status)
                {
                    PosicionObieto3(hit[i].v.vx, hit[i].v.vy, hit[i].pos);

                    //** Eliminacion del proyectil *******************************************************************************
                    // si se paso del borde izquierdo
                    if (hit[i].pos.x < 0 - hit[i].pos.width)
                    {
                        hit[i].status = 0;
                    }
                    else
                    {
                        // si se paso del borde derecho
                        if (hit[i].pos.x > RANCHO)
                        {
                            hit[i].status = 0;
                        }
                    }

                    if (hit[i].pos.y < 0)
                    {
                        hit[i].status = 0;
                    }
                    else
                    {
                        if (hit[i].pos.y > RALTO)
                        {
                            hit[i].status = 0;
                        }
                    }
                }
            }

            //** input *****************************************************************************************************************************
            if (!player.dash) // right left
            {
                if (IsKeyDown(KEY_RIGHT))
                {
                    player.x0 = player.pos.x;
                    player.pos.x += VX1;
                    lookR = 1;
                    lookL = 0;
                }
                else
                {
                    if (IsKeyDown(KEY_LEFT))
                    {
                        player.x0 = player.pos.x;
                        player.pos.x -= VX1;
                        lookR = 1;
                        lookL = 0;
                    }
                }
            }

            if (!player.dash) // up down
            {
                if (IsKeyDown(KEY_UP))
                {
                    player.pos.y -= VY1;
                }
                else
                {
                    if (IsKeyDown(KEY_DOWN))
                    {
                        player.pos.y += VY1;
                    }
                }
            }

            // dash KEY C
            if (player.timeDash > 80)
            {
                if (!player.dash)
                {
                    if (IsKeyPressed(KEY_C))
                    {
                        PlaySound(sdash);
                        Direccioniugador(lookL, lookR, lookUp, lookDown, player);
                        player.dash = 1;
                        player.timeDash = 0;
                    }
                }
            }

            // hit
            if (IsKeyDown(KEY_X))
            {
                for (i = 0; i < MAXHIT1; i++)
                {
                    Direccioniugador(lookL, lookR, lookUp, lookDown, player);
                    if (!player.buff) //** Meiora ******************************************************************************************************
                    {
                        if (player.AtkC > VATAQUE1)
                        {
                            if (hit[i].status == 0)
                            {
                                hit[i].status = 1;
                                player.AtkC = 0;
                                PlaySound(disparo_nv1);
                                InicializaProyectil(lookL, lookR, lookUp, lookDown, player, hit[i]);
                                CalculaComponentesVelocidad(VPROYECTIL1, 45 * hit[i].direccion, hit[i].v);
                                disparo=1;
                                // printf("Direccion = %d l = %d r = %d up = %d down = %d \n",hit[i].direccion,lookL,lookR,lookUp,lookDown);
                                i = MAXHIT1;
                            }
                        }
                    }
                    else
                    {
                        if (player.AtkC > VATAQUEBUFF1)
                        {
                            if (hit[i].status == 0)
                            {
                                hit[i].status = 1;
                                player.AtkC = 0;
                                disparo=1;
                                PlaySound(disparo_nv1);
                                InicializaProyectil(lookL, lookR, lookUp, lookDown, player, hit[i]);
                                CalculaComponentesVelocidad(VPROYECTIL1, 45 * hit[i].direccion, hit[i].v);
                                // printf("Direccion = %d l = %d r = %d up = %d down = %d \n",hit[i].direccion,lookL,lookR,lookUp,lookDown);
                                i = MAXHIT1;
                            }
                        }
                    }
                }
            }
        }

        // dibujado

        framesAutom++;
        if (framesAutom >= (60 / framesSpeed))
        {
            framesAutom = 0;
            currentFrame++;

            if (currentFrame > 5)
                currentFrame = 0;
            framesTortuga.x = (float)currentFrame * (float)tortuga.width / 6;
            framesTortugaizq.x = (float)currentFrame * (float)tortugaizq.width / 6;
            framesAnguila.x = (float)currentFrame * (float)anguila.width / 6;
            framesAnguilaizq.x = (float)currentFrame * (float)anguilaizq.width / 6;
            framesPulpo.x = (float)currentFrame * (float)pulpo.width / 6;
            framesPulpoizq.x = (float)currentFrame * (float)pulpoizq.width / 6;
            framesReposo.x = (float)currentFrame * (float)reposo.width / 4;
            framesReposoizq.x = (float)currentFrame * (float)reposoizq.width / 4;
        }

         Direccioniugador(lookL,lookR,lookUp,lookDown,player);

        // jugador
        if (!IsKeyDown(KEY_X))
        {
             framesSalto++;
                    if (framesSalto >= (60 / framesSpeed))
                    {
                        framesSalto = 0;
                        currentSalto++;

                        if (currentSalto > 3)
                            currentSalto = 0;
                        frameSalto.x = (float)currentSalto * (float)salto.width / 4;
                        frameSaltoder.x = (float)currentSalto * (float)saltoder.width / 4;
                    }
                    if (lookL)
                    {
                        DrawTextureRec(salto, frameSalto, Vector2{player.pos.x - 80, player.pos.y - 50}, WHITE);
                    }
                    else
                    {
                        if (lookR)
                        {
                            DrawTextureRec(saltoder, frameSalto, Vector2{player.pos.x - 40, player.pos.y - 50}, WHITE);
                        }
                        else
                        {
                            DrawTextureRec(saltoder, frameSalto, Vector2{player.pos.x - 40, player.pos.y - 50}, WHITE);
                        }
                    }
        }
        else
        {
            /*
            DrawTexture(ataquesderechos[1], player.pos.x, player.pos.y - 10, WHITE);
            DrawTexture(ataquesderechos[0], player.pos.x, player.pos.y - 10, WHITE);
            DrawTexture(ataquesderechos[3], player.pos.x - 5, player.pos.y - 30, WHITE);
            DrawTexture(ataquesderechos[2], player.pos.x, player.pos.y - 10, WHITE);
            DrawTexture(ataquesizquierdos[1], player.pos.x - 25, player.pos.y - 10, WHITE);
            DrawTexture(ataquesizquierdos[3], player.pos.x, player.pos.y - 30, WHITE);
            DrawTexture(ataquesizquierdos[2], player.pos.x - 32, player.pos.y - 10, WHITE);
            */
            if (disparo)
            {
                if (lookR)
                {
                    if (lookUp)
                    {
                        DrawTexture(ataquesderechos[3], player.pos.x - 5, player.pos.y - 30, WHITE);
                    }
                    else
                    {
                        if (lookDown)
                        {
                            DrawTexture(ataquesderechos[1], player.pos.x, player.pos.y - 10, WHITE);
                        }
                        else
                        {
                            DrawTexture(ataquesderechos[2], player.pos.x, player.pos.y - 10, WHITE);
                        }
                    }
                }
                else
                {
                    if (lookL)
                    {
                        if (lookUp)
                        {
                            DrawTexture(ataquesizquierdos[3], player.pos.x, player.pos.y - 30, WHITE);
                        }
                        else
                        {
                            if (lookDown)
                            {
                                DrawTexture(ataquesizquierdos[1], player.pos.x - 25, player.pos.y - 10, WHITE);
                            }
                            else
                            {
                                DrawTexture(ataquesizquierdos[2], player.pos.x - 32, player.pos.y - 10, WHITE);
                            }
                        }
                    }
                    else
                    {
                        if (lookUp)
                        {
                            DrawTexture(ataquesderechos[4], player.pos.x, player.pos.y - 10, WHITE);
                        }
                        else
                        {
                            if (lookDown)
                            {
                                DrawTexture(ataquesderechos[0], player.pos.x, player.pos.y - 10, WHITE);
                            }
                        }
                    }
                }
            }
            else
            {
                framesSalto++;
                    if (framesSalto >= (60 / framesSpeed))
                    {
                        framesSalto = 0;
                        currentSalto++;

                        if (currentSalto > 3)
                            currentSalto = 0;
                        frameSalto.x = (float)currentSalto * (float)salto.width / 4;
                        frameSaltoder.x = (float)currentSalto * (float)saltoder.width / 4;
                    }
                    if (lookL)
                    {
                        DrawTextureRec(salto, frameSalto, Vector2{player.pos.x - 80, player.pos.y - 50}, WHITE);
                    }
                    else
                    {
                        if (lookR)
                        {
                            DrawTextureRec(saltoder, frameSalto, Vector2{player.pos.x - 40, player.pos.y - 50}, WHITE);
                        }
                        else
                        {
                            DrawTextureRec(saltoder, frameSalto, Vector2{player.pos.x - 40, player.pos.y - 50}, WHITE);
                        }
                    }
                    
            }
        }

        for (i = 0; i < MAXHIT1; i++)
        {
            if (hit[i].status)
            {
                DrawTexture(bullet_nv1, hit[i].pos.x, hit[i].pos.y, WHITE);
            }
        }
        // suelo

        // vida
        for (i = 1; i <= player.vida.num; i++)
        {
            DrawTexture(corazon, player.vida.pos.x, player.vida.pos.y, WHITE);
            player.vida.pos.x += 25 + player.vida.pos.width;
        }
        player.vida.pos.x = 25;

        // enemigos
        for (i = 0; i < MAXSHARK; i++)
        {
            if (shark[i].status)
            {
                if (shark[i].right)
                {
                    // DrawRectangleRec(shark[i].pos, RED);
                    DrawTextureRec(pulpoizq, framesPulpoizq, Vector2{shark[i].pos.x - 25, shark[i].pos.y - 20}, WHITE);
                }

                if (shark[i].left)
                {
                    // DrawRectangleRec(shark[i].pos, RED);
                    DrawTextureRec(pulpo, framesPulpo, Vector2{shark[i].pos.x + 13, shark[i].pos.y - 20}, WHITE);
                }
            }
        }

        for (i = 0; i < MAXTORTUGA; i++)
        {
            if (tort[i].status)
            {
                if (tort[i].right)
                {
                    DrawTextureRec(tortugaizq, framesTortugaizq, Vector2{tort[i].pos.x - 15, tort[i].pos.y}, WHITE);
                }

                if (tort[i].left)
                {
                    DrawTextureRec(tortuga, framesTortuga, Vector2{tort[i].pos.x - 15, tort[i].pos.y - 50}, WHITE);
                }
            }
        }
        
        //DROPS
        //DROPS
        for(i=0;i<MAXDROPVIDA;i++)
        {
            if(dropVida[i].status)
            {
                DrawTexture(corazon,dropVida[i].pos.x,dropVida[i].pos.y,WHITE);
            }
        }
        for(i=0;i<MAXDROPASPEED;i++)
        {
            if(dropASpeed[i].statusDraw)
            {
                if(!dropASpeed[i].statusFun)
                 {
                    DrawTexture(Aspeed,dropASpeed[i].pos.x,dropASpeed[i].pos.y,WHITE);
                }
            }
        }
        for (i = 0; i < MAXANGUILA; i++)
        {
            if (ang[i].status)
            {
                if (!ang[i].hit.status)
                {
                    if (ang[i].left)
                    {
                        // DrawRectangleRec(ang[i].pos, RED);
                        DrawTextureRec(anguila, framesAnguila, Vector2{ang[i].pos.x - 5, ang[i].pos.y - 33}, WHITE);
                    }
                    if (ang[i].right)
                    {
                        // DrawRectangleRec(ang[i].pos, RED);
                        DrawTextureRec(anguilaizq, framesAnguilaizq, Vector2{ang[i].pos.x - 12, ang[i].pos.y - 33}, WHITE);
                    }
                }
                else
                {
                    if (ang[i].left)
                    {
                        framesAtaque++;
                        if (framesAtaque >= (60 / framesSpeed))
                        {
                            framesAtaque = 0;
                            currentAtaque++;

                            if (currentAtaque > 6)
                                currentAtaque = 0;
                            framesAtaque_ani.x = (float)currentAtaque * (float)ataque_ani.width / 6;
                            framesAtaque_anizq.x = (float)currentAtaque * (float)ataque_anizq.width / 6;
                        }
                        PlaySound(anguilasound);
                        DrawTextureRec(ataque_ani, framesAtaque_ani, Vector2{ang[i].hit.pos.x - 12, ang[i].pos.y - 33}, WHITE);
                    }
                    if (ang[i].right)
                    {
                        framesAtaque++;
                        if (framesAtaque >= (60 / framesSpeed))
                        {
                            framesAtaque = 0;
                            currentAtaque++;

                            if (currentAtaque > 6)
                                currentAtaque = 0;
                            framesAtaque_ani.x = (float)currentAtaque * (float)ataque_ani.width / 6;
                            framesAtaque_anizq.x = (float)currentAtaque * (float)ataque_anizq.width / 6;
                        }
                        DrawTextureRec(ataque_anizq, framesAtaque_anizq, Vector2{ang[i].hit.pos.x - 12, ang[i].pos.y - 33}, WHITE);
                    }
                }
            }
        }
        // piezas
        for (i = 0; i < 3; i++)
        {
            if (pieza[i].status)
            {
                DrawTexture(piezas_nv1[i], pieza[i].pos.x, pieza[i].pos.y, WHITE);
            }
        }
        // plataformas
        for (i = 0; i < MAXPLAT1; i++)
        {
            DrawTexture(plataforma_nv1, plat[i].x, plat[i].y, WHITE);
            // DrawRectangleRec(plat[i], DARKGREEN);
        }
        EndMode2D();
        EndDrawing();
    }
    finNivel1:

}

void Direccioniugador(int &L, int &R, int &Up, int &Down, Tplayer player)
{
    if (IsKeyDown(KEY_RIGHT))
    {
        if (IsKeyDown(KEY_UP))
        {
            R = 1;
            Up = 1;
            Down = 0;
            L = 0;
        }
        else
        {
            if (IsKeyDown(KEY_DOWN))
            {
                R = 1;
                Up = 0;
                Down = 1;
                L = 0;
            }
            else
            {
                R = 1;
                Up = 0;
                Down = 0;
                L = 0;
            }
        }
    }
    else
    {
        if (IsKeyDown(KEY_LEFT))
        {
            if (IsKeyDown(KEY_UP))
            {
                R = 0;
                Up = 1;
                Down = 0;
                L = 1;
            }
            else
            {
                if (IsKeyDown(KEY_DOWN))
                {
                    R = 0;
                    Up = 0;
                    Down = 1;
                    L = 1;
                }
                else
                {
                    R = 0;
                    Up = 0;
                    Down = 0;
                    L = 1;
                }
            }
        }
        else
        {
            if (IsKeyDown(KEY_UP))
            {
                R = 0;
                Up = 1;
                Down = 0;
                L = 0;
            }
            else
            {
                if (IsKeyDown(KEY_DOWN))
                {
                    R = 0;
                    Up = 0;
                    Down = 1;
                    L = 0;
                }
                else
                {
                    if (player.x0 <= player.pos.x)
                    {
                        R = 1;
                        Up = 0;
                        Down = 0;
                        L = 0;
                    }
                    else
                    {
                        R = 0;
                        Up = 0;
                        Down = 0;
                        L = 1;
                    }
                }
            }
        }
    }
}

void InicializaProyectil(int L, int R, int Up, int Down, Tplayer player, Thit &hit)
{
    hit.pos.y = player.pos.y + player.pos.height / 4;
    hit.pos.x = player.pos.x + player.pos.width / 2;
    if (R)
    {
        if (Up)
        {
            hit.direccion = 1;
        }
        else
        {
            if (Down)
            {
                hit.direccion = 7;
            }
            else
            {
                hit.direccion = 0;
            }
        }
    }
    else
    {
        if (L)
        {
            if (Up)
            {
                hit.direccion = 3;
            }
            else
            {
                if (Down)
                {
                    hit.direccion = 5;
                }
                else
                {
                    hit.direccion = 4;
                }
            }
        }
        else
        {
            if (Up)
            {
                hit.direccion = 2;
            }
            else
            {
                if (Down)
                {
                    hit.direccion = 6;
                }
            }
        }
    }
}

void CalculaComponentesVelocidad(float velocidad, float grados, Tvel &v)
{
    if (grados >= 360)
    {
        grados -= 360;
    }

    v.vy = velocidad * sin(Radianes3(grados));
    v.vx = sqrt((pow(velocidad, 2) - pow(v.vy, 2)));
    if (grados <= 90)
    {
        v.vy = -v.vy;
    }
    else
    {
        if (grados <= 180)
        {
            v.vx = -v.vx;
            v.vy = -v.vy;
        }
        else
        {
            if (grados <= 270)
            {
                v.vx = -v.vx;
                v.vy = -v.vy;
            }
            else
            {
                v.vy = -v.vy;
            }
        }
    }
}

float Radianes3(float grados)
{
    return (grados * M_PI / 180);
}

void PosicionObieto3(float vx, float vy, Trec &pos)
{
    pos.x += vx;
    pos.y += vy;
}

int CheckPlayerColision(Trec player, Trec mob)
{
    if (player.x < (mob.x + mob.width))
    {
        if ((player.x + player.width) > mob.x)
        {
            if (player.y < (mob.y + mob.height))
            {
                if ((player.y + player.height) > mob.y)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int CheckMobColision(Trec mob, Thit hit)
{
    if (mob.x < (hit.pos.x + hit.pos.width))
    {
        if ((mob.x + mob.width) > hit.pos.x)
        {
            if (mob.y < (hit.pos.y + hit.pos.height))
            {
                if ((mob.y + mob.height) > hit.pos.y)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void LimpiaEnemigosLvl1(Tshark shark[], Ttortu tort[], Tangui ang[])
{
    int i;
    for (i = 0; i < MAXSHARK; i++)
    {
        shark[i].status = 0;
    }
    for (i = 0; i < MAXTORTUGA; i++)
    {
        tort[i].status = 0;
    }
    for (i = 0; i < MAXANGUILA; i++)
    {
        ang[i].status = 0;
        ang[i].hit.status = 0;
    }
}

float CalculaAnguloAnguila(Trec enemigo, Trec player)
{
    float difx = fabs(player.x + player.width / 2 - (enemigo.x + enemigo.width / 2));
    float dify = fabs(player.y + player.height / 2 - (enemigo.y + enemigo.height / 2));
    float a = atan2(difx, dify);
    a = a * 180 / M_PI;
    if (player.x > enemigo.x)
    {
        if (player.y > enemigo.y)
        {
            return (270 + a);
        }
        else
        {
            return (90 - a);
        }
    }
    else
    {
        if (player.y > enemigo.y)
        {
            return (270 - a);
        }
        else
        {
            return (90 + a);
        }
    }
    return 0;
}

float CalculaAnguloAnguila(Trec ang, Trec player)
{
    float difx = fabs(player.x + player.width / 2 - ang.x);
    float dify = fabs(player.y + player.height / 2 - ang.y);
    float a = atan2(difx, dify);
    a = a * 180 / M_PI;
    if (player.x > ang.x)
    {
        if (player.y > ang.y)
        {
            return (270 + a);
        }
        else
        {
            return (90 - a);
        }
    }
    else
    {
        if (player.y > ang.y)
        {
            return (270 - a);
        }
        else
        {
            return (90 + a);
        }
    }
    return 0;
}

void AngElectro(Tangui &ang)
{
    ang.hit.pos.y = ang.pos.y - ang.pos.height;
    ang.hit.pos.x = ang.pos.x - 21;
    ang.hit.status = 1;
    ang.hit.time = 0;
}

void muerteLvl1(Tplayer &player, Tshark shark[], Ttortu tort[], Tangui ang[], Tpart pieza[], Trec plat[])
{
    int j;
    player.pos.x = 400;   // Posicion incial
    player.pos.y = SUELO; //""
    player.timeDash = 70;
    player.vida.num = MAXVIDA;
    LimpiaEnemigosLvl1(shark, tort, ang);
    for (j = 0; j < 3; j++)
    {
        pieza[j].status = 1;
        pieza[j].listo = 0;
        pieza[j].pos.x = plat[j].x + plat[j].width / 2 - pieza[j].pos.width / 2;
        pieza[j].pos.y = -300;
    }
}

void nivel2(int diflvl)
{
    SetTargetFPS(60);
    InitWindow(RANCHO, RALTO, "juego");
    srand(time(NULL));
    int j, i;
    int y0Cam;

    int framesAutom = 0;

    int framesSpeed = 8;
    int currentFrame = 0;

    int currentPersonaje = 0;
    int framesPersonaje = 0;

    int currentSalto = 0;
    int framesSalto = 0;

    // contadores
    int frameC = 0;
    float time = 0;
    int c = 0;
    int igncolision = 0;
    int hitc = 0;
    int platc = 0;
    // int caminarc=0;

    // banderas
    int bsuelo = 0;
    int bdown = 0;
    // int caminar=0;
    int lookR = 1;
    int lookL = 0;
    int lookUp = 0;
    int lookDown = 0;
    int hit = 0;
    int dash = 0;

    int fin = 0;
    // auxiliar
    int random;

    // ************************************************ TEXTURAS ********************************************************************
    Texture2D pajaro = LoadTexture("texturas/pajaro.png");
    Rectangle framesPajaro = {0.0f, 0.0f, (float)pajaro.width / 6, (float)pajaro.height};

    Texture2D pajaroizq = LoadTexture("texturas/pajaroizq.png");
    Rectangle framesPajaroizq = {0.0f, 0.0f, (float)pajaroizq.width / 6, (float)pajaroizq.height};

    Texture2D huevo = LoadTexture("texturas/egg.png");
    Rectangle framesHuevo = {0.0f, 0.0f, (float)huevo.width, (float)huevo.height};

    Texture2D carro = LoadTexture("texturas/Ranger.png");
    Rectangle framesCarro = {0.0f, 0.0f, (float)carro.width, (float)carro.height};

    Texture2D carro2 = LoadTexture("texturas/Ranger.png");
    Rectangle framesCarro2 = {0.0f, 0.0f, (float)carro2.width, (float)carro2.height};

    Texture2D caminar = LoadTexture("texturas/Cyborg_run.png");
    Rectangle framesCaminar = {0.0f, 0.0f, (float)caminar.width / 6, (float)caminar.height};

    Texture2D caminarizq = LoadTexture("texturas/Cyborg_run_left.png");
    Rectangle framesCaminarizq = {0.0f, 0.0f, (float)caminarizq.width / 6, (float)caminarizq.height};

    Texture2D reposo = LoadTexture("texturas/Cyborg_idle.png");
    Rectangle framesReposo = {0.0f, 0.0f, (float)reposo.width / 4, (float)reposo.height};

    Texture2D reposoizq = LoadTexture("texturas/Cyborg_idle_left.png");
    Rectangle framesReposoizq = {0.0f, 0.0f, (float)reposoizq.width / 4, (float)reposoizq.height};

    Texture2D danio = LoadTexture("texturas/Cyborg_hurt.png");
    Rectangle framesDanio = {0.0f, 0.0f, (float)danio.width, (float)danio.height};

    Texture2D salto = LoadTexture("texturas/Cyborg_jump.png");
    Rectangle frameSalto = {0.0f, 0.0f, (float)salto.width / 4, (float)salto.height};

    Texture2D saltoder = LoadTexture("texturas/Cyborg_jumpr.png");
    Rectangle frameSaltoder = {0.0f, 0.0f, (float)saltoder.width / 4, (float)saltoder.height};

    Texture2D background = LoadTexture("texturas/fondo1.png");
    Rectangle frameBackground = {0.0f, 0.0f, (float)RANCHO, (float)RALTO};

    Texture2D ground = LoadTexture("texturas/ground.png");
    Rectangle frameGround = {0.0f, 0.0f, (float)ground.width, (float)ground.height};

    Texture2D back = LoadTexture("texturas/back1.png");
    Texture2D middle = LoadTexture("texturas/middle.png");
    Texture2D front = LoadTexture("texturas/front.png");

    Texture2D plataforma = LoadTexture("texturas/plataforma1.png");

    Texture2D escudo = LoadTexture("texturas/escudo.png");
    Rectangle frameEscudo = {0.0f, 0.0f, (float)escudo.width, (float)escudo.height};

    Texture2D escudoh = LoadTexture("texturas/escudoh.png");
    Rectangle frameEscudoh = {0.0f, 0.0f, (float)escudoh.width, (float)escudoh.height};

    Texture2D piezas[3];

    Rectangle framePiezas[3] = {0.0f, 0.0f, (float)ground.width, (float)ground.height};

    Texture2D corazon=LoadTexture("texturas/corazon.png");
    piezas[0] = LoadTexture("texturas/pieza1_2.png");
    piezas[1] = LoadTexture("texturas/pieza2_2.png");
    piezas[2] = LoadTexture("texturas/pieza3_2.png");
    
    framePiezas[0] = {0.0f, 0.0f, (float)piezas[0].width, (float)piezas[0].height};
    framePiezas[1] = {0.0f, 0.0f, (float)piezas[1].width, (float)piezas[1].height};
    framePiezas[2] = {0.0f, 0.0f, (float)piezas[2].width, (float)piezas[2].height};

    // ************************************************ SONIDOS ********************************************************************

    InitAudioDevice();

    Sound dolor = LoadSound("sonidos/danio.wav");
    Sound brinco = LoadSound("sonidos/salto.mp3");
    Sound paso = LoadSound("sonidos/paso1.wav");
    Sound pajarin = LoadSound("sonidos/pajaro.wav");
    Sound agarrar = LoadSound("sonidos/pieza.wav");
    Sound carrillo = LoadSound("sonidos/carrillo2.wav");
    Music nivel2 = LoadMusicStream("sonidos/nivel2_musica.mp3");
    Sound sdash = LoadSound("sonidos/dash.mp3");
    SetSoundVolume(brinco, -0.15f);
    SetSoundVolume(pajarin, -0.5f);
    SetMusicVolume(nivel2, -0.5f);
    SetSoundVolume(carrillo, -0.2f);
    SetSoundVolume(sdash, +15);

    // Inicializacion ***************************************************************************************
    // Inicializacion Plataformas
    Tplat plat[MAXPLAT];
    plat[0].pos.x = 400;
    plat[0].status = 1;
    plat[0].flag = 0;
    plat[0].pos.width = 350;
    plat[0].pos.height = 40;
    plat[0].pos.y = (rand() % 300) + 200;
    for (j = 1; j < MAXPLAT; j++)
    {
        if (plat[j - 1].pos.x < -7200)
        {
            for (i = j + 1; i < MAXPLAT; i++)
            {
                plat[i].status = 0;
                plat[i].flag = 0;
                plat[i].pos.width = 0;
                plat[i].pos.height = 0;
                plat[i].pos.y = 0;
                plat[i].pos.x = 0;
            }
            j = MAXPLAT;
        }
        else
        {
            plat[j].status = 1;
            plat[j].flag = 0;
            plat[j].pos.width = 350;
            plat[j].pos.height = 40;
            plat[j].pos.y = (rand() % 250) + 200;
            plat[j].pos.x = plat[j - 1].pos.x - plat[j].pos.width - ((rand() % 200) + 50);
            platc++;
        }
    }

    // Inicializacion piezas
    Tpart pieza[3];
    int piezac = 0;
    random = (platc) / 3;
    for (j = 0; j < 3; j++)
    {

        pieza[j].status = 1;
        pieza[j].listo=0;
        pieza[j].pos.height = 163;
        pieza[j].pos.width = 114;

        if (j == 0)
        {
            pieza[j].pos.y = plat[platc - 1].pos.y - pieza[j].pos.height;
            pieza[j].pos.x = plat[platc - 1].pos.x + plat[platc].pos.width / 2;
        }
        else
        {
            pieza[j].pos.y = plat[platc - random * j].pos.y - pieza[j].pos.height;
            pieza[j].pos.x = plat[platc - random * j].pos.x + plat[platc - random * j].pos.width / 2;
        }
    }

    // Inicializa la posicion
    Tplayer2 player;
    player.pos.height = ALTOP;
    player.pos.width = ANCHOP-25;
    player.pos.x = 400;   // Posicion1 incial
    player.pos.y = SUELO; //""
    player.y0 = player.pos.y;
    player.v0 = 0;
    player.timeDash = 70;

    // vida
    player.vida.num=MAXVIDA;
    player.vida.pos.width=30;
    player.vida.pos.height=30;
    player.vida.pos.x=player.pos.x-600;;
    player.vida.pos.y=30;
    player.vida.time=0;

    // Inicializacion enemigos
    Tave ave[MAXAVE];
    for (j = 0; j < MAXAVE; j++)
    {
        ave[j].status = 0;
        ave[j].right = 0;
        ave[j].left = 0;
        ave[j].pos.x = 2000;
        ave[j].pos.y = 800;
        ave[j].pos.height = 20;
        ave[j].pos.width = 40;
    }

    Tegg egg[MAXEGG];
    for (j = 0; j < MAXEGG; j++)
    {
        egg[j].status = 0;
        egg[j].pos.height = 30;
        egg[j].pos.width = 20;
        egg[j].pos.x = 0;
        egg[j].pos.y = 800;
    }

    Tcar car[MAXCAR];
    for (j = 0; j < MAXCAR; j++)
    {
        car[j].status = 0;
        car[j].pos.height = 140;
        car[j].pos.width = 315;
        car[j].pos.x = 0;
        car[j].pos.y = 800;
        car[j].movimiento = 0;
        car[j].time = 120;
    }

    Thit hithit;

    // Inicializacion camara
    Camera2D camara = {0};
    camara.target.x = player.pos.x + 30;
    camara.target.y = player.pos.y;
    camara.offset.x = 640;
    camara.offset.y = CAMY;
    camara.rotation = 0;
    camara.zoom = 1;

    Tcora dropVida[MAXDROPVIDA];

    for(i=0;i<MAXDROPVIDA;i++)
    {
        dropVida[i].pos.width=30;
        dropVida[i].pos.height=30;
        dropVida[i].status=0;
        dropVida[i].time=0;
    }
    float posicion = player.pos.x;

    while (!WindowShouldClose())
    {

        time += 1;
        igncolision++;
        frameC++;
        player.timeDash++;
        player.vida.time++;

        //** terminar el nivel ***********************************************************************************
        if(pieza[0].status)
        {
            if(pieza[0].pos.y==SUELO-pieza[0].pos.height)
            {
                if(pieza[1].status)
                {
                    if(pieza[1].pos.y==SUELO-pieza[1].pos.height)
                    {
                        if(pieza[2].status)
                        {
                            if(pieza[2].pos.y==SUELO-pieza[2].pos.height)
                            {
                                
                                if(!fin)
                                {
                                    time=0;
                                }
                                fin=1;
                                LimpiaEnemigosLvl2(ave,car);
                                if(time>300)
                                {
                                    cinemaPuzleNivel2(diflvl);
                                    goto finNivel2;
                                }
                                
                            }
                        }
                    }
                }
            }
        }

        // **************************************************** DIBUJO *******************************************************
        BeginDrawing();

        BeginMode2D(camara);

        ClearBackground(LIGHTGRAY);
        float ancho = 700;
        for (int x = 0; x < 8; x++)
        {
            DrawTextureEx(back, Vector2{ancho, 0}, 0, 1, WHITE);
            DrawTextureEx(middle, Vector2{ancho, 0}, 0, 1, WHITE);
            DrawTextureEx(front, Vector2{ancho, 0}, 0, 1, WHITE);
            ancho -= back.width;
        }
    
        float piso = 2000;
        for (int x = 0; x < 2000; x++)
        {
            DrawTextureEx(ground, Vector2{piso, SUELO}, 0, 1, WHITE);
            piso -= ground.width;
        }
        //****************************************************** PIEZAS **********************************************************************
        
        for(j=0;j<3;j++)
        {   
            //drop
            if(!pieza[j].listo)
            {
                if(!pieza[j].status)
                {
                     if(CheckPlayerColision(player.pos,pieza[j].pos))
                    {
                        pieza[j].status=1;
                        pieza[j].listo=1;
                    }
                }
            }

            //recolleccion
            if(!pieza[j].listo)
            {
                if(pieza[j].status)
                {
                    if(CheckPlayerColision(player.pos,pieza[j].pos))
                    {
                        PlaySound(agarrar);
                        pieza[j].status=0;
                        pieza[j].pos.y=SUELO-pieza[j].pos.height;
                        piezac++;
                        switch(j)
                        {
                            case 0:
                                pieza[j].pos.x=850;
                                break;
                            case 1:
                                pieza[j].pos.x=964;
                                break;
                            case 2:
                                pieza[j].pos.x=1058;
                                break;
                        }
                        j=3;
                    }
                }
            }    
        }
    
        //******************************************************** AVES **************************************************************************
        for (j = 0; j < MAXAVE; j++)
        {
            // comportameinto
            if (ave[j].status)
            {
                // movimiento enemigo **si sale de la pantalla se elimina**
                if (ave[j].right)
                {
                    ave[j].pos.x -= AVESPEED;
                    if (ave[j].pos.x <= player.pos.x - 750 - ave[j].pos.width)
                    {
                        ave[j].status = 0;
                    }
                }
                else
                {
                    if (ave[j].left)
                    {
                        ave[j].pos.x += AVESPEED;
                        if (ave[j].pos.x >= player.pos.x + 750)
                        {
                            ave[j].status = 0;
                        }
                    }
                }

                // ataque enemigo ***********************************************************************************
                random = (rand() % 11) + 1;
                if (random == 1)
                {
                    if (ave[j].pos.x <= player.pos.x + player.pos.width + 200)
                    {
                        if (ave[j].pos.x >= player.pos.x - 200)
                        {
                            random = rand() % MAXEGG;
                            DropEgg(ave[j], egg[random]);
                        }
                    }
                }
                // Colision con golpe
                if (hit)
                {
                    if (CheckMobColision(ave[j].pos, hithit))
                    {
                        ave[j].status = 0;
                        random=rand()%10+1;
                        if(random<=4)
                        {
                            for(i=0;i<MAXDROPVIDA;i++)
                            {
                                if(!dropVida[i].status)
                                {
                                    dropVida[i].status=1;
                                    dropVida[i].time=0;
                                    dropVida[i].pos.x=ave[j].pos.x;
                                    dropVida[i].pos.y=ave[j].pos.y;
                                    i=MAXDROPVIDA;
                                }
                            }
                        }
                    }
                }

                // Colision con jugador
                if (ave[j].status)
                {
                    if(player.vida.time>INVULERABILIDAD)
                    {
                        if(CheckPlayerColision(player.pos,ave[j].pos))
                        {
                            PlaySound(dolor);
                            DrawTextureRec(danio, framesDanio, Vector2{player.pos.x - 82, player.pos.y - 60}, WHITE);
                            if(player.vida.num<1)
                            {
                                piezac=0;
                                time=0;
                                muerteLvl2(player,ave,car,pieza,plat,platc);
                            }
                            else
                            {
                                player.vida.num--;
                                player.vida.time=0;
                            }
                            i=MAXAVE;
                        }
                    }
                }
            }
            else
            {
                // generacion
                random = (rand() % 100) + 1;
                if (random == 1)
                {
                    ave[j].right = rand() % 2;
                    if (ave[j].right)
                    {
                        ave[j].status = 1;
                        ave[j].pos.x = player.pos.x + 610 + player.pos.width;
                        ave[j].pos.y = (rand() % 90) + 1;
                        ave[j].left = 0;
                        PlaySound(pajarin);
                    }
                    else
                    {
                        ave[j].status = 1;
                        ave[j].pos.x = player.pos.x - 610;
                        ave[j].pos.y = (rand() % 101) + 1;
                        ave[j].left = 1;
                        PlaySound(pajarin);
                    }
                }
            }
        }

        //** comportamiento huevo ********************************************************************************************************************************
        for (j = 0; j < MAXEGG; j++)
        {
            // elinacion de huevo
            if (egg[j].pos.y - egg[j].pos.height >= SUELO)
            {
                egg[j].status = 0;
                egg[j].pos.y = 800;
            }
            // caida de huevo
            if (egg[j].status)
            {
                egg[j].time += 1;
                egg[j].pos.y = Posicion1(egg[j].y0, 0, egg[j].time, 0);
            }

            // Colision con golpe
            if (hit)
            {
                if (CheckMobColision(egg[j].pos, hithit))
                {
                    if(egg[j].status)
                    {
                        egg[j].status = 0;
                        random=rand()%10+1;
                        if(random<=1)
                        {
                            for(i=0;i<MAXDROPVIDA;i++)
                            {
                                if(!dropVida[i].status)
                                {
                                    dropVida[i].status=1;
                                    dropVida[i].time=0;
                                    dropVida[i].pos.x=egg[j].pos.x;
                                    dropVida[i].pos.y=egg[j].pos.y;
                                    i=MAXDROPVIDA;
                                }
                            }
                        }
                    }
                }
            }

            // Colision con jugador
            if (egg[j].status)
            {
                if(player.vida.time>INVULERABILIDAD)
                {
                    if(CheckPlayerColision(player.pos,egg[j].pos))
                    {
                        PlaySound(dolor);
                        DrawTextureRec(danio, framesDanio, Vector2{player.pos.x - 82, player.pos.y - 60}, WHITE);
                        if(player.vida.num<1)
                        {
                            piezac=0;
                            time=0;
                            muerteLvl2(player,ave,car,pieza,plat,platc);
                        }
                        else
                        {
                            player.vida.num--;
                            player.vida.time=0;
                        }
                        i=MAXEGG;
                    }
                }
            }
        }

        //** enemigo2 carro ********************************************************************************************************************************
        for (j = 0; j < MAXCAR; j++)
        {
            // comportameinto
            if (car[j].status)
            {
                // movimiento enemigo
                if (car[j].movimiento)
                {
                    car[j].pos.x += CARSPEED;
                }
                else
                {
                    car[j].time++;
                    if (car[j].time > 60)
                    {
                        car[j].movimiento = 1;
                    }
                }
                // eliminacion del enemigo
                if (car[j].pos.x >= player.pos.x + 720)
                {
                    car[j].status = 0;
                }

                // Colision con golpe
                if (hit)
                {
                    if(car[j].movimiento)
                    {
                        if (CheckMobColision(car[j].pos, hithit))
                        {
                            car[j].movimiento = 0;
                            car[j].time = 0;
                            random=rand()%10+1;
                            if(random<=4)
                            {
                                for(i=0;i<MAXDROPVIDA;i++)
                                {
                                    if(!dropVida[i].status)
                                    {
                                        dropVida[i].status=1;
                                        dropVida[i].time=0;
                                        dropVida[i].pos.x=car[j].pos.x;
                                        dropVida[i].pos.y=car[j].pos.y;
                                        i=MAXDROPVIDA;
                                    }
                                }
                            }
                        }
                    }
                }

                // Colision con jugador
                if (car[j].status)
                {
                    if(player.vida.time>INVULERABILIDAD)
                    {
                        if(CheckPlayerColision(player.pos,car[j].pos))
                        {
                            PlaySound(dolor);
                            DrawTextureRec(danio, framesDanio, Vector2{player.pos.x - 82, player.pos.y - 60}, WHITE);

                            if(player.vida.num<1)
                            {
                                piezac=0;
                                time=0;
                                muerteLvl2(player,ave,car,pieza,plat,platc);
                            }
                            else
                            {
                                player.vida.num--;
                                player.vida.time=0;
                            }
                            i=MAXCAR;
                        }
                    }
                }
            }
            else
            {
                // generacion
                // random=GetRandomValue(1,1);
                if (player.pos.x < -60)
                {
                    car[j].status = 1;
                    car[j].movimiento = 1;
                    car[j].pos.x = player.pos.x - 610 - car[j].pos.width;
                    car[j].pos.y = SUELO - car[j].pos.height;
                    PlaySound(carrillo);
                }
            }
        }

        //DROPS
        for(i=0;i<MAXDROPVIDA;i++)
            {
                if(dropVida[i].status)
                {
                    //tiempo
                    dropVida[i].time++;
                    //eliminacion
                    if(dropVida[i].time>DESPAWNTIME)
                    {
                        dropVida[i].status=0;
                        dropVida[i].time=0;
                    }

                    //curacion
                    if(CheckPlayerColision(player.pos,dropVida[i].pos))
                    {
                        player.vida.num++;
                        dropVida[i].status=0;
                        dropVida[i].time=0;
                    }
                    else
                    {
                        //movimiento
                        if(dropVida[i].pos.y<SUELO-dropVida[i].pos.height)
                        {
                            dropVida[i].pos.y+=2;
                        }
                        else
                        {
                            dropVida[i].pos.y=SUELO-dropVida[i].pos.height;
                        }
                    }
                }
            }


        //** caluclar posicion y ********************************************************************************************************************************
        if (player.fall)
        {
            if (bdown)
            {
                if (velocidad1(player.v0, time) > 0)
                {
                    if (++c == 1)
                    {
                        player.v0 = velocidad1(player.v0, time); // velocidad1 inicial igual a velocidad1 actual
                        player.y0 = player.pos.y;
                        time = 1;
                    }
                }
                else
                {
                    Reposo3(time, player.v0, player.y0, player.pos.y);
                }
                player.pos.y = Posicion1(player.y0, player.v0, time, bdown);
            }
            else
            {
                player.pos.y = Posicion1(player.y0, player.v0, time, bdown);
            }
        }

        //** colisiones ********************************************************************************************************************************
        // suelo
        if (player.pos.y + player.pos.height > SUELO)
        {
            player.pos.y = SUELO - player.pos.height;
            Reposo3(time, player.v0, player.y0, player.pos.y);
            player.fall = 0;
            bsuelo = 1;
            player.jump = 1;
            player.jumpjump = 1;
        }

        // plataformas
        if (igncolision > 20)
        {
            // plataforma cuando cae
            if (velocidad1(player.v0, time) > 0)
            {
                for (j = 0; j < platc; j++)
                {
                    if (plat[j].status)
                    {
                        if (ColisionPlat2(player, plat[j]))
                        {
                            player.pos.y = plat[j].pos.y - player.pos.height;
                            Reposo3(time, player.v0, player.y0, player.pos.y);
                            player.fall = 0;
                            plat[j].flag = 1;
                            player.jump = 1;
                            player.jumpjump = 1;
                            bdown = 0;
                        }
                    }
                }
            }
        }

        // si salio de la paltaforma
        for (j = 0; j < platc; j++)
        {
            if (plat[j].status)
            {
                if (plat[j].flag)
                {
                    if (!ColisionPlat2(player, plat[j]))
                    {
                        Reposo3(time, player.v0, player.y0, player.pos.y);
                        player.fall = 1;
                        plat[j].flag = 0;
                        player.jump = 1;
                        player.jumpjump = 0;
                        bdown = 0;
                    }
                }
            }
        }

        //** golpe ********************************************************************************************************************************
        if (hit)
        {
            if (lookR)
            {
                hithit.pos.x = player.pos.x + ANCHOP - 20;
                hithit.pos.y = player.pos.y - 20;
            }
            else
            {
                if (lookL)
                {
                    hithit.pos.x = player.pos.x - 60;
                    hithit.pos.y = player.pos.y - 20;
                }
            }

            if (lookUp)
            {
                hithit.pos.x = player.pos.x - player.pos.width / 2;
                hithit.pos.y = player.pos.y - player.pos.height;
            }
            else
            {
                if (lookDown)
                {
                    hithit.pos.x = player.pos.x - player.pos.width / 2;
                    hithit.pos.y = player.pos.y + player.pos.height - player.pos.height / 3;
                }
            }
            if (hitc < 50)
            {
                hitc++;
            }
            else
            {
                hitc = 0;
                hit = 0;
            }
        }

        //** dash ********************************************************************************************************************************
        if (dash)
        {
            PlaySound(sdash);
            if (player.timeDash < 20)
            {
                if (lookR)
                {
                    player.pos.x += VD1;
                }
                else
                {
                    if (lookL)
                    {
                        player.pos.x -= VD1;
                    }
                }
            }
            else
            {
                if (player.pos.x > -10)
                {
                    player.jump = 1;
                    player.jumpjump = 0;
                }
                else
                {
                    player.jump == 0;
                    player.jumpjump = 0;
                }
                player.fall = 1;
                dash = Reposo3(time, player.v0, player.y0, player.pos.y);
            }
        }

        //** camara ********************************************************************************************************************************
        camara.target.y = player.pos.y;
        if (player.pos.y > 100)
        {
            camara.target.y = CAMY;
            camara.offset.y = CAMY;
            camara.target.x = player.pos.x + 25;
        }
        else
        {
            camara.offset.y = RANCHO / 12.5;
            camara.target.x = player.pos.x + 25;
        }

        //** intput ********************************************************************************************************************************
        if (!dash) // right left
        {
            if (IsKeyDown(KEY_RIGHT))
            {
                if (player.pos.x < 1280)
                {
                    player.pos.x += VX1;
                    lookR = 1;
                    lookL = 0;
                }
            }
            else
            {
                if (IsKeyDown(KEY_LEFT))
                {
                    if (player.pos.x > plat[platc - 1].pos.x - 610)
                    {
                        player.pos.x -= VX1;
                        lookR = 0;
                        lookL = 1;
                    }
                }
            }
        }

        if (!dash) // up down
        {
            if (IsKeyPressed(KEY_UP))
            {
                if (player.jump)
                {
                    PlaySound(brinco);
                    Reposo3(time, player.v0, player.y0, player.pos.y);
                    Salto1(time, player.v0, player.y0, player.pos.y);
                    player.fall = 1;
                    if (player.jumpjump) //! doblesalto
                    {
                        PlaySound(brinco);
                        player.jump = 1;
                        player.jumpjump = 0;
                    }
                    else
                    {
                        player.jump = 0;
                    }
                    for (j = 0; j < MAXPLAT; j++)
                    {
                        if (plat[j].status)
                        {
                            plat[j].flag = 0;
                        }
                    }
                    bsuelo = 0;
                    bdown = 0;
                }
            }
            else
            {
                if (IsKeyPressed(KEY_DOWN))
                {
                    for (j = 0; j < MAXPLAT; j++)
                    {
                        if (plat[j].flag)
                        {
                            // if(IsKeyPressedRepeat(KEY_DOWN))
                            {
                                player.fall = 1;
                                igncolision = 0;
                                bdown = 0;
                            }
                        }
                        else
                        {
                            bdown = 1;
                            player.fall = 1;
                            c = 0;
                        }
                    }
                }
            }
        }

        // hit
        if (IsKeyPressed(KEY_X))
        {
            if (IsKeyDown(KEY_UP))
            {
                hithit.pos.width = ALTOP + 30;
                hithit.pos.height = 90;
                hit = 1;
                dash = 0;
                player.fall = 1;
                lookUp = 1;
                lookDown = 0;
            }
            else
            {
                if (IsKeyDown(KEY_DOWN))
                {
                    hithit.pos.width = ALTOP + 30;
                    hithit.pos.height = 90;
                    hit = 1;
                    dash = 0;
                    player.fall = 1;
                    lookDown = 1;
                    lookUp = 0;
                }
                else
                {
                    hithit.pos.width = 90;
                    hithit.pos.height = ALTOP + 30;
                    hit = 1;
                    dash = 0;
                    player.fall = 1;
                    lookDown = 0;
                    lookUp = 0;
                }
            }
        }

        // dash KEY C
        if (player.pos.x < 1250)
        {
            if (player.pos.x > plat[platc - 1].pos.x - 590)
            {
                if (player.timeDash > 80)
                {
                    if (!dash)
                    {
                        if (IsKeyPressed(KEY_C))
                        {
                            dash = 1;
                            player.timeDash = 0;
                            Reposo3(time, player.v0, player.y0, player.pos.y);
                            player.fall = 0;
                            player.jump = 0;
                            player.jumpjump = 0;
                        }
                    }
                }
            }
        }


        // dibujado
        framesAutom++;
        if (framesAutom >= (60 / framesSpeed))
        {
            framesAutom = 0;
            currentFrame++;

            if (currentFrame > 5)
                currentFrame = 0;
            framesPajaro.x = (float)currentFrame * (float)pajaro.width / 6;
            framesPajaroizq.x = (float)currentFrame * (float)pajaroizq.width / 6;
            framesReposo.x = (float)currentFrame * (float)reposo.width / 4;
            framesReposoizq.x = (float)currentFrame * (float)reposoizq.width / 4;
        }

        if (player.fall)
        {
            framesSalto++;
            if (framesSalto >= (60 / framesSpeed))
            {
                framesSalto = 0;
                currentSalto++;

                if (currentSalto > 3)
                    currentSalto = 0;
                frameSalto.x = (float)currentSalto * (float)salto.width / 4;
                frameSaltoder.x = (float)currentSalto * (float)saltoder.width / 4;
            }
            if (lookL)
            {
                DrawTextureRec(salto, frameSalto, Vector2{player.pos.x - 80, player.pos.y - 60}, WHITE);
            }
            if (lookR)
            {
                DrawTextureRec(saltoder, frameSalto, Vector2{player.pos.x - 20, player.pos.y - 60}, WHITE);
            }
        }
        else
        {
            if (IsKeyDown(KEY_RIGHT))
            {
                framesPersonaje++;
                framesSalto = 0;
                if (framesPersonaje >= (60 / framesSpeed))
                {
                    framesPersonaje = 0;
                    currentPersonaje++;

                    if (currentPersonaje > 5)
                    {
                        currentPersonaje = 0;
                        PlaySound(paso);
                    }
                    framesCaminar.x = (float)currentPersonaje * (float)caminar.width / 6;
                }
                DrawTextureRec(caminar, framesCaminar, Vector2{player.pos.x - 20, player.pos.y - 60}, WHITE);
            }
            else if (IsKeyDown(KEY_LEFT))
            {
                framesPersonaje++;
                if (framesPersonaje >= (60 / framesSpeed))
                {
                    framesPersonaje = 0;
                    currentPersonaje++;

                    if (currentPersonaje > 5)
                    {
                        currentPersonaje = 0;
                        PlaySound(paso);
                    }
                    framesCaminarizq.x = (float)currentPersonaje * (float)caminarizq.width / 6;
                }
                DrawTextureRec(caminarizq, framesCaminarizq, Vector2{player.pos.x - 80, player.pos.y - 60}, WHITE);
            }
            else
            {
                framesPersonaje = 0;
                if (lookL)
                {
                    DrawTextureRec(reposoizq, framesReposoizq, Vector2{player.pos.x - 82, player.pos.y - 60}, WHITE);
                }
                if (lookR)
                {
                    DrawTextureRec(reposo, framesReposo, Vector2{player.pos.x - 20, player.pos.y - 60}, WHITE);
                }
            }
        }

        player.vida.pos.x=player.pos.x-600;
        //vida
        for(i=1;i<=player.vida.num;i++)
        {
            
            if(player.pos.y>100)
            {
                player.vida.pos.y=25;
            }
            else
            {
                player.vida.pos.y=player.pos.y-75;
            }
            DrawTexture(corazon,player.vida.pos.x,player.vida.pos.y,WHITE);
            player.vida.pos.x+=25+player.vida.pos.width;
        }

        // plataformas
        for (j = 0; j < platc; j++)
        {
            DrawTexture(plataforma, plat[j].pos.x, plat[j].pos.y, WHITE);
        }

        // enemigos

        for (j = 0; j < MAXAVE; j++)
        {

            if (ave[j].status)
            {
                if (ave[j].left)
                {
                    DrawTextureRec(pajaro, framesPajaro, Vector2{ave[j].pos.x, ave[j].pos.y - 50}, WHITE);
                }

                if (ave[j].right)
                {
                    DrawTextureRec(pajaroizq, framesPajaro, Vector2{ave[j].pos.x, ave[j].pos.y - 50}, WHITE);
                }
            }
        }
        for (j = 0; j < MAXEGG; j++)
        {
            if (egg[j].status)
            {
                DrawTextureRec(huevo, framesHuevo, Vector2{egg[j].pos.x, egg[j].pos.y}, WHITE);
            }
        }
        for (j = 0; j < MAXCAR; j++)
        {
            if (car[j].status)
            {
                DrawTextureRec(carro, framesCarro, Vector2{car[j].pos.x, car[j].pos.y}, WHITE);
            }
        }
        // piezas
        for (j = 0; j < 3; j++)
        {
            if (pieza[j].status)
            {
                if(j!=2)
                {
                    DrawTextureRec(piezas[j], framePiezas[j], Vector2{pieza[j].pos.x, pieza[j].pos.y}, WHITE);
                }
                else
                {
                    DrawTextureRec(piezas[j], framePiezas[j], Vector2{pieza[j].pos.x, pieza[j].pos.y+45}, WHITE);
                }
            }
        }
        // hit
        if (hit)
        {
            if (lookR)
            {
                if (lookDown || lookUp)
                {
                    DrawTextureRec(escudoh, frameEscudoh, {hithit.pos.x - 15, hithit.pos.y + 7}, WHITE);
                }
                else
                {
                    DrawTextureRec(escudo, frameEscudo, {hithit.pos.x + 25, hithit.pos.y + 7}, WHITE);
                }
            }
            if (lookL)
            {
                if (lookUp)
                {
                    DrawTextureRec(escudoh, frameEscudoh, {hithit.pos.x - 15, hithit.pos.y - 7}, WHITE);
                }
                else if (lookDown)
                {
                    DrawTextureRec(escudoh, frameEscudoh, {hithit.pos.x - 15, hithit.pos.y  + 7}, WHITE);
                }
                else
                {
                    DrawTextureRec(escudo, frameEscudo, {hithit.pos.x - 15, hithit.pos.y + 7}, WHITE);
                }
            }
        }
        //DROPS
        for(i=0;i<MAXDROPVIDA;i++)
        {
            if(dropVida[i].status)
            {
                DrawTexture(corazon,dropVida[i].pos.x,dropVida[i].pos.y,WHITE);
            }
        }
        PlayMusicStream(nivel2);
        UpdateMusicStream(nivel2);

        EndMode2D();
        EndDrawing();
    }
    finNivel2:
        UnloadSound(dolor);
        UnloadTexture(back);
        UnloadTexture(front);
        UnloadTexture(middle);
        UnloadTexture(ground);
        UnloadTexture(carro);
        UnloadTexture(plataforma);
        UnloadTexture(saltoder);
        UnloadTexture(salto);
        UnloadTexture(pajaroizq);
        UnloadTexture(caminar);
        UnloadTexture(caminarizq);
        UnloadTexture(reposoizq);
        UnloadTexture(huevo);
        UnloadTexture(pajaro);
        CloseAudioDevice();
}

int ReposoLvl2(float &time, float &v0, int &y0, int y)
{
    time = 0;
    v0 = 0;
    y0 = y;
    return 0;
}

int SaltoLvl2(float &time, float &v0, int &y0, int y)
{
    time = 0;
    y0 = y;
    v0 = VS;
    return 0;
}

void CalculaPosEnemigo(Tave &mob)
{
    if (mob.right)
    {
        mob.pos.x -= 6;
    }
    else
    {
        if (mob.left)
        {
            mob.pos.x += 6;
        }
    }
}

int CheckPlayerColisionLvl2(Trec player, Trec mob)
{
    if (player.x < (mob.x + mob.width))
    {
        if ((player.x + player.width) > mob.x)
        {
            if (player.y < (mob.y + mob.height))
            {
                if ((player.y + player.height) > mob.y)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void DropEgg(Tave mob, Tegg &egg)
{
    if (!egg.status)
    {
        egg.time = 0;
        egg.y0 = mob.pos.y;
        egg.pos.y = mob.pos.y;
        egg.pos.x = mob.pos.x + 14;
        egg.status = 1;
    }
}

void LimpiaEnemigosLvl2(Tave ave[], Tcar car[])
{
    int j;
    for (j = 0; j < MAXAVE; j++)
    {
        ave[j].status = 0;
    }
    for (j = 0; j < MAXCAR; j++)
    {
        car[j].status = 0;
    }
}

void muerteLvl2(Tplayer2 &player,Tave ave[],Tcar car[],Tpart pieza[],Tplat plat[],int platc)
{
    int j;
    player.pos.x=400;  //Posicion incial
    player.pos.y=SUELO;    //""
    player.y0=player.pos.y;
    player.v0=0;
    player.timeDash=70;
    player.vida.num=MAXVIDA;
    int aux=platc/3;
    LimpiaEnemigosLvl2(ave,car);
    for (j = 0; j < 3; j++)
    {
        pieza[j].status = 1;
        pieza[j].listo=0;
        pieza[j].pos.height = 163;
        pieza[j].pos.width = 114;

        if (j == 0)
        {
            pieza[j].pos.y = plat[platc - 1].pos.y - pieza[j].pos.height;
            pieza[j].pos.x = plat[platc - 1].pos.x + plat[platc].pos.width / 2;
        }
        else
        {
            pieza[j].pos.y = plat[(platc - aux * j)].pos.y - pieza[j].pos.height;
            pieza[j].pos.x = plat[(platc - aux * j)].pos.x + plat[(platc - aux * j)].pos.width / 2;
        }
    }
}

int ColisionPlat2(Tplayer2 player, Tplat plat)
{
    if (player.pos.x <= plat.pos.x + plat.pos.width) // Si esta tocando el lado derecho de la plataforma n
    {
        if (plat.pos.x <= player.pos.x + ANCHOP) // si esta tocando el lado izquierdo de la platforma n
        {
            if (player.pos.y + player.pos.height <= (plat.pos.y + 30))
            {
                if (player.pos.y + player.pos.height >= plat.pos.y)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int Posicion1(int y0, float v0, float time, int g)
{
    return (y0 + v0 * time + (g ? GD1 : G1) * time * time);
}

int nivel3(int diflvl)
{
    SetTargetFPS(60);
    InitWindow(RANCHO, RALTO, "juego");
    srand(time(NULL));
    int j, i, k;
    int y0Cam;

    // contadores
    int frameC = 0;
    float time = 0;
    int c = 0;
    int igncolision = 0;
    int hitc = 0;
    int platc = 0;
    // int caminarc=0;

    // banderas
    int bsuelo = 0;
    int bdown = 0;
    // int caminar=0;
    int lookR = 1;
    int lookL = 0;
    int lookUp = 0;
    int lookDown = 0;
    int dash = 0;

    int fin = 0;

    // auxiliar
    int random;
    Trec aux;
    aux.height = 20;
    aux.width = 20;
    float grados;

    // Inicializacion ***************************************************************************************
    // Inicializacion Plataformas
    Tplat plat[MAXPLAT3];
    for (i = 0; i < MAXPLAT3; i++)
    {
        plat[i].pos.height = 30;
        plat[i].pos.width = 322;
        plat[i].status = 1;
        plat[i].flag = 0;
    }
    plat[0].pos.x = RANCHO - plat[1].pos.width - 300;
    plat[0].pos.y = 450;
    plat[1].pos.x = 100;
    plat[1].pos.y = 250;
    plat[2].pos.x = 800;
    plat[2].pos.y = -50;
    plat[3].pos.x = 250;
    plat[3].pos.y = -400;

    //** piezas **********************************************************************************************************************************
    Tpart pieza[3];

    for (j = 0; j < 3; j++)
    {
        pieza[j].status = 1;
        pieza[j].pos.height = 181;
        pieza[j].pos.width = 63;
        pieza[j].pos.x = plat[j + 1].pos.x + plat[j + 1].pos.width / 2 - pieza[j].pos.width / 2;
        pieza[j].pos.y = -1500;
        pieza[j].listo = 0;
    }

    int piezac = 0;
    int hitb = 0;
    // Inicializa la posicion
    Tplayer3 player;
    player.pos.height = ALTOP + 10;
    player.pos.width = 25;
    player.pos.x = CAMX - player.pos.width; // Posicion incial
    player.pos.y = SUELO;                   //""
    player.y0 = player.pos.y;
    player.v0 = 0;
    player.timeDash = 70;
    player.AtkC = 0;

    // vida
    player.vida.num = MAXVIDA;
    player.vida.pos.width = 25;
    player.vida.pos.height = 25;
    player.vida.pos.x = 30;
    player.vida.pos.y = 30;
    player.vida.time = 0;

    // Inicializacion enemigos
    Ttow torre[MAXTORRE];
    for (j = 0; j < MAXTORRE; j++)
    {
        torre[j].status = 0;
        torre[0].direccion = 0;
        torre[1].direccion = 1;
        torre[j].pos.x = 2000;
        torre[j].pos.y = 800;
        torre[j].pos.height = 40;
        torre[j].pos.width = 60;
        torre[j].atkC = 0;
        for (i = 0; i < MAXHITTORRE; i++)
        {
            torre[j].hit[i].status = 0;
            torre[j].hit[i].pos.x = 0;
            torre[j].hit[i].pos.y = 1500;
            torre[j].hit[i].pos.height = 20;
            torre[j].hit[i].pos.width = 20;
        }
    }

    Tovni ovni[MAXOVNI];
    for (i = 0; i < MAXOVNI; i++)
    {
        ovni[i].pos.height = 35;
        ovni[i].pos.width = 60;
        ovni[i].pos.x = 0;
        ovni[i].pos.y = 1300;
        ovni[i].status = 0;
    }
    ovni[0].direccion = 1;
    ovni[1].direccion = 0;

    Tlaser laser;
    laser.pos.height = 114;
    laser.pos.width = 168;
    laser.pos.x = player.pos.x;
    laser.pos.y = 1500;
    laser.status = 0;
    laser.atkC = 0;
    laser.mov = 1;
    laser.hit.height = 10;
    laser.hit.width = 3000;

    Thit3 hit[MAXHIT3];
    for (i = 0; i < MAXHIT3; i++)
    {
        hit[i].status = 0;
        hit[i].pos.width = RANCHO;
        hit[i].pos.height = 25;
        hit[i].pos.x = 1280;
        hit[i].pos.y = 1500;
    }

    Tcora dropVida[MAXDROPVIDA];

    for (i = 0; i < MAXDROPVIDA; i++)
    {
        dropVida[i].pos.width = 30;
        dropVida[i].pos.height = 30;
        dropVida[i].status = 0;
        dropVida[i].time = 0;
    }

    TatkSpeed dropASpeed[MAXDROPASPEED];
    for (i = 0; i < MAXDROPASPEED; i++)
    {
        dropASpeed[i].pos.width = 80;
        dropASpeed[i].pos.height = 60;
        dropASpeed[i].statusDraw = 0;
        dropASpeed[i].statusFun = 0;
        dropASpeed[i].time = 0;
        dropASpeed[i].duracion = DURACIONBUFF;
    }

    // Inicializacion camara
    Camera2D camara = {0};
    camara.target.x = 0;
    camara.target.y = 0;
    camara.offset.x = 0;
    camara.offset.y = 0;
    camara.rotation = 0;
    camara.zoom = 1;
    Vector2 org;
    Vector2 org1;
    Trec temp;

    // inicializacion para dibujado

    int framesAutom = 0;

    int framesSpeed = 8;
    int currentFrame = 0;

    int currentPersonaje = 0;
    int framesPersonaje = 0;

    int currentSalto = 0;
    int framesSalto = 0;
    /******************************************************** CARGAR TEXTURAS **************************************************************/
    Texture2D morado = LoadTexture("texturas\\ovni.png");
    Texture2D bala = LoadTexture("texturas\\balalvl3.png");
    Texture2D suelo = LoadTexture("texturas\\suelo3.png");
    Texture2D fondo = LoadTexture("texturas\\luna.png");
    Texture2D plat3 = LoadTexture("texturas\\plat3.png");
    Texture2D corazon = LoadTexture("texturas\\corazon.png");
    Texture2D laserG = LoadTexture("texturas\\laserGreen.png");
    Texture2D laserM = LoadTexture("texturas\\laserMorado.png");
    Texture2D Aspeed = LoadTexture("texturas\\AtkSpeed.png");

    Texture2D nave[3];
    nave[0] = LoadTexture("texturas\\pieza1_3.png");
    nave[1] = LoadTexture("texturas\\pieza2_3.png");
    nave[2] = LoadTexture("texturas\\pieza3_3.png");

    Texture2D towl[9];
    towl[0] = LoadTexture("texturas\\torrel270.png");
    towl[1] = LoadTexture("texturas\\torrel292.png");
    towl[2] = LoadTexture("texturas\\torrel315.png");
    towl[3] = LoadTexture("texturas\\torrel337.png");
    towl[4] = LoadTexture("texturas\\torrel0.png");
    towl[5] = LoadTexture("texturas\\torrel22.png");
    towl[6] = LoadTexture("texturas\\torrel45.png");
    towl[7] = LoadTexture("texturas\\torrel67.png");
    towl[8] = LoadTexture("texturas\\torrel90.png");
    Texture2D towr[9];
    towr[0] = LoadTexture("texturas\\torrer270.png");
    towr[1] = LoadTexture("texturas\\torrer247.png");
    towr[2] = LoadTexture("texturas\\torrer225.png");
    towr[3] = LoadTexture("texturas\\torrer192.png");
    towr[4] = LoadTexture("texturas\\torrer180.png");
    towr[5] = LoadTexture("texturas\\torrer158.png");
    towr[6] = LoadTexture("texturas\\torrer135.png");
    towr[7] = LoadTexture("texturas\\torrer112.png");
    towr[8] = LoadTexture("texturas\\torrer90.png");

    // jugador
    Texture2D jet[2];
    jet[0] = LoadTexture("texturas\\jetL.png");
    jet[1] = LoadTexture("texturas\\jetR.png");

    Texture2D hitR[3];
    hitR[0] = LoadTexture("texturas\\HitR0.png");
    hitR[1] = LoadTexture("texturas\\HitR1.png");
    hitR[2] = LoadTexture("texturas\\HitR2.png");
    Texture2D hitL[3];
    hitL[0] = LoadTexture("texturas\\HitL0.png");
    hitL[1] = LoadTexture("texturas\\HitL1.png");
    hitL[2] = LoadTexture("texturas\\HitL2.png");
    Texture2D laserRed[2];
    laserRed[1] = LoadTexture("texturas\\laserR.png");
    laserRed[0] = LoadTexture("texturas\\laserL.png");

    Texture2D caminar = LoadTexture("texturas/Cyborg_run.png");
    Rectangle framesCaminar = {0.0f, 0.0f, (float)caminar.width / 6, (float)caminar.height};
    Texture2D caminarizq = LoadTexture("texturas/Cyborg_run_left.png");
    Rectangle framesCaminarizq = {0.0f, 0.0f, (float)caminarizq.width / 6, (float)caminarizq.height};
    Texture2D reposo = LoadTexture("texturas/Cyborg_idle.png");
    Rectangle framesReposo = {0.0f, 0.0f, (float)reposo.width / 4, (float)reposo.height};
    Texture2D reposoizq = LoadTexture("texturas/Cyborg_idle_left.png");
    Rectangle framesReposoizq = {0.0f, 0.0f, (float)reposoizq.width / 4, (float)reposoizq.height};
    Texture2D danio = LoadTexture("texturas/Cyborg_hurt.png");
    Rectangle framesDanio = {0.0f, 0.0f, (float)danio.width, (float)danio.height};
    Texture2D salto = LoadTexture("texturas/Cyborg_jump.png");
    Rectangle frameSalto = {0.0f, 0.0f, (float)salto.width / 4, (float)salto.height};
    Texture2D saltoder = LoadTexture("texturas/Cyborg_jumpr.png");
    Rectangle frameSaltoder = {0.0f, 0.0f, (float)saltoder.width / 4, (float)saltoder.height};

    //**************************************************** CARGAR AUDIOS *******************************************************************

    InitAudioDevice();

    Sound dolor = LoadSound("sonidos/danio.wav");
    Sound RecPieza = LoadSound("sonidos/pieza.wav");
    Sound las = LoadSound("sonidos/laser.wav");
    Sound brinco = LoadSound("sonidos/salto.mp3");
    Sound sdash = LoadSound("sonidos/paso1.wav");
    Sound jetpack = LoadSound("sonidos/jetpack.mp3");
    Sound orbita = LoadSound("sonidos/oribita_nv3.mp3");
    Sound ovni_laser = LoadSound("sonidos/laser_ovni.mp3");
    Sound canion = LoadSound("sonidos/canion.mp3");
    Music musica_nv3 = LoadMusicStream("sonidos/nivel3_musica.mp3");

    SetSoundVolume(sdash, +10.0f);
    SetSoundVolume(jetpack, -0.5f);
    SetSoundVolume(orbita, -0.3f);
    SetMusicVolume(musica_nv3, -1.2);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        BeginMode2D(camara);
        time += 0.5;
        igncolision += 1;
        frameC++;
        player.timeDash++;
        player.AtkC++;
        player.vida.time++;

        torre[0].atkC++;
        torre[1].atkC++;

        //** terminar el nivel ***********************************************************************************
        if (pieza[0].status)
        {
            if (pieza[0].pos.y == SUELO - pieza[0].pos.height)
            {
                if (pieza[1].status)
                {
                    if (pieza[1].pos.y == SUELO - pieza[1].pos.height)
                    {
                        if (pieza[2].status)
                        {
                            if (pieza[2].pos.y == SUELO - pieza[2].pos.height)
                            {
                                if (!fin)
                                {
                                    time = 0;
                                }
                                fin = 1;
                                LimpiaEnemigosLvl3(torre, ovni);
                                if (time > 300)
                                {
                                    cinemaPuzleNivel3(diflvl);
                                    goto finNivel3;
                                }
                               
                            }
                        }
                    }
                }
            }
        }

        if (!fin)
        {
            //** reajusta posicion x ****************************************************************************************************
            if (player.pos.x < 0)
            {
                player.pos.x = 0;
            }
            else
            {
                if (player.pos.x > RANCHO - player.pos.width)
                {
                    player.pos.x = RANCHO - player.pos.width;
                }
            }

            //** reajusta posicion y ***************************************************************************************
            if (player.pos.y < -900)
            {
                player.pos.y = -900;
            }

            //** pieza **************************************************************************************************************************
            for (j = 0; j < 3; j++)
            {
                // drop
                if (pieza[j].listo)
                {
                    if (!pieza[j].status)
                    {
                        if (CheckPlayerColision(player.pos, pieza[j].pos))
                        {
                            pieza[j].status = 1;
                        }
                    }
                }

                // recolleccion
                if (!pieza[j].listo)
                {
                    if (pieza[j].status)
                    {
                        if (CheckPlayerColision(player.pos, pieza[j].pos))
                        {
                            PlaySound(RecPieza);
                            pieza[j].status = 0;
                            pieza[j].listo = 1;
                            pieza[j].pos.y = SUELO - pieza[j].pos.height;
                            piezac++;
                            switch (j)
                            {
                            case 0:
                                pieza[j].pos.x = 150;
                                break;
                            case 1:
                                pieza[j].pos.x = 213;
                                break;
                            case 2:
                                pieza[j].pos.x = 276;
                                break;
                            }
                            j = 3;
                        }
                    }
                }
            }

            // movimiento piezas
            if (frameC > 300)
            {
                if (!pieza[0].listo)
                {
                    if (pieza[0].status)
                    {
                        if (pieza[0].pos.y < plat[1].pos.y - pieza[0].pos.height)
                        {
                            pieza[0].pos.y += 4;
                        }
                        else
                        {
                            if (piezac < 1)
                            {
                                pieza[0].pos.y = plat[1].pos.y - pieza[0].pos.height;
                            }
                        }
                    }
                }
                if (frameC > 600)
                {
                    if (!pieza[1].listo)
                    {
                        if (pieza[1].status)
                        {
                            if (pieza[1].pos.y < plat[2].pos.y - pieza[1].pos.height)
                            {
                                pieza[1].pos.y += 4;
                            }
                            else
                            {
                                if (piezac < 2)
                                {
                                    pieza[1].pos.y = plat[2].pos.y - pieza[1].pos.height;
                                }
                            }
                        }
                    }

                    if (frameC > 900)
                    {
                        if (!pieza[2].listo)
                        {
                            if (pieza[2].status)
                            {
                                if (pieza[2].pos.y < plat[3].pos.y - pieza[2].pos.height)
                                {
                                    pieza[2].pos.y += 4;
                                }
                                else
                                {
                                    if (piezac < 3)
                                    {
                                        pieza[2].pos.y = plat[3].pos.y - pieza[2].pos.height;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // enemigos

            //** torreta **************************************************************************************************************************
            for (i = 0; i < MAXTORRE; i++)
            {
                if (torre[i].status)
                {
                    // ataque
                    for (j = 0; j < MAXHITTORRE; j++)
                    {
                        if (torre[i].atkC > TORREASPEED)
                        {

                            // disparo
                            if (torre[i].hit[j].status == 0)
                            {
                                if (torre[i].direccion)
                                {
                                    torre[i].hit[j].pos.x = torre[i].pos.x;
                                    torre[i].hit[j].pos.y = torre[i].pos.y;
                                    grados = CalculaAngulo3(torre[i].hit[j].pos, player.pos);
                                    CalculaComponentesVelocidad(TORREVPROYECTIL, grados, torre[i].hit[j].v);
                                    torre[i].atkC = 0;
                                    torre[i].hit[j].status = 1;
                                    j = MAXHITTORRE;
                                }
                                else
                                {
                                    torre[i].hit[j].pos.x = torre[i].pos.x + torre[i].pos.width;
                                    torre[i].hit[j].pos.y = torre[i].pos.y;
                                    grados = CalculaAngulo3(torre[i].hit[j].pos, player.pos);
                                    CalculaComponentesVelocidad(TORREVPROYECTIL, grados, torre[i].hit[j].v);
                                    torre[i].atkC = 0;
                                    torre[i].hit[j].status = 1;
                                    j = MAXHITTORRE;
                                }
                            }
                        }
                        else
                        {
                            //** ataaque ** movimiento
                            if (torre[i].hit[j].status)
                            {
                                PosicionObieto3(torre[i].hit[j].v.vx, torre[i].hit[j].v.vy, torre[i].hit[j].pos);

                                // si se paso del borde izquierdo
                                if (torre[i].hit[j].pos.x < 0 - torre[i].hit[j].pos.width)
                                {
                                    torre[i].hit[j].status = 0;
                                }
                                else
                                {
                                    // si se paso del borde derecho
                                    if (torre[i].hit[j].pos.x > RANCHO)
                                    {
                                        torre[i].hit[j].status = 0;
                                    }
                                }

                                // colision con jugador
                                if (player.vida.time > INVULERABILIDAD)
                                {
                                    if (CheckPlayerColision(player.pos, torre[i].hit[j].pos))
                                    {
                                        PlaySound(dolor);
                                        if (player.vida.num < 1)
                                        {
                                            piezac = 0;
                                            frameC = 0;
                                            muerteLvl3(player, torre, ovni, pieza, plat);
                                        }
                                        else
                                        {
                                            player.vida.num--;
                                            player.vida.time = 0;
                                        }
                                        j = MAXHITTORRE;
                                    }
                                }
                            }
                        }
                    }

                    // Colision con golpe (enemigo)
                    for (j = 0; j < MAXHIT3; j++)
                    {
                        if (hit[j].status)
                        {
                            if (hit[j].time > 10)
                            {
                                if (CheckMobColision(torre[i].pos, hit[j].pos))
                                {
                                    torre[i].status = 0;
                                    random = rand() % 10 + 1;
                                    if (random <= 4)
                                    {
                                        random = rand() % 2;
                                        if (random)
                                        {
                                            for (k = 0; k < MAXDROPVIDA; k++)
                                            {
                                                if (!dropVida[k].status)
                                                {
                                                    dropVida[k].status = 1;
                                                    dropVida[k].time = 0;
                                                    dropVida[k].pos.x = torre[i].pos.x;
                                                    dropVida[k].pos.y = torre[i].pos.y;
                                                    k = MAXDROPVIDA;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            for (k = 0; k < MAXDROPASPEED; k++)
                                            {
                                                if (!dropASpeed[k].statusDraw)
                                                {
                                                    if (!dropASpeed[k].statusFun)
                                                    {
                                                        dropASpeed[k].statusDraw = 1;
                                                        dropASpeed[k].statusFun = 0;
                                                        dropASpeed[k].time = 0;
                                                        dropASpeed[k].pos.x = torre[i].pos.x;
                                                        dropASpeed[k].pos.y = torre[i].pos.y;
                                                        k = MAXDROPASPEED;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    // Colision con jugador (enemigo)
                    if (player.vida.time > INVULERABILIDAD)
                    {
                        if (CheckPlayerColision(player.pos, torre[i].pos))
                        {
                            PlaySound(dolor);
                            if (player.vida.num < 1)
                            {
                                piezac = 0;
                                frameC = 0;
                                muerteLvl3(player, torre, ovni, pieza, plat);
                            }
                            else
                            {
                                player.vida.num--;
                                player.vida.time = 0;
                            }
                            i = MAXTORRE;
                        }
                    }
                }
                else
                {
                    // generacion
                    random = (rand() % 300) + 1;
                    if (random == 1)
                    {
                        if (torre[i].direccion)
                        {
                            torre[i].status = 1;
                            torre[i].pos.x = RANCHO - torre[i].pos.width - 10;
                            torre[i].pos.y = 50;
                            for (j = 0; j < MAXHITTORRE; j++)
                            {
                                torre[i].hit[j].status = 0;
                            }
                        }
                        else
                        {
                            torre[i].status = 1;
                            torre[i].pos.x = 10;
                            torre[i].pos.y = 50;
                            for (j = 0; j < MAXHITTORRE; j++)
                            {
                                torre[i].hit[j].status = 0;
                            }
                        }
                    }
                }
            }

            //** ovni ************************************************************************************************************
            for (i = 0; i < MAXOVNI; i++)
            {
                // comportameinto
                if (ovni[i].status)
                {
                    ovni[i].time++;
                    // movimiento enemigo **si sale de la pantalla se elimina**
                    if (ovni[i].direccion)
                    { // movimiento
                        ovni[i].pos.x -= OVNISPEED;
                        ovni[i].pos.y += OVNIAMP * cos(2 * M_PI / OVNILONG * ovni[i].time);

                        if (ovni[i].pos.x <= 0 - ovni[i].pos.width)
                        {
                            ovni[i].status = 0;
                        }
                    }
                    else
                    {
                        // movimiento
                        ovni[i].pos.x += OVNISPEED;
                        ovni[i].pos.y += OVNIAMP * cos(2 * M_PI / OVNILONG * ovni[i].time);
                        // eliminacion
                        if (ovni[i].pos.x > RANCHO + ovni[i].pos.width)
                        {
                            ovni[i].status = 0;
                        }
                    }

                    // Colision con golpe
                    for (j = 0; j < MAXHIT3; j++)
                    {
                        if (hit[j].status)
                        {
                            if (hit[i].time > 10)
                            {
                                if (CheckMobColision(ovni[i].pos, hit[j].pos))
                                {
                                    ovni[i].status = 0;
                                    random = rand() % 10 + 1;
                                    if (random <= 4)
                                    {
                                        random = rand() % 2;
                                        if (random)
                                        {
                                            for (k = 0; k < MAXDROPVIDA; k++)
                                            {
                                                if (!dropVida[k].status)
                                                {
                                                    dropVida[k].status = 1;
                                                    dropVida[k].time = 0;
                                                    dropVida[k].pos.x = ovni[i].pos.x;
                                                    dropVida[k].pos.y = ovni[i].pos.y;
                                                    k = MAXDROPVIDA;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            for (k = 0; k < MAXDROPASPEED; k++)
                                            {
                                                if (!dropASpeed[k].statusDraw)
                                                {
                                                    if (!dropASpeed[k].statusFun)
                                                    {
                                                        dropASpeed[k].statusDraw = 1;
                                                        dropASpeed[k].statusFun = 0;
                                                        dropASpeed[k].time = 0;
                                                        dropASpeed[k].pos.x = ovni[i].pos.x;
                                                        dropASpeed[k].pos.y = ovni[i].pos.y;
                                                        k = MAXDROPASPEED;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    // Colision con iugador
                    if (ovni[i].status)
                    {

                        if (player.vida.time > INVULERABILIDAD)
                        {
                            if (CheckPlayerColision(player.pos, ovni[i].pos))
                            {
                                PlaySound(dolor);
                                if (player.vida.num < 1)
                                {
                                    piezac = 0;
                                    frameC = 0;
                                    muerteLvl3(player, torre, ovni, pieza, plat);
                                }
                                else
                                {
                                    player.vida.num--;
                                    player.vida.time = 0;
                                }
                                i = MAXOVNI;
                            }
                        }
                    }
                }
                else
                {
                    // generacion
                    random = (rand() % 100) + 1;
                    if (random == 1)
                    {
                        if (ovni[i].direccion)
                        {
                            PlaySound(orbita);
                            ovni[i].status = 1;
                            ovni[i].pos.x = RANCHO;
                            ovni[i].pos.y = player.pos.y;
                            ovni[i].time = 0;
                        }
                        else
                        {
                            PlaySound(orbita);
                            ovni[i].status = 1;
                            ovni[i].pos.x = 0 - ovni[i].pos.width;
                            ovni[i].pos.y = player.pos.y;
                            ovni[i].time = 0;
                        }
                    }
                }
            }

            //** laser ****************************************************************************************************************************
            if (laser.status)
            {
                laser.atkC++;
                // movimiento enemigo **si sale de la pantalla se elimina**
                if (laser.mov)
                {
                    laser.pos.x = RANCHO - player.pos.x - player.pos.width;

                    laser.pos.y = pow(((laser.pos.x - CAMX - laser.pos.width / 2) * 0.02), 2) + SUELO - 600;
                    if (player.pos.y < 400)
                    {
                        laser.pos.y -= fabs(SUELO - player.pos.y);
                        laser.pos.y += 250;
                    }

                    if (laser.pos.x < 0)
                    {
                        laser.pos.x = 0;
                    }
                    else
                    {
                        if (laser.pos.x + laser.pos.width > RANCHO)
                        {
                            laser.pos.x = RANCHO - laser.pos.width;
                        }
                    }
                }

                //** ataque *******************************************************************************************************************
                if (laser.atkC > 240)
                {
                    if (laser.atkC < 360)
                    {
                        if (laser.atkC == 241)
                        {
                            laser.hit.x = laser.pos.x + laser.pos.width / 2;
                            laser.hit.y = laser.pos.y + laser.pos.height / 2;
                            laser.grados = CalculaAngulo3(laser.pos, player.pos);
                            laser.mov = 0;
                            laser.time = 0;
                        }
                    }
                    else
                    {
                        laser.time++;
                        if (laser.time < 15)
                        {
                            for (i = 0; i < 1500; i += 10)
                            {

                                if (player.pos.x < laser.pos.x)
                                {
                                    grados = 275 + laser.grados;
                                    aux.x = laser.pos.x + tan(Radianes3(grados)) * i;
                                    aux.y = laser.pos.y + i;
                                }
                                else
                                {
                                    grados = 270 - laser.grados;
                                    aux.x = laser.pos.x - tan(Radianes3(grados)) * i;
                                    aux.y = laser.pos.y + i;
                                }
                                if (player.vida.time > INVULERABILIDAD)
                                {
                                    if (CheckPlayerColision(player.pos, aux))
                                    {
                                        if (player.vida.num < 1)
                                        {
                                            piezac = 0;
                                            frameC = 0;
                                            muerteLvl3(player, torre, ovni, pieza, plat);
                                        }
                                        else
                                        {
                                            player.vida.num--;
                                            player.vida.time = 0;
                                        }
                                        i = SUELO;
                                    }
                                }
                            }
                        }
                        else
                        {
                            laser.mov = 1;
                            laser.time = 0;
                            laser.atkC = 0;
                        }
                    }
                }
            }
            else
            {
                // generacion
                random = (rand() % 100) + 1;
                if (random == 1)
                {
                    laser.status = 1;
                    laser.pos.x = -laser.pos.width;
                    laser.pos.y = camara.target.y - 537;
                    laser.time = 0;
                    laser.atkC = 0;
                }
            }

            //** DROPS ************************************************************************************************************************
            for (i = 0; i < MAXDROPVIDA; i++)
            {
                if (dropVida[i].status)
                {
                    // tiempo
                    dropVida[i].time++;
                    // eliminacion
                    if (dropVida[i].time > DESPAWNTIME)
                    {
                        dropVida[i].status = 0;
                        dropVida[i].time = 0;
                    }

                    // curacion
                    if (CheckPlayerColision(player.pos, dropVida[i].pos))
                    {
                        player.vida.num++;
                        dropVida[i].status = 0;
                        dropVida[i].time = 0;
                    }
                    else
                    {
                        // movimiento
                        if (dropVida[i].pos.y < SUELO - dropVida[i].pos.height)
                        {
                            dropVida[i].pos.y += 2;
                        }
                        else
                        {
                            dropVida[i].pos.y = SUELO - dropVida[i].pos.height;
                        }
                    }
                }
            }

            for (i = 0; i < MAXDROPASPEED; i++)
            {
                if (dropASpeed[i].statusDraw)
                {
                    // tiempo
                    dropASpeed[i].time++;
                    // eliminacion
                    if (!dropASpeed[i].statusFun)
                    {
                        if (dropASpeed[i].time > DESPAWNTIME)
                        {
                            dropASpeed[i].statusDraw = 0;
                            dropASpeed[i].statusFun = 0;
                            dropASpeed[i].time = 0;
                        }
                        if (CheckPlayerColision(player.pos, dropASpeed[i].pos))
                        {
                            player.buff = 1;
                            dropASpeed[i].statusDraw = 0;
                            dropASpeed[i].statusFun = 1;
                            dropASpeed[i].time = 0;
                            dropASpeed[i].duracion = 0;
                        }
                        else
                        {
                            // movimiento
                            if (dropASpeed[i].pos.y < SUELO - dropASpeed[i].pos.height * 3)
                            {
                                dropASpeed[i].pos.y += 1;
                            }
                            else
                            {
                                dropASpeed[i].pos.y = SUELO - dropASpeed[i].pos.height * 3;
                            }
                        }
                    }
                }
                else
                {
                    if (player.buff)
                    {
                        if (dropASpeed[i].statusFun)
                        {
                            if (dropASpeed[i].duracion < DURACIONBUFF)
                            {
                                dropASpeed[i].duracion++;
                            }
                            else
                            {
                                player.buff = 0;
                                dropASpeed[i].statusFun = 0;
                                dropASpeed[i].statusDraw = 0;
                                dropASpeed[i].time = 0;
                                dropASpeed[i].duracion = 0;
                            }
                        }
                    }
                }
            }

            //** caluclar posicion y ********************************************************************************************************************************
            if (player.fall)
            {
                player.jetc++;
                if (bdown)
                {
                    if (velocidad(player.v0, time) > 0)
                    {
                        if (++c == 1)
                        {
                            player.v0 = velocidad(player.v0, time); // velocidad inicial igual a velocidad actual
                            player.y0 = player.pos.y;
                            time = 1;
                        }
                    }
                    else
                    {
                        Reposo3(time, player.v0, player.y0, player.pos.y);
                    }

                    // jetpack *******************
                    if (!player.jet) // si no esta usando el jetpack calcula caida
                    {
                        player.pos.y = Posicion3(player.y0, player.v0, time, bdown); // y=y0+v0*t+G*t^2  caida acelerada
                    }
                    else
                    {
                        player.jet = JetPack(time, player.v0, player.y0, player.pos.y, bdown); // inicializa un minisalto cuando se suelte abajo
                                                                                               // hace mas comodo el uso del jetpack
                        player.pos.y += VY3;                                                    // sube con velocidad constante
                        bdown = 0;
                    }
                }
                else
                {

                    // jetpack***********
                    if (!player.jet) // si no esta usando el jetpack calcula caida
                    {
                        player.pos.y = Posicion3(player.y0, player.v0, time, bdown); // y=y0+v0*t+G*t^2   //calcula caida
                    }
                    else
                    {
                        player.jet = JetPack(time, player.v0, player.y0, player.pos.y, bdown); // inicializa un minisalto cuando se suelte abajo
                                                                                               // hace mas comodo el uso del jetpack
                        player.pos.y += VY3;
                    }
                }
            }

            //** colisiones ********************************************************************************************************************************
            // v=v0*2*G*t derivada de la posicion=velocidad
            // suelo
            if (player.pos.y + player.pos.height > SUELO)
            {
                player.pos.y = SUELO - player.pos.height;
                Reposo3(time, player.v0, player.y0, player.pos.y);
                player.fall = 0;
                bsuelo = 1;
                player.jump = 1;
                player.jumpjump = 0;
                player.jet = 0;
            }

            // plataformas
            if (igncolision > 35)
            {
                // plataforma cuando cae
                if (velocidad(player.v0, time) > 0)
                {
                    for (j = 0; j < MAXPLAT3; j++)
                    {
                        if (plat[j].status)
                        {
                            if (ColisionPlat3(player, plat[j]))
                            {
                                player.pos.y = plat[j].pos.y - player.pos.height;
                                Reposo3(time, player.v0, player.y0, player.pos.y);
                                player.fall = 0;
                                plat[j].flag = 1;
                                player.jump = 1;
                                player.jumpjump = 0;
                                bdown = 0;
                                player.jet = 0;
                            }
                        }
                    }
                }
            }

            // si salio de la paltaforma
            for (j = 0; j < MAXPLAT3; j++)
            {
                if (plat[j].status)
                {
                    if (plat[j].flag)
                    {
                        if (!ColisionPlat3(player, plat[j]))
                        {
                            Reposo3(time, player.v0, player.y0, player.pos.y);
                            player.fall = 1;
                            plat[j].flag = 0;
                            player.jump = 0;
                            player.jumpjump = 0;
                            bdown = 0;
                            player.jet = 0;
                        }
                    }
                }
            }

            //** golpe ********************************************************************************************************************************
            for (i = 0; i < MAXHIT3; i++)
            {
                //** movimiento del disparo ***********************************************************************************
                if (hit[i].status)
                {
                    //** Eliminacion del proyectil *******************************************************************************
                    hit[i].time++;
                    if (hit[i].time < 25)
                    {
                        hitb = 1;
                        if (hit[i].time > 10)
                        {
                            hit[i].pos.y = player.pos.y - 18;
                            if (hit[i].direccion)
                            {
                                hit[i].pos.x = player.pos.x + player.pos.width * 3 + 3;
                            }
                            else
                            {
                                hit[i].pos.x = player.pos.x - player.pos.width * 3 - hit[i].pos.width + 17;
                            }
                        }
                    }
                    else
                    {
                        hitb = 0;
                        hit[i].status = 0;
                        hit[i].time = 0;
                        hit[i].pos.x = 1500;
                        hit[i].pos.y = -300;
                    }
                }
            }

            //** dash ********************************************************************************************************************************
            if (dash)
            {
                if (player.timeDash < 20)
                {
                    if (lookR)
                    {
                        player.pos.x += VD3;
                    }
                    else
                    {
                        if (lookL)
                        {
                            player.pos.x -= VD3;
                        }
                    }
                }
                else
                {
                    player.jump == 0;
                    player.fall = 1;
                    dash = Reposo3(time, player.v0, player.y0, player.pos.y);
                }
            }

            //** camara ********************************************************************************************************************************
            if (player.pos.y > 400)
            {
                camara.target.y = 0;
                camara.offset.y = 0;
            }
            else
            {
                camara.target.y = player.pos.y;
                camara.offset.y = 400;
            }

            //** intput ********************************************************************************************************************************
            // hit
            if (IsKeyPressed(KEY_X))
            {
                for (i = 0; i < MAXHIT3; i++)
                {
                    Direccioniugador3(lookL, lookR, lookUp, lookDown, player);
                    if (!player.buff) //** Meiora ******************************************************************************************************
                    {
                        if (player.AtkC > VATAQUE3)
                        {
                            if (!hit[i].status)
                            {
                                hit[i].pos.y = player.pos.y + player.pos.height / 4;
                                Direccioniugador3(lookL, lookR, lookL, lookDown, player);
                                if (lookR)
                                {
                                    hit[i].direccion = 1;
                                    hit[i].pos.x = player.pos.x + player.pos.width / 2;
                                }
                                else
                                {
                                    if (lookL)
                                    {
                                        hit[i].direccion = 0;
                                        hit[i].pos.x = player.pos.x + player.pos.width / 2 - RANCHO;
                                    }
                                }
                                hit[i].status = 1;
                                hit[i].time = 0;
                                player.AtkC = 0;
                                i = MAXHIT3;
                            }
                        }
                    }
                    else
                    {
                        if (player.AtkC > VATAQUEBUFF3)
                        {
                            if (!hit[i].status)
                            {
                                hit[i].pos.y = player.pos.y + player.pos.height / 4;
                                hit[i].pos.x = player.pos.x + player.pos.width / 2;
                                Direccioniugador3(lookL, lookR, lookL, lookDown, player);
                                if (lookR)
                                {
                                    hit[i].direccion = 1;
                                }
                                else
                                {
                                    if (lookL)
                                    {
                                        hit[i].direccion = 0;
                                    }
                                }
                                hit[i].status = 1;
                                hit[i].time = 0;
                                player.AtkC = 0;
                                i = MAXHIT3;
                            }
                        }
                    }
                }
            }

            // dash KEY C
            if (player.pos.x < 1250)
            {
                if (player.pos.x > plat[platc - 1].pos.x - 590)
                {
                    if (player.timeDash > 80)
                    {
                        if (!dash)
                        {
                            if (IsKeyPressed(KEY_C))
                            {
                                PlaySound(sdash);
                                dash = 1;
                                player.timeDash = 0;
                                Reposo3(time, player.v0, player.y0, player.pos.y);
                                player.fall = 0;
                                player.jump = 0;
                                player.jumpjump = 0;
                            }
                        }
                    }
                }
            }

            if (!dash) // right left
            {
                if (IsKeyDown(KEY_RIGHT))
                {
                    if (player.pos.x < 1280)
                    {
                        player.x0 = player.pos.x;
                        player.pos.x += VX3;
                        lookR = 1;
                        lookL = 0;
                    }
                }
                else
                {
                    if (IsKeyDown(KEY_LEFT))
                    {
                        if (player.pos.x > plat[platc - 1].pos.x - 610)
                        {
                            player.x0 = player.pos.x;
                            player.pos.x -= VX3;
                            lookR = 0;
                            lookL = 1;
                        }
                    }
                }
            }

            if (!dash) // up down
            {
                if (IsKeyDown(KEY_UP))
                {
                    if (player.jump)
                    {
                        PlaySound(brinco);
                        Reposo3(time, player.v0, player.y0, player.pos.y);
                        Salto1(time, player.v0, player.y0, player.pos.y);
                        player.fall = 1;
                        if (player.jumpjump) //! doblesalto
                        {
                            PlaySound(brinco);
                            player.jump = 1;
                            player.jumpjump = 0;
                        }
                        else
                        {
                            player.jump = 0;
                        }
                        for (j = 0; j < MAXPLAT3; j++)
                        {
                            if (plat[j].status)
                            {
                                plat[j].flag = 0;
                            }
                        }
                        player.jetc = 0;
                        bsuelo = 0;
                        bdown = 0;
                    }
                    else
                    {
                        if (IsKeyPressed(KEY_UP))
                        {
                            PlaySound(jetpack);
                        }
                        if (player.jetc > 60)
                        {
                            player.jet = 1; // esta usando jetpack
                            c = 0;          // habilita bajar rapido
                        }
                    }
                }
                else
                {
                    if (IsKeyPressed(KEY_DOWN))
                    {
                        for (j = 0; j < MAXPLAT3; j++)
                        {
                            if (plat[j].flag)
                            {
                                // if(IsKeyPressedRepeat(KEY_DOWN))
                                {
                                    player.fall = 1;
                                    igncolision = 0;
                                    bdown = 0;
                                }
                            }
                            else
                            {

                                bdown = 1;
                                player.fall = 1;
                                c = 0;
                            }
                        }
                    }
                }
            }
        }
        ClearBackground(BLANK);
        PlayMusicStream(musica_nv3);
        UpdateMusicStream(musica_nv3);
        DrawTexture(fondo, 0, -1300, WHITE);
        org.x = laser.pos.x + laser.pos.width / 2;
        org.y = laser.pos.y + laser.pos.height / 2;
        org1.x = 0;
        org1.y = 0;
        // jugador
        // jetpack
        Direccioniugador3(lookL, lookR, lookUp, lookDown, player);
        if (lookR)
        {
            DrawTexture(jet[1], player.pos.x - 45, player.pos.y - 10, WHITE);
        }
        else
        {
            if (lookL)
            {
                DrawTexture(jet[0], player.pos.x + player.pos.width - 10, player.pos.y - 10, WHITE);
            }
            else
            {
                DrawTexture(jet[1], player.pos.x - 45, player.pos.y - 10, WHITE);
            }
        }
        if (!hitb)
        {
            if (player.fall)
            {
                framesSalto++;
                if (framesSalto >= (60 / framesSpeed))
                {
                    framesSalto = 0;
                    currentSalto++;

                    if (currentSalto > 3)
                        currentSalto = 0;
                    frameSalto.x = (float)currentSalto * (float)salto.width / 4;
                    frameSaltoder.x = (float)currentSalto * (float)saltoder.width / 4;
                }
                if (lookL)
                {
                    DrawTextureRec(salto, frameSalto, Vector2{player.pos.x - 80, player.pos.y - 50}, WHITE);
                }
                else
                {
                    if (lookR)
                    {
                        DrawTextureRec(saltoder, frameSalto, Vector2{player.pos.x - 40, player.pos.y - 50}, WHITE);
                    }
                    else
                    {
                        DrawTextureRec(saltoder, frameSalto, Vector2{player.pos.x - 40, player.pos.y - 50}, WHITE);
                    }
                }
            }
            else
            {
                if (IsKeyDown(KEY_RIGHT))
                {
                    framesPersonaje++;
                    framesSalto = 0;
                    if (framesPersonaje >= (60 / framesSpeed))
                    {
                        framesPersonaje = 0;
                        currentPersonaje++;

                        if (currentPersonaje > 5)
                            currentPersonaje = 0;
                        framesCaminar.x = (float)currentPersonaje * (float)caminar.width / 6;
                    }
                    DrawTextureRec(caminar, framesCaminar, Vector2{player.pos.x - 40, player.pos.y - 75}, WHITE);
                }
                else if (IsKeyDown(KEY_LEFT))
                {
                    framesPersonaje++;
                    if (framesPersonaje >= (60 / framesSpeed))
                    {
                        framesPersonaje = 0;
                        currentPersonaje++;

                        if (currentPersonaje > 5)
                            currentPersonaje = 0;
                        framesCaminarizq.x = (float)currentPersonaje * (float)caminarizq.width / 6;
                    }
                    DrawTextureRec(caminarizq, framesCaminarizq, Vector2{player.pos.x - 80, player.pos.y - 75}, WHITE);
                }
                else
                {
                    framesPersonaje = 0;
                    if (lookL)
                    {
                        DrawTextureRec(reposoizq, framesReposoizq, Vector2{player.pos.x - 85, player.pos.y - 75}, WHITE);
                    }
                    else
                    {
                        if (lookR)
                        {
                            DrawTextureRec(reposo, framesReposo, Vector2{player.pos.x - 30, player.pos.y - 75}, WHITE);
                        }
                        else
                        {
                            DrawTextureRec(reposo, framesReposo, Vector2{player.pos.x - 30, player.pos.y - 75}, WHITE);
                        }
                    }
                }
            }
        }

        // suelo
        DrawTexture(suelo, 0, SUELO - 4, WHITE);
        // printf("\n centro jux = %f centro laser = %f\n",player.pos.x+player.pos.width/2,laser.pos.x+laser.pos.width/2);
        // laser

        if (laser.time > 1)
        {
            if (laser.time < 15)
            {
                PlaySound(ovni_laser);
                DrawTextureEx(laserRed[1], org, 360 - laser.grados, 1, WHITE);
            }
        }

        if (laser.atkC > 240)
        {
            if (laser.atkC < 360)
            {
                DrawTexture(laserG, laser.pos.x, laser.pos.y, WHITE);
            }
            else
            {
                DrawTexture(laserM, laser.pos.x, laser.pos.y, WHITE);
            }
        }
        else
        {
            DrawTexture(laserM, laser.pos.x, laser.pos.y, WHITE);
        }

        // vida
        for (i = 1; i <= player.vida.num; i++)
        {
            if (player.pos.y > 400)
            {
                player.vida.pos.y = 25;
            }
            else
            {
                player.vida.pos.y = player.pos.y - 375;
            }
            DrawTexture(corazon, player.vida.pos.x, player.vida.pos.y, WHITE);
            player.vida.pos.x += 25 + player.vida.pos.width;
        }
        player.vida.pos.x = 25;

        // plataformas
        for (j = 0; j < MAXPLAT3; j++)
        {
            DrawTexture(plat3, plat[j].pos.x, plat[j].pos.y, WHITE);
        }
        // enemigos
        for (j = 0; j < MAXTORRE; j++)
        {
            if (torre[j].status)
            {
                for (i = 0; i < MAXHITTORRE; i++)
                {
                    if (torre[j].hit[i].status)
                    {
                        DrawTexture(bala, torre[j].hit[i].pos.x - 4, torre[j].hit[i].pos.y - 4, WHITE);
                        PlaySound(canion);
                    }
                }

                if (torre[j].direccion)
                {
                    grados = CalculaAngulo3(torre[j].pos, player.pos);
                    if (grados <= 112)
                    {
                        DrawTexture(towr[8], torre[j].pos.x - 5, torre[j].pos.y - 5, WHITE);
                    }
                    else
                    {
                        if (grados <= 135)
                        {
                            DrawTexture(towr[7], torre[j].pos.x - 5, torre[j].pos.y - 5, WHITE);
                        }
                        else
                        {
                            if (grados <= 158)
                            {
                                DrawTexture(towr[6], torre[j].pos.x - 5, torre[j].pos.y - 5, WHITE);
                            }
                            else
                            {
                                if (grados <= 180)
                                {
                                    DrawTexture(towr[5], torre[j].pos.x - 5, torre[j].pos.y - 5, WHITE);
                                }
                                else
                                {
                                    if (grados <= 192)
                                    {
                                        DrawTexture(towr[4], torre[j].pos.x - 5, torre[j].pos.y - 5, WHITE);
                                    }
                                    else
                                    {
                                        if (grados <= 225)
                                        {
                                            DrawTexture(towr[3], torre[j].pos.x - 5, torre[j].pos.y - 5, WHITE);
                                        }
                                        else
                                        {
                                            if (grados <= 247)
                                            {
                                                DrawTexture(towr[2], torre[j].pos.x - 5, torre[j].pos.y - 5, WHITE);
                                            }
                                            else
                                            {
                                                if (grados <= 270)
                                                {
                                                    DrawTexture(towr[1], torre[j].pos.x - 5, torre[j].pos.y - 5, WHITE);
                                                }
                                                else
                                                {
                                                    if (grados > 270)
                                                    {
                                                        DrawTexture(towr[0], torre[j].pos.x - 5, torre[j].pos.y - 5, WHITE);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    grados = CalculaAngulo3(torre[j].pos, player.pos) + 90;

                    if (grados > 360)
                    {
                        grados -= 360;
                    }

                    if (grados > 90)
                    {
                        if (grados <= 270)
                        {
                            if (grados <= 112)
                            {
                                DrawTexture(towl[5], torre[j].pos.x - 5, torre[j].pos.y - 5, WHITE);
                            }
                            else
                            {
                                if (grados <= 135)
                                {
                                    DrawTexture(towl[6], torre[j].pos.x - 5, torre[j].pos.y - 5, WHITE);
                                }
                                else
                                {
                                    if (grados <= 158)
                                    {
                                        DrawTexture(towl[7], torre[j].pos.x - 5, torre[j].pos.y - 5, WHITE);
                                    }
                                    else
                                    {
                                        DrawTexture(towl[8], torre[j].pos.x - 5, torre[j].pos.y - 5, WHITE);
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        if (grados <= 22)
                        {
                            DrawTexture(towl[1], torre[j].pos.x - 5, torre[j].pos.y - 5, WHITE);
                        }
                        else
                        {
                            if (grados <= 45)
                            {
                                DrawTexture(towl[2], torre[j].pos.x - 5, torre[j].pos.y - 5, WHITE);
                            }
                            else
                            {
                                if (grados <= 67)
                                {
                                    DrawTexture(towl[3], torre[j].pos.x - 5, torre[j].pos.y - 5, WHITE);
                                }
                                else
                                {
                                    if (grados <= 90)
                                    {
                                        DrawTexture(towl[4], torre[j].pos.x - 5, torre[j].pos.y - 5, WHITE);
                                    }
                                }
                            }
                        }
                    }
                    if (grados >= 337)
                    {
                        DrawTexture(towl[0], torre[j].pos.x - 5, torre[j].pos.y - 5, WHITE);
                    }
                }
            }
        }
        for (i = 0; i < MAXOVNI; i++)
        {
            if (ovni[i].status)
            {
                DrawTexture(morado, ovni[i].pos.x - 12.5, ovni[i].pos.y - 7.5, WHITE);
            }
        }
        // piezas
        for (j = 0; j < 3; j++)
        {
            if (pieza[j].status)
            {
                DrawTexture(nave[j], pieza[j].pos.x, pieza[j].pos.y, WHITE);
            }
        }
        // golpe
        for (i = 0; i < MAXHIT3; i++)
        {
            if (hit[i].status)
            {

                if (lookR)
                {
                    if (hit[i].time < 5)
                    {
                        DrawTexture(hitR[0], player.pos.x - 15, player.pos.y - 35, WHITE);
                    }
                    else
                    {
                        if (hit[i].time < 10)
                        {
                            DrawTexture(hitR[1], player.pos.x - 25, player.pos.y - 35, WHITE);
                        }
                        else
                        {
                            PlaySound(las);
                            DrawTexture(laserRed[1], hit[i].pos.x, hit[i].pos.y - 10, WHITE);
                            DrawTexture(hitR[2], player.pos.x - 35, player.pos.y - 35, WHITE);
                        }
                    }
                }
                else
                {
                    if (lookL)
                    {
                        if (hit[i].time < 5)
                        {
                            DrawTexture(hitL[0], player.pos.x - 45, player.pos.y - 35, WHITE);
                        }
                        else
                        {
                            if (hit[i].time < 10)
                            {
                                DrawTexture(hitL[1], player.pos.x - 55, player.pos.y - 35, WHITE);
                            }
                            else
                            {
                                PlaySound(las);
                                DrawTexture(laserRed[0], hit[i].pos.x + 190, hit[i].pos.y - 10, YELLOW);
                                DrawTexture(hitL[2], player.pos.x - 60, player.pos.y - 35, WHITE);
                            }
                        }
                    }
                }
            }
        }
        // DROPS
        for (i = 0; i < MAXDROPVIDA; i++)
        {
            if (dropVida[i].status)
            {
                DrawTexture(corazon, dropVida[i].pos.x, dropVida[i].pos.y, WHITE);
            }
        }
        for (i = 0; i < MAXDROPASPEED; i++)
        {
            if (dropASpeed[i].statusDraw)
            {
                if (!dropASpeed[i].statusFun)
                {
                    DrawTexture(Aspeed, dropASpeed[i].pos.x, dropASpeed[i].pos.y, WHITE);
                }
            }
        }
        EndMode2D();
        EndDrawing();
    }

    for (i = 0; i < 9; i++)
    {
        UnloadTexture(towl[i]);
        UnloadTexture(towr[i]);
    }
    for (i = 0; i < 3; i++)
    {
        UnloadTexture(nave[i]);
    }
    finNivel3:
        UnloadTexture(jet[0]);
        UnloadTexture(jet[1]);
        UnloadTexture(morado);
        UnloadTexture(bala);
}

float velocidad(float v0, float time)
{
    return (v0 + 2 * G3 * time);
}

int ColisionPlat3(Tplayer3 player, Tplat plat)
{
    if (player.pos.x <= plat.pos.x + plat.pos.width) // Si esta tocando el lado derecho de la plataforma n
    {
        if (plat.pos.x <= player.pos.x + ANCHOP) // si esta tocando el lado izquierdo de la platforma n
        {
            if (player.pos.y + player.pos.height <= (plat.pos.y + 30))
            {
                if (player.pos.y + player.pos.height >= plat.pos.y)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int Reposo3(float &time, float &v0, int &y0, int y)
{
    time = 0;
    v0 = 0;
    y0 = y;
    return 0;
}

int Salto1(float &time, float &v0, int &y0, int y)
{
    time = 0;
    y0 = y;
    v0 = VS3;
    return 0;
}

int Posicion(int y0, float v0, float time, int g)
{
    return (y0 + v0 * time + (g ? GD3 : G3) * time * time);
}

int CheckMobColision(Trec mob, Trec hit)
{
    if (mob.x < (hit.x + hit.width))
    {
        if ((mob.x + mob.width) > hit.x)
        {
            if (mob.y < (hit.y + hit.height))
            {
                if ((mob.y + mob.height) > hit.y)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void LimpiaEnemigosLvl3(Ttow torre[], Tovni ovni[])
{
    int j, i;
    for (j = 0; j < MAXTORRE; j++)
    {
        torre[j].status = 0;
        for (i = 0; i < MAXHITTORRE; i++)
        {
            torre[j].hit[i].status = 0;
            torre[j].hit[i].v.vx = 0;
            torre[j].hit[i].v.vy = 0;
            if (torre[j].direccion)
            {

                torre[j].hit[i].pos.x = -500;
            }
            else
            {
                torre[j].hit[i].pos.x = 1500;
            }
        }
    }
    for (i = 0; i < MAXOVNI; i++)
    {
        ovni[i].status = 0;
    }
}

int JetPack(float &time, float &v0, int &y0, int y, int bdown)
{
    if (!bdown)
    {
        time = 0;
        v0 = VSJ3;
        y0 = y;
    }
    else
    {
        Reposo3(time, v0, y0, y);
    }
    return 0;
}

void Direccioniugador3(int &L, int &R, int &Up, int &Down, Tplayer3 player)
{
    if (IsKeyDown(KEY_RIGHT))
    {
        if (IsKeyDown(KEY_UP))
        {
            R = 1;
            Up = 1;
            Down = 0;
            L = 0;
        }
        else
        {
            if (IsKeyDown(KEY_DOWN))
            {
                R = 1;
                Up = 0;
                Down = 1;
                L = 0;
            }
            else
            {
                R = 1;
                Up = 0;
                Down = 0;
                L = 0;
            }
        }
    }
    else
    {
        if (IsKeyDown(KEY_LEFT))
        {
            if (IsKeyDown(KEY_UP))
            {
                R = 0;
                Up = 1;
                Down = 0;
                L = 1;
            }
            else
            {
                if (IsKeyDown(KEY_DOWN))
                {
                    R = 0;
                    Up = 0;
                    Down = 1;
                    L = 1;
                }
                else
                {
                    R = 0;
                    Up = 0;
                    Down = 0;
                    L = 1;
                }
            }
        }
        else
        {
            if (IsKeyDown(KEY_UP))
            {
                R = 0;
                Up = 1;
                Down = 0;
                L = 0;
                if (player.x0 <= player.pos.x)
                {
                    R = 1;
                    Up = 0;
                    Down = 0;
                    L = 0;
                }
                else
                {
                    R = 0;
                    Up = 0;
                    Down = 0;
                    L = 1;
                }
            }
            else
            {
                if (IsKeyDown(KEY_DOWN))
                {
                    R = 0;
                    Up = 0;
                    Down = 1;
                    L = 0;
                    if (player.x0 <= player.pos.x)
                    {
                        R = 1;
                        Up = 0;
                        Down = 0;
                        L = 0;
                    }
                    else
                    {
                        R = 0;
                        Up = 0;
                        Down = 0;
                        L = 1;
                    }
                }
                else
                {
                    if (player.x0 <= player.pos.x)
                    {
                        R = 1;
                        Up = 0;
                        Down = 0;
                        L = 0;
                    }
                    else
                    {
                        R = 0;
                        Up = 0;
                        Down = 0;
                        L = 1;
                    }
                }
            }
        }
    }
}

void InicializaProyectil(int L, int R, int Up, int Down, Tplayer3 player, Thit &hit)
{
    hit.pos.y = player.pos.y + player.pos.height / 4;
    hit.pos.x = player.pos.x + player.pos.width / 2;
    if (R)
    {
        if (Up)
        {
            hit.direccion = 1;
        }
        else
        {
            if (Down)
            {
                hit.direccion = 7;
            }
            else
            {
                hit.direccion = 0;
            }
        }
    }
    else
    {
        if (L)
        {
            if (Up)
            {
                hit.direccion = 3;
            }
            else
            {
                if (Down)
                {
                    hit.direccion = 5;
                }
                else
                {
                    hit.direccion = 4;
                }
            }
        }
        else
        {
            if (Up)
            {
                hit.direccion = 2;
            }
            else
            {
                if (Down)
                {
                    hit.direccion = 6;
                }
            }
        }
    }
}

float CalculaAngulo3(Trec enemigo, Trec player)
{
    float difx = fabs(player.x + player.width / 2 - (enemigo.x + enemigo.width / 2));
    float dify = fabs(player.y + player.height / 2 - (enemigo.y + enemigo.height / 2));
    float a = atan2(difx, dify);
    a = a * 180 / M_PI;
    if (player.x > enemigo.x)
    {
        if (player.y > enemigo.y)
        {
            return (270 + a);
        }
        else
        {
            return (90 - a);
        }
    }
    else
    {
        if (player.y > enemigo.y)
        {
            return (270 - a);
        }
        else
        {
            return (90 + a);
        }
    }
    return 0;
}

void muerteLvl3(Tplayer3 &player, Ttow torre[], Tovni ovni[], Tpart pieza[], Tplat plat[])
{
    int j;
    player.pos.x = 400;   // Posicion incial
    player.pos.y = SUELO; //""
    player.y0 = player.pos.y;
    player.v0 = 0;
    player.timeDash = 70;
    player.vida.num = MAXVIDA;
    player.vida.time = 0;
    LimpiaEnemigosLvl3(torre, ovni);
    for (j = 0; j < 3; j++)
    {
        pieza[j].status = 1;
        pieza[j].listo = 0;
        pieza[j].pos.x = plat[j + 1].pos.x + plat[j + 1].pos.width / 2 - pieza[j].pos.width / 2;
        pieza[j].pos.y = -1500;
    }
}

