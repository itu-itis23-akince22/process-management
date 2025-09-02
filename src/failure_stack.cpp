#include "failure_stack.h"

void initialize_failed_stack(FAILURE_STACK *fs){
    fs->top = -1;
}

bool isFull(FAILURE_STACK *fs){
    return fs->top == MAX_FAILED - 1;
}

bool isEmpty(FAILURE_STACK *fs){
    return fs->top == -1;
}

void push(FAILURE_STACK *fs, PROCESS_QUEUE data){
    if (!isFull(fs)) {
        fs->stack[++fs->top] = data;
    }
    
}

PROCESS_QUEUE pop(FAILURE_STACK *fs){
    if (!isEmpty(fs)) {
        return fs->stack[fs->top--];
    }
    PROCESS_QUEUE empty = {0};
    return empty;
}
