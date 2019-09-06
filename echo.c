#include "headers.h"

void echo(char string[])
{
    // printf("Entered echo \n");
    ll len=strlen(string);
    if(string[0]=='"' && string[len-2]=='"')
    {
        string[len-2]='\0';
        printf("%s",&string[1]);
    }
    else
    printf("%s",string);
    return;
}