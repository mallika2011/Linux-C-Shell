#include "headers.h"

void alljobs()
{
    for(ll i=1; i<=job_count; i++)
    {
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
            fscanf(fd, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &status);
            fclose(fd);
        }
        
        if(status=='T')
            strcpy(s,"Stopped");
        else 
            strcpy(s,"Running");

        printf("[%lld] %s %s [%lld]\n",i, s, name,pid);


    }
}