#include "headers.h"

int hr = -1, hl = -1, hsize = 0, n = 10;

void his_load(ll l, ll r)
{
    hl=l;
    hr=r;
}

void del()
{
    if (hl == -1)
        printf("\nError: empty history");

    if (hl == hr)
    {
        hl = -1;
        hr = -1;
    }
    else if (hl == n - 1)
        hl = 0;
    else
        hl++;
}

void wr(char new[])
{
    if ((hl == 0 && hr == n - 1) || (hr == (hl - 1) % (n - 1)))
        del();

    else if (hl == -1)
    {
        hl = hr = 0;
        strcpy(history[hr], new);
    }

    else if (hr == n - 1 && hl != 0)
    {
        hr = 0;
        strcpy(history[hr], new);
    }

    else
    {
        hr++;
        strcpy(history[hr], new);
    }
}

int his_check(char new[])
{
    int f = 0;
    for (ll i = 0; i < n; i++)
    {
        if (strcmp(new, history[i]) == 0)
        {
            f = 1;
            break;
        }
    }
    if (f == 0)
    {
        if ((n + hr - hl + 1) % n != 0)
            wr(new);

        else
        {
            del();
            wr(new);
        }
    }
    // printf("Values\nhl=%d\nhr=%d\n",hl,hr);
    return f;
}

void history_print()
{
    if (hl == hr && hl == -1)
        printf("No History\n");
    else
    {   
        if(hl<=hr)
        for (ll i = hl; i <= hr; i++)
            printf("> %s\n", history[i]);

        else
        {
            for(ll i=hl; i<n; i++)
            printf("> %s\n", history[i]);

            for(ll i=0; i<=hr; i++)
            printf("> %s\n", history[i]);
        }   
    }
}