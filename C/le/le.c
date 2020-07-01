#include <stdio.h>

int IsLE()
{
     int i = 1;
     char *ptr = (char*)&i;
     return (*ptr==1)?1:0;
}

int main()
{
     int res;
     res=IsLE();
     printf("%d\n",res);
     return 1;
}
