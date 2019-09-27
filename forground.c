#include "headers.h"

void fore(char **token)
{
    pid_t pid;

    pid = fork();
    current_fore.pid = pid;
    strcpy(current_fore.name, token[0]);

    if (pid < 0)
        perror("Error: Fork Failed\n");
    else if (pid == 0)
    {
        // printf("%s %s\n", token[0], token[1]);
        int f = execvp(token[0], token);
        // printf("f= %d\n",f);
        if (f < 0)
        {
            perror("Error: exec failed\n");
            printf("myshell: command not found: %s\n", token[0]);
        }
        exit(0);
    }
    else
    {
        int status;
        waitpid(pid,&status,WUNTRACED);
        // printf("before %d\n",childid);
    }
}