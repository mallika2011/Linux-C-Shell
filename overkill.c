#include "headers.h"

void overkill()
{
    for(ll i=1; i<=job_count; i++)
    {
        kill(job_arr[i].pid,9);
    }

    overkillflag=1;
}