#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(2, "usage: %s sec\n", argv[0]);
    exit(1);
  }
  setalarm(gettimeofday() + atoi(argv[1]));
  exit(0);
}
