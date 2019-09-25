#include "headers.h"
#define hsize 10

char prompt[200000] = "";
char dir[100000];
char *list_com[100000], *temp[100000];
int s, x = 0;
ll ii = 0;
ll l, r, myid, childid;

void promptprint()
{
  x = 0;
  strcpy(dir, "");

  getcwd(cwd, sizeof(cwd));
  strcpy(prompt, "");

  // printf("cwd= %s\n",cwd);
  if (strcmp(cwd, pseudo_home) == 0)
    strcpy(dir, "~");
  else
  {

    for (ii = 0; pseudo_home[ii]; ii++)
    {
      if (pseudo_home[ii] != cwd[ii])
      {
        // printf("char home %c\nchar cwd %c\n",pseudo_home[ii],cwd[ii]);
        x = ii;
        break;
      }
    }
    // printf("Not equal at %d\n",x);
    if (x == 0)
    {
      dir[0] = '~';
      ll p, j;
      for (p = 1, j = ii; cwd[j]; p++, j++)
      {
        // printf("%c",cwd[j]);
        dir[p] = cwd[j];
      }
      dir[p] = '\0';
    }

    else
      strcpy(dir, cwd);
  }

  // printf("dir = %s\n",dir);
  strcat(prompt, "<");
  strcat(prompt, username);
  strcat(prompt, " @ ");
  strcat(prompt, sysname);
  strcat(prompt, ":");

  printf("\033[1;32m");

  printf("\n%s ", prompt);
  printf("\033[0m");
  strcpy(prompt, "");
  strcat(prompt, dir);
  strcat(prompt, ">");

  printf("\033[1;34m");
  // printf("\033[1;36m");

  printf("%s ", prompt);
  printf("\033[0m");
}

void del_process(int id)
{
  // printf("Entered killproc with job count = %lld and proc number=%d\n", job_count, id);
  int flag=0;
  if(id==-1)
    job_count=0;
  else
  for (ll i = 1; i <= job_count; i++)
  {
    // printf("loop\n");
    if (job_arr[i].pid == id)
    {
      // printf("job killed\n");
      flag=1;
      for (ll j = i; j < job_count; j++)
        job_arr[j] = job_arr[j + 1];
      job_count--;
    }
  }
  if(flag==0 && id!=-1)
    printf("Error: no such process found\n");
}

void done()
{
  // printf("ENTERED\n");
  pid_t p;
  int status;
  p = waitpid(-1, &status, WNOHANG);
  for (ll z = 1; z <= job_count; z++)
  {
    if (p < 0)
    {
      perror("\nwaitpid failed\n");
    }
    const int exit = WEXITSTATUS(status);

    // printf("WIFEXITED (STATUS) OF KJOB = %d\nWEXITSTATUS %d  p= %d  job_arr[z] %d\n", WIFEXITED(status), WEXITSTATUS(status),p,job_arr[z].pid);

    if ( ((WIFEXITED(status) && p == job_arr[z].pid) || (kjobkill==1 && p == job_arr[z].pid) ) && overkillflag ==0)
    {
      if(kjobkill ==1)
        kjobkill=0;
      if (exit == 0)
        fprintf(stderr, "\nExitted normally with exit status: %d\n", exit);
      else
        fprintf(stderr, "\nExitted abnormally\n");

      fprintf(stderr, "%s with pid %d: exited\n", job_arr[z].name, p);
      promptprint();
      fflush(stdout);
      del_process(p);
    }

  }
    if(overkillflag==1)
    del_process(-1);
}

// void ctrl_c(int signo)
// {
//     pid_t p = getpid();

//     printf("myid = %d\nchildid = %d\n",p, childid);
//     if (p != myid)
//         return;
//     printf("next step\n");
//     if (childid != -1)
//     {
//       printf("Killing\n");
//       kill(childid, SIGINT);
//     }
//     signal(SIGINT, ctrl_c);
// }

