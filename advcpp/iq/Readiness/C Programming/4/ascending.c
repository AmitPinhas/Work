#include <stdio.h>

#define TRUE 1
#define FALSE 0

int Ascending(int a_num);
int AscendingRec(int a_num);

int main()
{
    if(Ascending(1279))
    {
        puts("PASS");
    }
    else
    {
        puts("FAIL");
    }

    if(Ascending(3871))
    {
        puts("FAIL");
    }
    else
    {
        puts("PASS");
    } 

    if(Ascending(279))
    {
        puts("PASS");
    }
    else
    {
        puts("FAIL");
    }  

    if(Ascending(01))
    {
        puts("PASS");
    }
    else
    {
        puts("FAIL");
    }           
    
    if(Ascending(-1234))
    {
        puts("PASS");
    }
    else
    {
        puts("FAIL");
    }        

    return 1;
}

int Ascending(int a_num)
{
    if(a_num < 0)
    {
        a_num *= -1;
    }

    if(a_num <= 9)
    {
        return TRUE;
    }


    return AscendingRec(a_num);
}

int AscendingRec(int a_num)
{
    char bigDigit;
    char smallDigit;

    if(a_num == 0)
    {
        return TRUE;
    }

    bigDigit = a_num % 10;
    a_num = a_num/10;
    smallDigit = a_num % 10;

    if(smallDigit > bigDigit)
    {
        return FALSE;
    }

    return AscendingRec(a_num);
}