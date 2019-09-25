#include "headers.h"

int pipecheck(char com[])
{
    ll flag = 0;
    for (ll i = 0; com[i]; i++)
    {
        if (com[i] == '|')
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

void redirection_check(char ogcom[])
{
    char *token[100000];
    token[0] = strtok(ogcom, " \t\r\n");
    ll k = 0;

    while (token[k] != NULL) //Separating tokens within the command
    {
        k++;
        token[k] = strtok(NULL, " \t\r\n");
    }
    for (ll j = 0; j < k; j++)
    {
        // printf("TOKEN[i]= %s\n",token[i]);

        for (ll i = 0; token[j][i]; i++)
            if ((token[j][i] == '>') || token[j][i] == '<' || (token[j][i] == '>' && token[j][i + 1] == '>') && redflag == 0)
            {
                redflag = 1;
                if (token[j][i] == '>' && token[j][i + 1] == '>')
                    i++;
            }
            else if ((token[j][i] == '>') || token[j][i] == '<' || (token[j][i] == '>' && token[j][i + 1] == '>') && redflag == 1)
            {
                redflag = 2;
                if (token[j][i] == '>' && token[j][i + 1] == '>')
                    i++;
            }
    }
}

void piping(char *commands[], ll k)
{
    pipingflag = 1;
    pid_t pid;
    int mypipe[2];
    transitfd = open("transit.txt", O_RDWR | O_CREAT, 0755);
    char *part[10000], buffer[100000], ogcom[10000];

    for (ll i = 0; i < k - 1; i++)
    {
        char *part[10000], *part2[10000];
        strcpy(ogcom, commands[i]);
        part[0] = strtok(commands[i], " \t\n\r"); //separating the commands
        ll ii = 0;
        while (part[ii] != NULL)
        {
            ii++;
            part[ii] = strtok(NULL, " \t\r\n");
        }

        // printf("*%lld. -%s-\n", i, ogcom);
        // printf("tokens = \n");
        // for (ll j = 0; j < ii; j++)
        //     printf("%lld. -%s-\n", j, part[j]);

        
        strcpy(ogcom, commands[i+1]);
        part2[0] = strtok(commands[i + 1], " \t\n\r"); //separating the commands
        ii = 0;
        while (part2[ii] != NULL)
        {
            ii++;
            part2[ii] = strtok(NULL, " \t\r\n");
        }

        // printf("*%lld. -%s-\n", i+1, ogcom);
        // printf("tokens = \n");
        // for (ll j = 0; j < ii; j++)
        //     printf("%lld. -%s-\n", j, part2[j]);

        int z = pipe(mypipe);
        if (z == -1)
        {
            perror("Error: pipe could not be created\n");
            exit(1);
        }
        pid = fork();
        // printf("succ till here\n");
        if (pid == 0)
        {
            int oldout = dup(STDOUT_FILENO);
            int oldin = dup(STDIN_FILENO);

            if (i != 0)
            {
                dup2(transitfd, 0);    //input from transit
                dup2(mypipe[1], 1);    // output to pipe
                int z = execvp(part[0], part); // exec
                if(z<0)
                    perror("Error: command not found\n");
                dup2(oldin, 0);        //revert input
                dup2(oldout, 1);       //revert output
                close(transitfd);      //close file
            }
            else
            {
                dup2(mypipe[1], 1);    // output to pipe
                int z = execvp(part[0], part); // exec
                if(z<0)
                    perror("Error: command not found\n");
                dup2(oldout, 1);       //revert output
            }
        }
        else
        {

            int oldout = dup(STDOUT_FILENO);
            int oldin = dup(STDIN_FILENO);

            if (i != k - 2)
            {
                dup2(transitfd, 1);      //Output to transitfd
                dup2(mypipe[0], 0);      //Input from pipe
                int z = execvp(part2[0], part2); //exec
                if(z<0)
                    perror("Error: command not found\n");
                dup2(oldin, 0);          //revert input
                dup2(oldout, 1);         //revert output
                close(transitfd);        //close file
            }
            else
            {
                // printf("last else\n");
                // char buf[1000];
                // read(mypipe[0],buf,1000);
                // printf("%s\n",buf);
                ///*
                dup2(mypipe[0], 0);      //Input from pipe
                int z = execvp(part2[0], part2); //exec
                if(z<0)
                    perror("Error: command not found\n");
                dup2(oldin, 0);          //revert input*/
            }
        }
        // printf("One process donn\n");
    }

    printf("finished\n");
}