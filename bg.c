#include "headers.h"

void bg(char *token[])
{
    ll num=atoi(token[1]);
    ll flag=0;
    for(ll i=1; i<=job_count; i++)
    {
        if(i==num)
        {
            flag=1;
            kill(job_arr[num].pid, SIGTTIN);  
            kill(job_arr[num].pid,SIGCONT);
        }
    }
    if(flag==0)
        printf("Error: No such job found\n");
}