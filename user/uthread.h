#define MAX_UTHREADS 16

int uthread_add(void (*f)(void), uint8 *stack, uint64 size);
void uthread_start(void);
void uthread_yield(void);
void uthread_exit(void);
int uthread_gettid(void);
