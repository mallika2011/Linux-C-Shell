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
            del_process(job_arr[num].pid);  // DELETING THE PROCESS FROM THE BACKGROUND PROC ARRAY
            waitpid(-1, NULL, WUNTRACED);   // WAITING FOR THAT PROCESS TO FINISH EXECUTION
        }
    }
    if (flag == 0)
        printf("Error: No such process found\n");
}