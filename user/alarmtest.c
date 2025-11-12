#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
  uint64 t = gettimeofday();
  // printf("t: %ld\n", t);
  t = t + 20;
  // printf("t: %ld\n", t);
  setalarm(t);
  exit(0);
}
