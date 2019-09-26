#include "headers.h"

void settingenv(char *token[], ll k)
{
    if (k != 3)
        printf("Error: Incorrect number of arguments\n");

    else
    {
        ll z = setenv(token[1], token[2], 1);
        if (z < 0)
            perror("Error:\n");
    }
}

void unsettingenv(char *token[], ll k)
{
    if (k != 2)
        printf("Error: Incorrect number of arguments\n");
    else
    {
        ll z = unsetenv(token[1]);
        if (z < 0)
            perror("Error:\n");
    }
}