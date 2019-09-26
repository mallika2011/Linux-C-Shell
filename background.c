#include "headers.h"
pid_t pid;

void back(char *token[])
{
    curid++;
    pid = fork();
    setpgid(0, 0);
    if (pid < 0)
        perror("Error: Fork Failed\n");
    else if (pid == 0)
    {
        pid_t p = getpid();
        int z = execvp(token[0], token);
        if (z < 0)
            perror("myshell:Error\n");

        if (strcmp(token[0], "vim") == 0)
            kill(p, 19);
        exit(0);
    }
    else
    {
        job_count++;
        printf("[%lld] %d %s\n", job_count, pid, token[0]); // DETAILS OF BG PROCESS
        job_arr[job_count].pid = pid;
        strcpy(job_arr[job_count].name, token[0]); // TO KILL PROCESSES
    }

    return;
}