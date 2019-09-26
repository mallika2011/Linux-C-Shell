#include "headers.h"

void echo(char *token[], ll k)
{
    // printf("Entered echo \n");
    char st[10000] = "", string[10000];
    for (ll o = 1; o <= k - 1; o++)
    {
        strcat(st, token[o]);
        strcat(st, " ");
    }

    strcpy(string, st);
    ll len = strlen(string);
    if (string[0] == '"' && string[len - 2] == '"')
    {
        string[len - 2] = '\0';
        printf("%s", &string[1]);
    }
    else
        printf("%s", string);
    return;
}