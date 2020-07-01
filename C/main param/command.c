#include <stdio.h>
/* #define DEBUG 1 */

int main(int argc, char *argv[])
{
     int num1 , num2 ;
     num1 = atoi(argv[1]);
     num2 = atoi(argv[2]);
     #ifdef DEBUG
     printf("%d\n" , argc);
     #endif
     printf("%d*%d = %d\n" ,num1,num2, num1*num2);
     return 1;
}
