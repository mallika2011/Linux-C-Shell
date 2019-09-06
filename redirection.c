#include "headers.h"

int status;

void output_redirect(char com[])
{

    char *command[100000], to[10000], *from[10000];
    char *chk = strtok(com, ">");
    int fds[10];
    ll k = 0;

    while (chk != NULL)
    {
        command[k++] = chk;
        chk = strtok(NULL, "> ");
    }

    k = 0;
    from[0] = strtok(command[0], " \t\n\r");
    while (from[k] != NULL)
    {
        k++;
        from[k] = strtok(NULL, " \t\n\r");
    }
    strcpy(to, command[1]);

    int oldout = dup(STDOUT_FILENO);
    int pid = fork();

    fds[0] = open(to, O_WRONLY | O_CREAT, 0755);
    dup2(fds[0], 1);

    if (pid == 0)
    {
        int z = execvp(from[0], from);
        if (z < 0)
        {
            perror("myshell:Error\n");
            dup2(oldout, 1);
            close(fds[0]);
        }
        exit(0);
    }
    else
    {
        while (wait(&status) != pid)
            ;

        dup2(oldout, 1);
        close(fds[0]);
    }
}

void input_redirect(char com[])
{
    // printf("CAME INTO INPUT REDIRECTION\n");
    char *command[100000], to[10000], *from[10000];
    char *chk = strtok(com, "<");
    int fds[10];
    ll k = 0;

    while (chk != NULL)
    {
        command[k++] = chk;
        chk = strtok(NULL, "< ");
    }

    k = 0;
    from[0] = strtok(command[0], " \t\n\r");
    while (from[k] != NULL)
    {
        k++;
        from[k] = strtok(NULL, " \t\n\r");
    }
    strcpy(to, command[1]);
    int oldin = dup(STDIN_FILENO);
    int pid = fork();

    fds[0] = open(to, O_RDONLY);
    // printf("fd val = %d\n", fds[0]);
    if (fds[0] < 0)
        perror("File doesn't exist\n");
    if (pid == 0)
    {
        if (fds[0] < 0)
            ;
        else
        {
            dup2(fds[0], 0);
            int z = execvp(from[0], from);
            if (z < 0)
                perror("myshell:Error\n");
            dup2(oldin, 0);
        }
        exit(0);
    }
    else
        while (wait(&status) != pid)
            ;
}

void redirection(char *token[], ll k, char list_com[], int redflag)
{
    for (ll i = 0; i < k; i++)
    {
        if (strcmp(token[i], ">") == 0)
            output_redirect(list_com);
        else if (strcmp(token[i], "<") == 0)
            input_redirect(list_com);

        // else if (strcmp(token[i], ">>") == 0)
        //     append_redirect()
    }
}