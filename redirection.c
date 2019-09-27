#include "headers.h"

int status;

void choice(int fds[], char *from[], int k, int oldin, int oldout)
{
    // printf("*****CAME INTO CHOICE *****\n");

    if (strcmp(from[k - 1], "&") == 0) // FOR BACKGROUND PROCESSES
    {
        from[k - 1] = NULL;
        back(from);
    }
    else if (from[0][0] == '.') // FOR EXECUTABLES
        fore(from);
    else if (strcmp(from[0], "pwd") == 0) //COMMAND : PWD
        pwd();
    else if (strcmp(from[0], "cd") == 0) //COMMAND : CD
    {
        cd(from,k);
    }

    else if (strcmp(from[0], "echo") == 0) //COMMAND : ECHO
    {
        echo(token, k);
    }
    else if (strcmp(from[0], "ls") == 0) // COMMAND :LS
    {
        ls(cwd, k, from);
    }
    else if (strcmp(from[0], "pinfo") == 0) //COMMAND :PINFO
        pinfo(k, from);
    else if (strcmp(from[0], "vi") == 0 || strcmp(from[0], "emacs") == 0 || strcmp(from[0], "gedit") == 0) // COMMAND : VI, EMACS, GEDIT FOREGROUND
        fore(from);
    else if (strcmp(from[0], "code") == 0) // TRIAL COMMAND FOR VSCODE
        fore(from);
    else if (strcmp(from[0], "history") == 0) //HISTORY
    {
        history_print();
        his_check(from[0]);
    }
    else if (strcmp(from[0], "jobs") == 0)
        alljobs();
    else
    {
        int z = execvp(from[0], from);
        if (z < 0)
        {
            perror("myshell:Error\n");
            dup2(oldout, 1);
            close(fds[0]);
        }
    }
}

void both(char com[], ll app)
{
    char *command[100000], to[10000], *from[10000], *temp1[100000], *temp2[100000], *temp3[100000], input_file[100000], delim[10], output_file[100000];
    strcpy(output_file, "");
    strcpy(input_file, "");
    int fds[10];
    for (ll i = 0; i < 10; i++)
        fds[i] = -1;
    ll k = 0;
    if (app == 1)
        strcpy(delim, ">>");
    else
        strcpy(delim, ">");
    char *chk = strtok(com, delim);
    while (chk != NULL)
    {
        command[k++] = chk;
        chk = strtok(NULL, delim);
    }

    if (k == 2)
    {
        strcpy(to, command[1]); //OUTPUT FILEEEEE
        temp1[0] = strtok(to, " \t\n\r");
        strcpy(output_file, temp1[0]);
    }
    // printf("output file %s\n", output_file);

    k = 0;
    temp2[0] = strtok(command[0], "<");
    while (temp2[k] != NULL)
    {
        k++;
        temp2[k] = strtok(NULL, "<");
    }
    if (k == 2)
    {
        strcpy(input_file, temp2[1]); //INPUT FILEEEE
        temp3[0] = strtok(input_file, " \t\n\r");
        strcpy(input_file, temp3[0]);
    }
    // printf("input file = %s\nk=%d\n", input_file, k);
    k = 0;
    from[0] = strtok(temp2[0], " \t\n\r");
    while (from[k] != NULL)
    {
        k++;
        from[k] = strtok(NULL, " \t\n\r");
    }

    // printf("%s-%s-%s-\n", from[0], input_file, output_file);

    if (strcmp(input_file, "") != 0 && strcmp(output_file, "") == 0) // HAS INPUT REDIRECTION ONLY
    {
        // printf("came into input\n");
        int oldin = dup(STDIN_FILENO);
        int pid = fork();

        fds[0] = open(input_file, O_RDONLY);
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
                choice(fds,from,k,oldin,-1);
                dup2(oldin, 0);
            }
            exit(0);
        }
        else
            while (wait(&status) != pid)
                ;
    }
    else if (strcmp(output_file, "") != 0 && strcmp(input_file, "") == 0) //HAS OUTPUT REDIRECTION ONLY
    {
        // printf("Came into output\n");
        int oldout = dup(STDOUT_FILENO);
        int pid = fork();

        if (app == 0)
            fds[0] = open(output_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        else if (app == 1)
            fds[0] = open(output_file, O_APPEND | O_WRONLY | O_CREAT, 0644);
        dup2(fds[0], 1);

        if (pid == 0)
        {
            // printf("Going to choice\n");
            choice(fds,from,k,-1,oldout);
            // printf("did choice\n");
            // dup2(oldout, 1);
            // close(fds[0]);

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
    else
    {
        // printf("Came into both\n");
        int oldin = dup(STDIN_FILENO);
        int oldout = dup(STDOUT_FILENO);
        int pid = fork();

        fds[0] = open(input_file, O_RDONLY);
        if (app == 0)
            fds[1] = open(output_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        else if (app == 1)
            fds[1] = open(output_file, O_APPEND | O_WRONLY | O_CREAT, 0644);
        dup2(fds[1], 1);
        if (fds[0] < 0)
            perror("File doesn't exist\n");
        if (pid == 0)
        {
            if (fds[0] < 0)
                ;
            else
            {
                dup2(fds[0], 0);
                choice(fds, from, k, oldin, oldout);
                dup2(oldin, 0);
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
}

void redirection(char *token[], ll k, char list_com[], int redflag)
{
    // printf("LIST OF COMMS = %s\n", list_com);
    ll app = 0, inp = 0, out = 0, a = 0;
    for (ll i = 0; i < k; i++)
    {
        if (strcmp(token[i], ">") == 0)
            out += 1;
        else if (strcmp(token[i], "<") == 0)
            inp += 1;
        else if (strcmp(token[i], ">>") == 0)
        {
            app = 1;
            a += 1;
        }
    }
    both(list_com, app);
}