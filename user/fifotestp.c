#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

const int n = 10;

int
main(int argc, char *argv[])
{
  // pause(20);
  int p2c = open("p2c", O_WRONLY);
  int c2p = open("c2p", O_RDONLY);
  if (p2c < 0 || c2p < 0) {
    fprintf(2, "open failed\n");
    exit(1);
  }
  unsigned char k = 0;
  write(p2c, &k, 1);
  for (int i = 0; i < n; i++) {
    read(c2p, &k, 1);
    printf("parent: %d\n", k);
    k = k + 1;
    write(p2c, &k, 1);
  }
  close(p2c);
  close(c2p);
  exit(0);
}
