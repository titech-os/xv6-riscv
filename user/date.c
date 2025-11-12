// works until 2100/2/28
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define DY4 (365 + 365 + 366 + 365)

int dy[4] = { 365, 365, 366, 365 };
int dm[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 
               30, 31, 30, 31 };

int
main()
{
  uint64 s = gettimeofday();
  int days = s / 3600 / 24;
  int dy4 = days % DY4;
  int year = 1970 + days / DY4 * 4;
  int month = 0;
  int day = 0;
  for (int i = 0, d = 0; i < 4; d += dy[i], i++) {
    if (dy4 < d + dy[i]) {
      year += i;
      day = dy4 - d;
      if (i == 2) dm[1] = 29;  // leap year
      break;
    }
  }
  for (int i = 0, d = 0; i < 12; d += dm[i], i++) {
    if (day < d + dm[i]) {
      day = day - d + 1;
      month = i + 1;
      break;
    }
  }
  int hour = s / 3600 % 24;
  int minute = s / 60 % 60;
  int second = s % 60;
  printf("%d/%d/%d %d:%d:%d\n", 
         year, month, day, hour, minute, second);

  exit(0);
}
