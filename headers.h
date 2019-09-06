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
char *token[100000];

/*MAIN LOOP */  void loop(void);
/*PWD */        void pwd();
/*CD */         void cd(char path[]);
/*ECHO */       void echo(char string[]);
/*LS */         void ls(char dir[], ll k, char *token[]);
/*PINFO */      void pinfo(ll k, char *token[]);
/*FOREGROUND */ void fore(char *token[]);
/*BACKGROUND */ void back(char *token[]);
/*REDIRECTION*/ void redirection(char *token[], ll k, char list_com[], int redflag);
void history_print();
int his_check(char new[]);
void his_load(ll l, ll r);
extern int alphasort();