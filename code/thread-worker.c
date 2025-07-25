// File:	thread-worker.c

// List all group member's name: Eliana Stevens (jes503)
/*
 */
// username of iLab:
// iLab Server:


#include "thread-worker.h"
#include "thread_worker_types.h"

#define STACK_SIZE 16 * 1024
#define QUANTUM 10 * 1000


/* run queue implementation */

//run queue node
typedef struct RunQueueNode {
    TCB *thread;
    struct RunQueueNode *next;
} RunQueueNode;

// Define the structure for the run queue
typedef struct RunQueue {
    RunQueueNode *front;
    RunQueueNode *rear;
} RunQueue;

RunQueue* init_run_queue() {
    RunQueue *queue = (RunQueue*)malloc(sizeof(RunQueue));
    if (queue == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Function to add a thread to the run queue
void enqueue(RunQueue *queue, TCB *thread) {
    RunQueueNode *new_node = (RunQueueNode*)malloc(sizeof(RunQueueNode));
    if (new_node == NULL) {
        // Handle memory allocation failure
        return;
    }
    new_node->thread = thread;
    new_node->next = NULL;
    if (queue->rear == NULL) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

// Function to remove and return the front thread from the run queue
struct TCB* dequeue(RunQueue *queue) {
    if (queue->front == NULL) {
        // Queue is empty
        return NULL;
    }
    RunQueueNode *temp = queue->front;
    struct TCB *thread = temp->thread;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return thread;
}

// Function to check if the run queue is empty
int is_empty(RunQueue *queue) {
    return (queue->front == NULL);
}

// INITIALIZE ALL YOUR OTHER VARIABLES HERE
int init_scheduler_done = 0;
RunQueue *my_queue;
*my_queue = init_run_queue();


/* create a new thread */
int worker_create(worker_t *thread, pthread_attr_t *attr,
                  void *(*function)(void *), void *arg)
{
    // - create Thread Control Block (TCB)
    struct TCB *new_tcb = (TCB *)malloc(sizeof(TCB));
    if (new_tcb == NULL) {
        return -1; // Failed to allocate memory for TCB
    }

    new_tcb->tid++;

    // - create and initialize the context of this worker thread

    getcontext(&(new_tcb->context));
    new_tcb->context.uc_link = NULL;
    new_tcb->context.uc_stack.ss_sp = new_tcb->stack;
    new_tcb->context.uc_stack.ss_size = STACK_SIZE; //context creation

    makecontext(&(new_tcb->context), (void (*)(void))function, 1, arg); //context initialization

    // - allocate space of stack for this thread to run

    //*thread = new_tcb; //space in TCB

    // after everything is set, push this thread into run queue and make it ready for the execution.
    new_tcb->status = READY;
    enqueue(my_queue, new_tcb);
    return 0;
}

/* give CPU possession to other user-level worker threads voluntarily */
int worker_yield()
{
    //set current tcb to thread at front of the queue
    struct TCB *current_tcb = my_queue.front->thread;

    // - change worker thread's state from Running to Ready
    current_tcb->status = READY;

    // - save context of this thread to its thread control block
    ucontext_t current_context = current_tcb->context;

    // - switch from thread context to scheduler context
    swapcontext(&current_context, &scheduler_context);
    return 0;

};

/* terminate a thread */
void worker_exit(void *value_ptr)
{
    // - if value_ptr is provided, save return value
    // - de-allocate any dynamic memory created when starting this thread (could be done here or elsewhere)

    if (*value_ptr != NULL){
        free(value_ptr);
    } //or something like that
}

/* Wait for thread termination */
int worker_join(worker_t thread, void **value_ptr)
{

    // - wait for a specific thread to terminate
    // - if value_ptr is provided, retrieve return value from joining thread
    // - de-allocate any dynamic memory created by the joining thread
    return 0;

};

/* initialize the mutex lock */
int worker_mutex_init(worker_mutex_t *mutex,
                      const pthread_mutexattr_t *mutexattr)
{
    //- initialize data structures for this mutex
    return 0;

};

/* aquire the mutex lock */
int worker_mutex_lock(worker_mutex_t *mutex)
{

    // - use the built-in test-and-set atomic function to test the mutex
    // - if the mutex is acquired successfully, enter the critical section
    // - if acquiring mutex fails, push current thread into block list and
    // context switch to the scheduler thread
    return 0;

};

/* release the mutex lock */
int worker_mutex_unlock(worker_mutex_t *mutex)
{
    // - release mutex and make it available again.
    // - put one or more threads in block list to run queue
    // so that they could compete for mutex later.

    return 0;
};

/* destroy the mutex */
int worker_mutex_destroy(worker_mutex_t *mutex)
{
    // - make sure mutex is not being used
    // - de-allocate dynamic memory created in worker_mutex_init

    return 0;
};

/* scheduler */
static void schedule()
{
// - every time a timer interrupt occurs, your worker thread library
// should be contexted switched from a thread context to this
// schedule() function

// - invoke scheduling algorithms according to the policy (RR or MLFQ)

// - schedule policy
#ifndef MLFQ
    // Choose RR
    
#else
    // Choose MLFQ
    
#endif
}

static void sched_rr()
{
    // - your own implementation of RR
    // (feel free to modify arguments and return types)
    printf("make the scheduler dumbass");
    return -1;

}

/* Preemptive MLFQ scheduling algorithm */
static void sched_mlfq()
{
    printf("in CS416, this is not required for me");
    return -1;

}

// Feel free to add any other functions you need.
// You can also create separate files for helper functions, structures, etc.
// But make sure that the Makefile is updated to account for the same.
