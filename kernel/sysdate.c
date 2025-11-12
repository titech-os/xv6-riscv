#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

#define TIME_LOW  0x00
#define TIME_HIGH 0x04
#define ALARM_LOW 0x08
#define ALARM_HIGH 0x0C
#define IRQ_ENABLED	0x10
#define CLEAR_ALARM	0x14
#define ALARM_STATUS	0x18
#define CLEAR_INTERRUPT	0x1c

#define Reg(reg) ((volatile uint32 *)(RTC0 + reg))
#define ReadReg(reg) (*(Reg(reg)))
#define WriteReg(reg, v) (*(Reg(reg)) = (v))

struct spinlock rtclock;

void
rtcinit(void)
{
  initlock(&rtclock, "rtc");
  WriteReg(IRQ_ENABLED, 0);
  WriteReg(CLEAR_ALARM, 1);
}

void
rtcintr(void)
{
  WriteReg(CLEAR_INTERRUPT, 1);
  WriteReg(IRQ_ENABLED, 0);
  printf("RTC interrupt\n");
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

uint64
sys_setalarm(void)
{
  uint64 time;
  argaddr(0, &time);
  // printf("time: %ld\n", time);
  time *= 1000000000L;
  acquire(&rtclock);
  WriteReg(CLEAR_ALARM, 1);
  WriteReg(ALARM_HIGH, time >> 32);
  WriteReg(ALARM_LOW, time);
  WriteReg(IRQ_ENABLED, 1);
  release(&rtclock);
  return 0;
}
