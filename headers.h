#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <dirent.h>
#include <signal.h>
#include <sys/stat.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#define ll long long int

char cwd[200000], pseudo_home[1024];
char sysname[100000];
char username[1000000];
char history[10][1000];
int pid_arr[100000];
int child_flag;
int curid;
int kjobkill;
int overkillflag;
char *token[100000];

typedef struct jobs{
    char name[10000];
    pid_t pid;
}job;

ll job_count;
struct jobs job_arr[100000];

/*MAIN LOOP */      void loop(void);
/*PWD */            void pwd();
/*CD */             void cd(char path[]);
/*ECHO */           void echo(char string[]);
/*LS */             void ls(char dir[], ll k, char *token[]);
/*PINFO */          void pinfo(ll k, char *token[]);
/*FOREGROUND */     void fore(char *token[]);
/*BACKGROUND */     void back(char *token[]);
/*REDIRECTION*/     void redirection(char *token[], ll k, char list_com[], int redflag);
/*PIPING*/          int pipecheck();
/*PIPING*/          void piping(char *commands[], ll k);
/*JOB PRINT*/       void alljobs();
/*KJOBS*/           void kjob(char *token[],ll k);
/*FG*/              void fg(char *token[]);
/*BG*/              void bg(char *token[]);
/*OVERKILL*/        void overkill();
/*SETENV*/          void settingenv(char *token[],ll k);
/*UNSETTING ENV*/   void unsettingenv(char *token[], ll k) ;
/*del proc*/        void del_process(int id);
void history_print();
int his_check(char new[]);
void his_load(ll l, ll r);
extern int alphasort();