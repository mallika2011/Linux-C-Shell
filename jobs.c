#include "headers.h"

void alljobs()
{
    // printf("job count = %lld   %s   %lld\n",job_count, job_arr[1].name, job_arr[1].pid);
    for(ll i=1; i<=job_count; i++)
    {
        // if((job_arr[i].name,"firefox"==0))
        // {
        //     printf("[%lld] %s %s [%lld]\n",i,"stopped", "firefox",job_arr[i].pid);
        //     continue;
        // }
        ll pid=job_arr[i].pid;
        char name[10000],file[10000],status,s[100000];
        strcpy(name,job_arr[i].name);
        
        sprintf(file, "/proc/%lld/stat",pid);

        FILE *fd;
        fd=fopen(file,"r");
        if(fd<0)
            perror("Error: no such process exists\n");
        else
        {
            fscanf(fd, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &status);
            fclose(fd);
        }

        if(status=='T')
            strcpy(s,"Stopped");
        else 
            strcpy(s,"Running");

        // [1] Running emacs assign1.txt [221]
        printf("[%lld] %s %s [%lld]\n",i, s, name,pid);


    }
}