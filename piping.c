#include "headers.h"

int pipecheck(char com[])
{
    ll flag=0;
    for(ll i=0; com[i]; i++)
    {
        if(com[i]=='|')
        {
            flag=1;
            break;
        }
    }
    return flag;
}

void piping(char *commands[], ll k)
{
    printf("k= %lld\n",k);
    // for(ll i=0; i<k;i++)
    // {
    //     printf("%lld. -%s-\n",i,commands[i]);
    // }

    for(ll i=0; i<k; i++)
    {
        
    }




}