// void ctrl_z(int signo)
// {
//     printf("ININININI\n");
//     pid_t p = getpid();
//     if (p != myid)
//         return;
//     //print();
//     if (childid != -1)
//     {
//         // kill(childid, SIGTTIN);
//         printf("double\n");
//         kill((pid_t)childid, SIGTSTP);
//         // back_count++;
//         // back[back_count].pid = childpid;
//         // back[back_count].is_back = 1;
//         // strcpy(back[back_count].name, fore.name);
//     }
//     signal(SIGTSTP, ctrl_z);
// }

// ****************************************** MAIN LOOP ***********************************************************//


void loop(void)
{
  char *command; //reading the command
  char **args;   //reading the arguments
  ssize_t size = 0;
  int status = 1; //status of the executed command
  char ogcom[10000];



  do
  {
    redflag = 0;
    childid=-1;
    //********************************************* SIGNALS ***********************************************
    signal(SIGCHLD, done);
    
    // signal(SIGINT, ctrl_c);
    // signal(SIGTSTP, ctrl_z);
       

    // *********************************** DISPLAYING THE PROMPT  ***********************************************

    promptprint();

    //*************************************************** COMMANDS ************************************************

    getline(&command, &size, stdin);

    list_com[0] = strtok(command, ";\n"); //separating the commands
    ll i = 0;
    while (list_com[i] != NULL)
    {
      i++;
      list_com[i] = strtok(NULL, ";\n");
    }

    for (ll j = 0; j < i; j++)
    {
      strcpy(ogcom, list_com[j]);

      getcwd(cwd, sizeof(cwd));

      if (pipecheck(list_com[j]))                       //**************************CHECK *************************************//
      {
        temp[0] = strtok(list_com[j], "|");
        ll k = 0;
        while (temp[k] != NULL)
        {
          k++;
          temp[k] = strtok(NULL, "|");
        }
        printf("OG COM : %s\n", ogcom);
        piping(temp,k);
      }

      else
      {
        token[0] = strtok(list_com[j], " \t\r\n");
        ll k = 0;

        while (token[k] != NULL) //Separating tokens within the command
        {
          k++;
          token[k] = strtok(NULL, " \t\r\n");
        }
        // printf("Numner of tokens = %lld\n",k);
        for (ll j = 0; j < k; j++)
        {
          // printf("TOKEN[i]= %s\n",token[i]);

          for(ll i=0; token[j][i]; i++)
          if ((token[j][i]=='>')|| token[j][i]=='<' || (token[j][i]=='>' && token[j][i+1]=='>') && redflag == 0)
              {
                redflag = 1;
                if(token[j][i]=='>' && token[j][i+1]=='>')
                  i++;
              }
          else if ((token[j][i]=='>')|| token[j][i]=='<' || (token[j][i]=='>' && token[j][i+1]=='>') && redflag == 1)
              {
                redflag = 2;
                if(token[j][i]=='>' && token[j][i+1]=='>')
                  i++;
              }
        }

        if (strcmp(token[0], "history") != 0) //WRITING INTO HISTORY
        {
          int q = his_check(token[0]);
        }

        //************************************************************************* IF ELSE OF COMMANDS ******************************************************

        if (strcmp(token[k - 1], "&") == 0) // FOR BACKGROUND PROCESSES
        {
          // printf("entered back\n");
          token[k - 1] = NULL;
          back(token);
        }
        else if (redflag == 1 || redflag == 2) // FOR REDIRECTION
          redirection(token, k, ogcom, redflag);

        else if (token[0][0] == '.') // FOR EXECUTABLES
          fore(token);

        else if (strcmp(token[0], "quit") == 0) //EXIT
        {
          FILE *fd2;
          fd2 = fopen("his.txt", "w");

          for (ll i = 0; i < hsize; i++)
          {
            fprintf(fd2, "%s\n", history[i]);
          }
          fclose(fd2);

          status = 0;
        }
        else if (strcmp(token[0], "pwd") == 0) //COMMAND : PWD
          pwd();
        else if (strcmp(token[0], "cd") == 0) //COMMAND : CD
        {
          if (k > 2)
            perror("myshell: Error: Too many arguments\n");
          if (k > 1)
            cd(token[1]);
          else
            chdir(pseudo_home);
        }
        else if (strcmp(token[0], "echo") == 0) //COMMAND : ECHO
        {
          char st[10000] = "";
          for (ll o = 1; o <= k - 1; o++)
          {
            strcat(st, token[o]);
            strcat(st, " ");
          }
          echo(st);
        }

        else if (strcmp(token[0], "ls") == 0) // COMMAND :LS
          ls(cwd, k, token);
        else if (strcmp(token[0], "pinfo") == 0) //COMMAND :PINFO
          pinfo(k, token);
        else if (strcmp(token[0], "vi") == 0 || strcmp(token[0], "emacs") == 0 || strcmp(token[0], "gedit") == 0) // COMMAND : VI, EMACS, GEDIT FOREGROUND
          fore(token);
        else if (strcmp(token[0], "code") == 0) // TRIAL COMMAND FOR VSCODE
          fore(token);
        else if (strcmp(token[0], "history") == 0) //HISTORY
        {
          history_print();
          his_check(token[0]);
        }
        else if(strcmp(token[0],"jobs")==0)       //JOBS
          alljobs();
        else if(strcmp(token[0],"kjob")==0)       //KJOBS
          kjob(token,k);
        else if(strcmp(token[0],"bg")==0)         //BG
          bg(token);  
        else if(strcmp(token[0],"fg")==0)         //FG
          fg(token);
        else if(strcmp(token[0],"overkill")==0)   //OVERKILL
          overkill();
        else if(strcmp(token[0],"setenv")==0)
          settingenv(token,k);
        else if(strcmp(token[0],"unsetenv")==0)
          unsettingenv(token,k);
        else
          // printf("myshell: command not found: %s\n", token[0]);
          fore(token);
        
      }
    }

  } while (status);
}

