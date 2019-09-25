#include "headers.h"

void fg(char *token[])
{
    ll num = atoi(token[1]);
    ll flag = 0;
    for (ll i = 1; i <= job_count; i++)
    {
        if (i == num)
        {
            flag = 1;
            kill(job_arr[num].pid, SIGCONT);
            del_process(job_arr[num].pid);
            waitpid(-1, NULL, WUNTRACED);
        }
    }
    if (flag == 0)
        printf("Error: No such process found\n");
}