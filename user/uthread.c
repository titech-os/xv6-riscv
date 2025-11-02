#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "user/uthread.h"

// Saved registers for kernel context switches. (from kernel/proc.h)
struct context {
  uint64 ra;
  uint64 sp;

  // callee-saved
  uint64 s0;
  uint64 s1;
  uint64 s2;
  uint64 s3;
  uint64 s4;
  uint64 s5;
  uint64 s6;
  uint64 s7;
  uint64 s8;
  uint64 s9;
  uint64 s10;
  uint64 s11;
};

// swtch.S (from kernel/defs.h)
void swtch(struct context*, struct context*);


int uthread_add(void (*f)(void), uint8 *stack, uint64 size) {
  // TODO: Replace this comment with your code.
  return -1; // This line should also be replaced with your code.
}

void uthread_start(void) {
  // TODO: Replace this comment with your code.
}

void uthread_yield(void) {
  // TODO: Replace this comment with your code.
}

void uthread_exit(void) {
  // TODO: Replace this comment with your code.
}

int uthread_gettid(void) {
  // TODO: Replace this comment with your code.
  return -1; // This line should also be replaced with your code.
}
