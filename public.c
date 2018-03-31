#include<stdio.h>

char *mygets(char *src, int size)
{ 
    char *dest = src;
    for(; dest<src+size-1; )
    {
        *dest = getchar();
        if(*src == '\n')
            continue;
        if(*dest == '\n')
            break;
        dest++;
    }
    if(*dest != '\n')
        while(getchar() != '\n');
    *dest = '\0';
    return src;
}

long myscanf()
{
    long value = 0;
    scanf("%ld", &value);
    getchar();
    return value;
}


