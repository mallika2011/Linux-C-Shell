#include "headers.h"
pid_t pid;


void back(char *token[])
{
    curid++;
    pid = fork();
    if (pid < 0)
        perror("Error: Fork Failed\n");
    else if (pid == 0)
    {   
        
        int z=execvp(token[0], token);
        if(z<0)
            perror("myshell:Error\n");
        exit(0);
    }
    else
    {
        // printf("[1] %d\n", pid);
        pid_arr[curid]=pid;
    }
    return;
}