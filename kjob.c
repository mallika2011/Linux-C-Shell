#include "headers.h"

void kjob(char *token[], ll k)
{
    ll number, signo;

    number=atoi(token[1]);
    signo=atoi(token[2]);

    ll flag = 0;
    if(k!=3)
        printf("Error: Incorrect number of arguments\n");
    else
    {
        if(signo==9)
            kjobkill=1;
        if (number <= job_count && number > 0)
            kill(job_arr[number].pid, signo);
        else
            printf("Error : No such process found\n");
    }
}