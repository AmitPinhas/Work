#include <stdio.h>

#define SIZE_ASCII 256

void Replace(char *a_first, const char *a_second, char a_newChar);

int main()
{
    char first[] = "hello world";
    char second[] = {'e','o','d','\0'};
    Replace(first, second, '/');

    puts(first);


    return 1;
}

void Replace(char *a_first, const char *a_second, char a_newChar)
{
    char lut[SIZE_ASCII] = {0};

    size_t i;

    if(NULL == a_first || NULL == a_second)
    {
        return;
    }

    for(i = 0; a_second[i] != '\0'; ++i)
    {
        lut[a_second[i] - 'a'] = '1';
    }

    for(i = 0; a_first[i] != '\0'; ++i)
    {
        if(lut[a_first[i] - 'a'])
        {
            a_first[i] = a_newChar;
        }
    }

    return;
}