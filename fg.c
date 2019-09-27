#include "headers.h"

void fg(char *token[])
{
    ll num = atoi(token[1]);
    ll flag = 0;
    for (ll i = 1; i <= job_count; i++)
    {
        if (i == num)
        {
            int status;
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU,SIG_IGN);
            tcsetpgrp(STDIN_FILENO,job_arr[num].pid);
            flag = 1;
            current_fore.pid=job_arr[num].pid;
            strcpy(current_fore.name,job_arr[num].name);
            kill(job_arr[num].pid, SIGCONT);
            del_process(job_arr[num].pid);  // DELETING THE PROCESS FROM THE BACKGROUND PROC ARRAY
            waitpid(-1, NULL, WUNTRACED);   // WAITING FOR THAT PROCESS TO FINISH EXECUTION
            tcsetpgrp(STDIN_FILENO,getpgrp());
            signal(SIGTTIN,SIG_DFL);
            signal(SIGTTOU,SIG_DFL);

        }
    }
    if (flag == 0)
        printf("Error: No such process found\n");
}