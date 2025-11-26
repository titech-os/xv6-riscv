#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 2){
    fprintf(2, "Usage: %s name\n", argv[0]);
    exit(1);
  }
  if(mkfifo(argv[1]) < 0){
    fprintf(2, "%s: failed to create fifo %s\n", argv[0], argv[1]);
    exit(1);
  }
  exit(0);
}
