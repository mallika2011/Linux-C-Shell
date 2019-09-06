#include "headers.h"

void lsa(char dir[])
{
    char tempdir[100000];

    if (dir[0] == '~')
    {
        strcpy(tempdir, pseudo_home);
        strcat(tempdir, &dir[1]);
        strcpy(dir, tempdir);
    }
    DIR *d;
    struct dirent **read;
    ll x = 0, no = scandir(dir, &read, NULL, alphasort);
    if (no < 0)
        perror("Error: no such file or directory exists\n");
    else
        while (x < no)
        {
            printf("%s\n", read[x++]->d_name);
        }
}

void lsl(char dir[], int flag)
{
    char tempdir[100000];

    if (dir[0] == '~')
    {
        strcpy(tempdir, pseudo_home);
        strcat(tempdir, &dir[1]);
        strcpy(dir, tempdir);
    }

    DIR *d;
    struct dirent **read;
    ll x = 0, no = scandir(dir, &read, NULL, alphasort);

    if (no < 0)
        perror("Error: No such file or directory\n");
    else
        while (x < no)
        {
            char path[10000];
            struct stat s;
            strcpy(path, read[x++]->d_name);
            // printf("%s\n",path);

            if (path[0] == '.' && flag == 0)
                continue;
            else
            {
                char per[20] = "", own[10], ug[10], date[30], time[6], path2[10000];
                ll hardlinks, size;
                strcpy(path2,"");
                strcat(path2, dir);
                strcat(path2, "/");
                strcat(path2, path);

                stat(path2, &s);
                // printf("path2 == %s\n",path2);

                hardlinks = s.st_nlink;

                struct passwd *pd;
                pd = getpwuid(s.st_uid);
                struct group *gr;
                gr = getgrgid(s.st_gid);

                size = s.st_size;

                if (S_ISDIR(s.st_mode) ? strcat(per, "d") : strcat(per, "-"))
                    ;
                if ((s.st_mode & S_IRUSR) ? strcat(per, "r") : strcat(per, "-"))
                    ;
                if ((s.st_mode & S_IWUSR) ? strcat(per, "w") : strcat(per, "-"))
                    ;
                if ((s.st_mode & S_IXUSR) ? strcat(per, "x") : strcat(per, "-"))
                    ;
                if ((s.st_mode & S_IRGRP) ? strcat(per, "r") : strcat(per, "-"))
                    ;
                if ((s.st_mode & S_IWGRP) ? strcat(per, "w") : strcat(per, "-"))
                    ;
                if ((s.st_mode & S_IXGRP) ? strcat(per, "x") : strcat(per, "-"))
                    ;
                if ((s.st_mode & S_IROTH) ? strcat(per, "r") : strcat(per, "-"))
                    ;
                if ((s.st_mode & S_IWOTH) ? strcat(per, "w") : strcat(per, "-"))
                    ;
                if ((s.st_mode & S_IXOTH) ? strcat(per, "x") : strcat(per, "-"))
                    ;

                strftime(date, 24, "%Y-%m-%d    %H:%M", localtime(&(s.st_ctime)));

                printf("%-12s%-6lld%-8s%-8s%-8lld%-24s%-20s\n", per, hardlinks, pd->pw_name, gr->gr_name, size, date, path);
            }
        }
    return;
}

void onlyls(char dir[])
{
    char tempdir[100000];

    if (dir[0] == '~')
    {
        strcpy(tempdir, pseudo_home);
        strcat(tempdir, &dir[1]);
        strcpy(dir, tempdir);
    }
    DIR *d;
    struct dirent **read;
    ll x = 0, count = scandir(dir, &read, NULL, alphasort);
    if (count < 0)
        perror("Error: no such file or directory exists\n");
    else
        while (x < count)
        {
            if (read[x]->d_name[0] == '.')
            {
                // printf("came in\n");
                x++;
                continue;
            }
            else
            {
                printf("%s\n", read[x]->d_name);
                x++;
            }
        }
}
void ls(char dir[], ll k, char *token[])
{
    if (k == 1)
        onlyls(dir);

    else if (k == 2 && strcmp(token[1], "-a") == 0)
        lsa(dir);
    else if (k == 2 && strcmp(token[1], "-l") == 0)
        lsl(dir, 0);
    else if (k == 2 && ((strcmp(token[1], "-la") == 0) || strcmp(token[1], "-al") == 0))
        lsl(dir, 1);
    else if (k == 2)
        onlyls(token[1]);
    else if (k == 3 && (strcmp(token[1], "-a") == 0 && strcmp(token[2], "-l") == 0) || (strcmp(token[2], "-a") == 0 && strcmp(token[1], "-l") == 0))
        lsl(dir, 1);
    else if (k == 3 && ((strcmp(token[1], "-l") == 0) && (strcmp(token[2], "-l") != 0) && (strcmp(token[2], "-a") != 0)) || ((strcmp(token[2], "-l") == 0) && (strcmp(token[1], "-l") != 0) && (strcmp(token[1], "-a") != 0)))
    {
        if (strcmp(token[1], "-l") == 0)
            lsl(token[2], 0);
        else
            lsl(token[1], 0);
    }

    else if (k == 3 && ((strcmp(token[1], "-a") == 0) && (strcmp(token[2], "-l") != 0) && (strcmp(token[2], "-a") != 0)) || ((strcmp(token[2], "-a") == 0) && (strcmp(token[1], "-l") != 0) && (strcmp(token[1], "-a") != 0)))
    {
        if (strcmp(token[1], "-a") == 0)
            lsa(token[2]);
        else
            lsa(token[1]);
    }
    return;
}