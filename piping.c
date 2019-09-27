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

//***************************************************************************************************************

int redirection_check(char ogcom[])
{
    char *token[100000];
    token[0] = strtok(ogcom, " \t\r\n");
    ll k = 0, r;

    while (token[k] != NULL) //Separating tokens within the command
    {
        k++;
        token[k] = strtok(NULL, " \t\r\n");
    }
    for (ll j = 0; j < k; j++)
    {
        for (ll i = 0; token[j][i]; i++)
            if ((token[j][i] == '>') || token[j][i] == '<' || (token[j][i] == '>' && token[j][i + 1] == '>') && r == 0)
            {
                r = 1;
                if (token[j][i] == '>' && token[j][i + 1] == '>')
                    i++;
            }
            else if ((token[j][i] == '>') || token[j][i] == '<' || (token[j][i] == '>' && token[j][i + 1] == '>') && r == 1)
            {
                r = 2;
                if (token[j][i] == '>' && token[j][i + 1] == '>')
                    i++;
            }
    }
    return r;
}

//**********************************************************************************************************
void piping(char *commands[], ll k)
{
    pipingflag = 1;
    pid_t pid;
    int mypipe[2], mypipe2[2], inp = 0, outp = 0;
    char *part[10000], buffer[100000], ogcom[10000], temp[10000];
    for (ll i = 0; i < k; i++)
    {
        char *part[10000], *part2[10000];
        strcpy(ogcom, commands[i]);
        int oldout, oldin, ofd, ifd, r = 0;

        part[0] = strtok(ogcom, " \t\n\r"); //separating the commands
        ll ii = 0;
        while (part[ii] != NULL)
        {
            ii++;
            part[ii] = strtok(NULL, " \t\r\n");
        }

        // printf("*%lld. -%s-\n", i, commands[i]);
        // printf("tokens = \n");
        // for (ll j = 0; j < ii; j++)
        // printf("%lld. -%s-\n", j, part[j]);

        if (i % 2 != 0)
        {
            int z = pipe(mypipe2);
            if (z < 0)
                perror("Error: pipe could not be created\n");
        }
        else
        {
            int z = pipe(mypipe);
            if (z < 0)
                perror("Error: pipe could not be created\n");
        }

        pid_t pid = fork();
        if (pid == 0)
        {
            if (i == 0)
            {
                dup2(mypipe[1], 1); // output to pipe
                close(mypipe[0]);   //closing input end of pipe
                strcpy(temp, commands[i]);
            }
            else if (i == k - 1)
            {
                if (i % 2 == 1)
                {
                    // printf("came into odd end\n");
                    dup2(mypipe[0], 0); //Input from pipe
                }
                else
                {
                    // printf("came into even end\n");
                    dup2(mypipe2[0], 0); //input from transit
                }

            }

            else if (i % 2 == 0)
            {
                // printf("came into even middle\n");
                dup2(mypipe2[0], 0); //input from transit
                close(mypipe[0]);    // close input end of pipe
                dup2(mypipe[1], 1);  // output to pipe
            }

            else if (i % 2 == 1)
            {
                // printf("came into odd middle\n");
                dup2(mypipe[0], 0);  //input from pipe
                close(mypipe[1]);    // close output end of pipe
                dup2(mypipe2[1], 1); // output to transit
            }

            // printf("VALUEEE OFFF RR = %d\n", r);

            strcpy(temp, commands[i]);
            r = redirection_check(temp);
            if (r == 1 || r == 2)
                redirection(part, ii, commands[i], r);

            // printf("now from exec\n");
            else
            {
                int z = execvp(part[0], part); // exec
                if (z < 0)
                    perror("Error: command not found\n");
                    
                if(r==0)
                    exit(0);
            }
            exit(0);
        }
        else
        {
            wait(NULL);

            if (i == 0)
            {
                close(mypipe[1]);
                if (inp == 1)
                {
                    dup2(oldin, 0);
                    close(ifd);
                }
            }
            else if (i == k - 1)
            {
                if (i % 2 == 0)
                    close(mypipe2[0]);
                else
                    close(mypipe[0]);

                if (outp == 1)
                {
                    dup2(oldout, 1);
                    close(ofd);
                }
            }
            else if (i % 2 == 0)
            {
                close(mypipe2[0]);
                close(mypipe[1]);
            }
            else if (i % 2 == 1)
            {
                close(mypipe[0]);
                close(mypipe2[1]);
            }
        }
    }
}