#include "kernel/types.h"
#include "user/user.h"

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

struct context foo_context;
struct context bar_context;
struct context baz_context;

#define STACK_DEPTH 512
uint64 bar_stack[STACK_DEPTH];
uint64 baz_stack[STACK_DEPTH];

void foo() {
    uint64 c = 0;
    for (;;) {
        printf("foo : %l\n", c);
        swtch(&foo_context, &bar_context);
        c += 1;
    }
}

void bar() {
    uint64 c = 0;
    for (;;) {
        printf("bar : %l\n", c);
        swtch(&bar_context, &baz_context);
        c += 2;
    }
}

void baz() {
    uint64 c = 0;
    for (;;) {
        printf("baz : %l\n", c);
        swtch(&baz_context, &foo_context);
        c += 3;
    }
}

int main() {
    // setting up initial contexts
    bar_context.ra = (uint64)bar;
    bar_context.sp = (uint64)(bar_stack + STACK_DEPTH);
    baz_context.ra = (uint64)baz;
    baz_context.sp = (uint64)(baz_stack + STACK_DEPTH);
    // start from foo
    foo();
    return 0;
}