int main(int argc, char const *argv[])
{
  myid=getpid();
  // printf("ORIGINAL SHELL ID= %lld\n",myid);

  char old_his[100000];
  ssize_t his_size = 100000;
  int line = 0, cnt = 0, t = 0;

  //**************************************** READING OLD HISTORY FROM FILE ***********************
  FILE *fd;
  fd = fopen("his.txt", "r");

  if (fd < 0)
    perror("Error: history file does not exist.\n");

  while (fgets(old_his, sizeof(old_his), fd))
    line++;
  fseek(fd, 0, SEEK_SET);

  // printf("count= %d\nline= %d\nhsize=%d\n", cnt, line, hsize);

  if (line >= hsize)
  {
    line = line - hsize;
    while (fgets(old_his, sizeof(old_his), fd))
    {
      if (cnt >= line)
      {
        strcpy(history[t++], old_his);
        // printf("history = %s\n", history[0]);
      }
      else
        cnt++;
    }
  }

  else
  {
    while (fgets(old_his, sizeof(old_his), fd))
    {
      strcpy(history[t++], old_his);
    }
  }
  l = 0;
  r = t - 1;
  // printf("History l=%d   r=%d\n", l, r);
  his_load(l, r);
  fclose(fd);

  // *************************************************** PROGRAM START *******************************

  char currentdir[100000], to[100000];
  int pos = 0, sl;
  child_flag = 0;
  curid = -1;
  job_count=0;
  kjobkill=0;
  overkillflag=0;
  pipingflag=0;

  getcwd(currentdir, sizeof(currentdir));
  // printf("%s\n", currentdir);

  while (argv[0][pos])
  {
    if (argv[0][pos] == '/')
      sl = pos;
    pos++;
  }

  for (ll i = 0; i < sl; i++)
    to[i] = argv[0][i];

  chdir(to);
  getcwd(pseudo_home, sizeof(pseudo_home));
  getlogin_r(username, sizeof(username)); //Getting the username of the current active user
  gethostname(sysname, sizeof(sysname));  //Getting the machine name
  chdir(currentdir);

  printf("\033[1;31m");
  printf("\n--------------------------------------------------------------\nYour Pseudo Home Is %s\n--------------------------------------------------------------\n\n", pseudo_home);
  printf("\033[0m");

  loop();
  return 0;
}
