#include "headers.h"


// ********************************************* PWD *************************************************************//

void pwd()
{
  // printf("Into the pwd function\n");
  char buf[1000000];
  getcwd(buf, sizeof(buf));
  printf("%s\n", buf);
}