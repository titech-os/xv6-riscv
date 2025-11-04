#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "user/uthread.h"

// stacks for user-level threads
#define STACK_SIZE 4096
uint8 foo_stack[STACK_SIZE] __attribute__((aligned(16)));
uint8 bar_stack[STACK_SIZE] __attribute__((aligned(16)));
uint8 baz_stack[STACK_SIZE] __attribute__((aligned(16)));

int randx = 1;
int rand(void) {
  randx = (214013 * randx + 2531011) & 2147483647;
  return randx;
}

void spin_random_wait(void) {
  int n = (rand() >> 8) % 50 + 50;
  for (int i = 0; i < n; i++) {
    uthread_yield();
  }
}

int locked = 0;
int cs_count = 0;

void fun() {
  printf("thread %d started\n", uthread_gettid());
  for (int i = 0; i < 10; i++) {
    spin_random_wait();  // NC
    uthread_acquire(&locked);
    cs_count++;
    if (cs_count > 1) {
      printf("error: tid=%d, cs_count=%d\n", uthread_gettid(), cs_count);
    }
    spin_random_wait();  // CS
    cs_count--;
    uthread_release(&locked);
  }
  printf("thread %d stopped\n", uthread_gettid());
  uthread_exit();
}

int main() {
  randx = uptime();
  uthread_add(fun, foo_stack, STACK_SIZE);
  uthread_add(fun, bar_stack, STACK_SIZE);
  uthread_add(fun, baz_stack, STACK_SIZE);
  uthread_start();
  exit(0);
}
