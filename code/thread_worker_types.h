#ifndef TW_TYPES_H
#define TW_TYPES_H

#include <ucontext.h>

#define STACK_SIZE 16 * 1024

typedef unsigned int worker_t;

typedef enum {
    READY,
    SCHEDULED,
    BLOCKED,
    TERMINATED,
    EXECUTE
} ThreadStatus;

typedef struct TCB
{
    /* add important states in a thread control block */
    // thread Id
    int32_t tid;
    // thread status
    ThreadStatus status;
    // thread context
    ucontext_t context;
    // thread stack
    char stack[STACK_SIZE];
    // thread priority
    int priority;
    // And more ...

    // YOUR CODE HERE

} TCB;

#endif
