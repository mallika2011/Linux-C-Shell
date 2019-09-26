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

// void redirection_check(char ogcom[])
// {
//     char *token[100000];
//     token[0] = strtok(ogcom, " \t\r\n");
//     ll k = 0;

//     while (token[k] != NULL) //Separating tokens within the command
//     {
//         k++;
//         token[k] = strtok(NULL, " \t\r\n");
//     }
//     for (ll j = 0; j < k; j++)
//     {
//         // printf("TOKEN[i]= %s\n",token[i]);

//         for (ll i = 0; token[j][i]; i++)
//             if ((token[j][i] == '>') || token[j][i] == '<' || (token[j][i] == '>' && token[j][i + 1] == '>') && redflag == 0)
//             {
//                 redflag = 1;
//                 if (token[j][i] == '>' && token[j][i + 1] == '>')
//                     i++;
//             }
//             else if ((token[j][i] == '>') || token[j][i] == '<' || (token[j][i] == '>' && token[j][i + 1] == '>') && redflag == 1)
//             {
//                 redflag = 2;
//                 if (token[j][i] == '>' && token[j][i + 1] == '>')
//                     i++;
//             }
//     }
// }

//**********************************************************************************************************
void piping(char *commands[], ll k)
{
    pipingflag = 1;
    pid_t pid;
    int mypipe[2], mypipe2[2];
    char *part[10000], buffer[100000], ogcom[10000];
    for (ll i = 0; i < k; i++)
    {
        char *part[10000], *part2[10000];
        strcpy(ogcom, commands[i]);
        int oldout;
        int oldin;

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
        //     printf("%lld. -%s-\n", j, part[j]);

        if (i % 2 != 0)
        {
            int z = pipe(mypipe2); 
            if(z<0)
                perror("Error: pipe could not be created\n");
        }
        else
        {
            int z = pipe(mypipe); 
            if(z<0)
                perror("Error: pipe could not be created\n");
        }

        pid_t pid = fork();
        if (pid == 0)
        {
            // printf("vlaue of i = %d\n", i);
            // oldout = dup(STDOUT_FILENO);
            // oldin = dup(STDIN_FILENO);
            int transitfd = open("transit.txt", O_RDWR | O_CREAT | O_TRUNC, 0755);
            if (i == 0)
            {
                // printf("came into 0\n");
                dup2(mypipe[1], 1); // output to pipe
                close(mypipe[0]);   //closing input end of pipe
            }
            else if (i == k - 1)
            {
                if (i % 2 == 1)
                {
                    // printf("came into odd end\n");
                    dup2(mypipe[0], 0); //Input from pipe
                    // char buf[1000];
                    // read(mypipe[0], buf, 1000);
                    // printf("*******%s\n", buf);
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
            int z = execvp(part[0], part); // exec
            if (z < 0)
                perror("Error: command not found\n");
            exit(0);
        }
        else
        {
            wait(NULL);

            if (i == 0)
            {
                close(mypipe[1]);
            }
            else if (i == k - 1)
            {
                if (i % 2 == 0)
                    close(mypipe2[0]);
                else
                    close(mypipe[0]);
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
    // printf("finished\n");
}