#include <stdio.h>
#include <stdlib.h>

typedef struct _tabla
{
    int num;
    char opRight[2];
    char opDown[2];
    int status;
}Ttab;

int main()
{
    FILE *fa;
    fa=fopen("dif1_1.txt","r");
    int i,j;
    Ttab tabla[2][3];
    float respuestasx[3];
    float respuestasy[2];

    if(fa)
    {
        for(i=0;i<2;i++)
        {
            for(j=0;j<3;j++)
            {
                fscanf(fa,"%d %c %c",&tabla[i][j].num,&tabla[i][j].opRight[0],&tabla[i][j].opDown[0]);
                printf("%d %c %c",tabla[i][j].num,tabla[i][j].opRight[0],tabla[i][j].opDown[0]);
            }
        }
            fscanf(fa," %f %f %f %f %f ",&respuestasy[0],&respuestasy[1],&respuestasx[0],&respuestasx[1],&respuestasx[2]);
            printf(" %f %f %f %f %f ",respuestasy[0],respuestasy[1],respuestasx[0],respuestasx[1],respuestasx[2]);
            fclose(fa);
    }
    system("pause");
    return 0;
}