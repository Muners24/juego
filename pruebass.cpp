#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b, c;
    char op1, op2;
    char str[10];
    float res=0;
    gets(str);
    sscanf(str, "%d %c %d %c %d", &a, &op1, &b, &op2, &c);
    float af,bf,cf;
    af=float(a);
    bf=float(b);
    cf=float(c);
    printf("%f %c %f %c %f \n",af,op1,bf,op2,cf);
    int primer=0;
    int segundo=0;
    if(op1=='*'||op1=='/')
    {
        if(op1=='*')
        {   
            res+=af*bf;
            primer=1;
        }
        else
        {
            if(op1=='/')
            {
                res+=float(af/bf);
                primer=1;
            }
        }
    }
    else
    {
        if(op2=='*'||op2=='/')
        {
            if(op2=='*')
            {
                res+=bf*cf;
                segundo=1;
            }
            else
            {
                if(op2=='/')
                {
                    res+=float(bf/cf);
                    segundo=1;
                }
            }
        }
    }

    if(!segundo)
    {
        if(primer)
        {
            if(op2=='*'||op2=='/')
            {
                if(op2=='*')
                {
                    res=res*cf;
                    segundo=1;
                    printf("%f res\n",res);
                }
                else
                {
                    if(op2=='/')
                    {
                        res=float(res/cf);
                        segundo=1;
                    }
                }
            }
        }
        else
        {
            if(op2=='*'||op2=='/')
            {
                if(op2=='*')
                {
                    res=bf*cf;
                    segundo=1;
                }
                else
                {
                    if(op2=='/')
                    {
                        res+=float(bf/cf);
                        segundo=1;
                    }
                }
            }
        }
    }

    if(!primer)
    {
        if(segundo)
        {
            if(op1=='+')
            {
                res=af+res;
                primer=1;
            }
            else
            {
                if(op1=='-')
                {
                    res=af-res;
                    primer=1;
                }
            }
        }
        else
        {
            if(op1=='+')
            {
                res+=af+bf;
                primer=1;
            }
            else
            {
                if(op1=='-')
                {
                    res+=af-bf;
                    primer=1;
                }
            }
        }
    }

    if(!segundo)
    {
        if(primer)
        {
            if(op2=='+')
            {
                res=res+cf;
                segundo=1;
            }
            else
            {
                if(op2=='-')
                {
                    res=res-cf;
                    segundo=1;
                }
            }
        }
        else
        {
            if(op2=='+')
            {
                res+=bf+cf;
                segundo=1;
            }
            else
            {
                if(op2=='-')
                {
                    res+=bf-cf;
                    segundo=1;
                }
            } 
        }
    }
    printf("%f",res);
    return 0;
}