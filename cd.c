#include "headers.h"

//********************************************** CD ***************************************************************//

void cd(char *token[], ll k)
{
    if (k > 2)
        perror("myshell: Error: Too many arguments\n");

    if (k > 1)
    {
        char path[10000];
        strcpy(path, token[1]);
        if (strcmp(path, "~") == 0)
        {
            chdir(pseudo_home);
            char cur[1000];
            getcwd(cur, sizeof(cur));
            return;
        }
        else if (path[0] == '~' && strlen(path) > 1)
            path[0] = '.';
        int check = chdir(path);
        if (check < 0)
        {
            printf("cd: no such file or directory: %s\n", path);
        }
        else
        {
            char cur[1000];
            getcwd(cur, sizeof(cur));
        }
        return;
    }
    else
        chdir(pseudo_home);
}
