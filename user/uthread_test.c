#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "user/uthread.h"

// stacks for user-level threads
#define STACK_SIZE 4096
uint8 foo_stack[STACK_SIZE] __attribute__((aligned(16)));
uint8 bar_stack[STACK_SIZE] __attribute__((aligned(16)));
uint8 baz_stack[STACK_SIZE] __attribute__((aligned(16)));

void foo() {
    int c = 0;
    for (int i = 0; i < 7; i++) {
        printf("foo (tid=%d): %d\n", uthread_gettid(), c);
        c += 1;
        uthread_yield();
    }
    uthread_exit();
}

void bar(void) {
    int c = 0;
    for (int i = 0; i < 5; i++) {
        printf("bar (tid=%d): %d\n", uthread_gettid(), c);
        uthread_yield();
        c += 2;
    }
    uthread_exit();
}

void baz_sub(int *cp) {
  printf("baz (tid=%d): %d\n", uthread_gettid(), *cp);
  uthread_yield();
  *cp += 3;
}

void baz(void) {
    int c = 0;
    for (int i = 0; i < 5; i++) {
        baz_sub(&c);
        baz_sub(&c);
    }
    uthread_exit();
}

int main() {
  uthread_add(foo, foo_stack, STACK_SIZE);
  uthread_add(bar, bar_stack, STACK_SIZE);
  uthread_add(baz, baz_stack, STACK_SIZE);
  uthread_start();
  exit(0);
}
