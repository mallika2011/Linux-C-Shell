#include "headers.h"

//********************************************** CD ***************************************************************//

void cd(char path[])
{
    // printf("Into the cd function\nPath =%s\n", path);
    
    if (strcmp(path, "~") == 0)
    {
        chdir(pseudo_home);
        // printf("Path to go to =%s\n", path);
        char cur[1000];
        getcwd(cur, sizeof(cur));
        // printf("current dir = %s\n", cur);

        return;
    }
    else if (path[0] == '~' && strlen(path) > 1)
        path[0] = '.';

    // printf("Path to go to =%s\n", path);
    int check = chdir(path);
    if (check < 0)
    {
        printf("cd: no such file or directory: %s\n", path);
    }
    else
    {
        char cur[1000];
        getcwd(cur, sizeof(cur));
        // printf("current dir = %s\n", cur);
    }
    return;
}
