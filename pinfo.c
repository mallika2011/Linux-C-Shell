#include "headers.h"

void pinfo(ll k, char *token[])
{

    ll memory;
    int f, f2;
    char buf[1000000], file[10000], c, status, temp[100000];
    pid_t pid;

    if (k == 1)
        pid = getpid(); //GETTING PID
    else
        pid = atoi(token[1]);
    sprintf(file, "/proc/%d/stat", pid); //For status, memory

    f = open(file, O_RDONLY);
    f2 = open(file, O_RDONLY);
    if (f < 0)
        perror("Error: no such process exists\n");
    else
    {
        FILE *fd;
        fd = fopen(file, "r");
        fscanf(fd, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lld %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &status, &memory);
        fclose(fd);
        printf("PID -- %d\n", pid);
        printf("Process Status -- %c\n", status);
        printf("Memory -- %lld\n", memory);

        sprintf(file, "/proc/%d/exe", pid); // For executable path
        int x = readlink(file, buf, sizeof(buf));
        buf[x] = '\0';

        // getcwd(cwd,sizeof(cwd));
        x=0;
        ll ii;
        char buf2[100000];
        if (strcmp(buf, pseudo_home) == 0)
            strcpy(buf, "~");
        else
        {

            for (ii = 0; pseudo_home[ii]; ii++)
            {
                if (pseudo_home[ii] != buf[ii])
                {
                    // printf("char home %c\nchar cwd %c\n",pseudo_home[ii],cwd[ii]);
                    x = ii;
                    break;
                }
            }
            // printf("Not equal at %d\n",x);
            if (x == 0)
            {
                buf2[0] = '~';
                ll p, j;
                for (p = 1, j = ii; buf[j]; p++, j++)
                {
                    // printf("%c",cwd[j]);
                    buf2[p] = buf[j];
                }
                buf2[p] = '\0';
            }

            else
                strcpy(buf2, buf);
        }

        printf("Executable Path---  %s\n", buf2);
    }
}
