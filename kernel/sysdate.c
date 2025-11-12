#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

#define TIME_LOW  0x00
#define TIME_HIGH 0x04

#define Reg(reg) ((volatile uint32 *)(RTC0 + reg))
#define ReadReg(reg) (*(Reg(reg)))

struct spinlock rtclock;

void
rtcinit(void)
{
  initlock(&rtclock, "rtc");
}

uint64
sys_gettimeofday(void)
{
  acquire(&rtclock);
  uint64 time_l = ReadReg(TIME_LOW);
  uint64 time_h = ReadReg(TIME_HIGH);
  release(&rtclock);
  uint64 nsec = (time_h << 32) | time_l;
  return nsec / 1000000000L;
}
