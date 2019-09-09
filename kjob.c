#include "headers.h"

void kjob(char *token[], ll k)
{
    ll number, signo;

    number=atoi(token[1]);
    signo=atoi(token[2]);

    ll flag = 0;
    if(k!=3)
        printf("Error: Incorrect number of arguments\n");

    else if (signo == 9)
    {
        for (ll i = 1; i <= job_count; i++)
        {
            // printf("loop\n");
            if (i == number)
            {
                flag = 1;
                for (ll j = i; j < job_count; j++)
                    job_arr[j] = job_arr[j + 1];
                job_count--;
            }
        }
        printf("JOB COUNT = %lld\n",job_count);
        if (flag == 0)
            printf("Error : No such process found\n");
        else 
        {
            printf("JOB COUNT = %lld\n",job_count);
            kill(job_arr[number].pid,signo);
            printf("JOB COUNT = %lld\n",job_count);
        }
    }
    else
    {
        if (number <= job_count && number > 0)
            kill(job_arr[number].pid, signo);
        else
            printf("Error : No such process found\n");
    }
}