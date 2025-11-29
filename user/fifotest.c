#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  char *av[] = { 0 };
  int cp, cc;
  if ((cp = fork()) < 0) {
    fprintf(2, "fork failed\n");
    exit(1);
  }
  else if (cp == 0) {
    exec("fifotestp", av);
  }
  if ((cc = fork()) <  0) {
    fprintf(2, "fork failed\n");
    exit(1);
  }
  else if (cc == 0) {
    exec("fifotestc", av);
  }
  wait(0);
  wait(0);
  exit(0);
}
