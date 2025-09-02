#include "process_manager.h"


void initialize_process_manager(PROCESS_MANAGER *pm){
    pm->front = 0;
    pm->rear  = -1;
    pm->size  = 0;
}

bool isFull(PROCESS_MANAGER *pm){
    return pm->size == MAX_PROCESS;
}

bool isEmpty(PROCESS_MANAGER *pm){
    return pm->size == 0;
}

void insert_front(PROCESS_MANAGER *pm, PROCESS_QUEUE pq){
    if (isFull(pm)) return;
    if (pm->size == 0){
        pm->front = 0;
        pm->rear  = 0;
        pm->deque[0] = pq;
        pm->size = 1;
        return;
    }
    pm->front = (pm->front - 1 + MAX_PROCESS) % MAX_PROCESS;
    pm->deque[pm->front] = pq;
    pm->size++;
}

void insert_rear(PROCESS_MANAGER *pm, PROCESS_QUEUE pq){
    if (isFull(pm)) return;
    if (pm->size == 0){
        pm->front = 0;
        pm->rear  = 0;
        pm->deque[0] = pq;
        pm->size = 1;
        return;
    }
    pm->rear = (pm->rear + 1) % MAX_PROCESS;
    pm->deque[pm->rear] = pq;
    pm->size++;
}

PROCESS_QUEUE delete_front(PROCESS_MANAGER *pm){
    if (isEmpty(pm)) return PROCESS_QUEUE{};
    PROCESS_QUEUE pq = pm->deque[pm->front];
    pm->front = (pm->front + 1) % MAX_PROCESS;
    pm->size--;
    if (pm->size == 0){
        pm->front = 0;
        pm->rear  = -1;
    }
    return pq;
}

PROCESS_QUEUE delete_rear(PROCESS_MANAGER *pm){
    if (isEmpty(pm)) return PROCESS_QUEUE{};
    PROCESS_QUEUE pq = pm->deque[pm->rear];
    pm->rear = (pm->rear - 1 + MAX_PROCESS) % MAX_PROCESS;
    pm->size--;
    if (pm->size == 0){
        pm->front = 0;
        pm->rear  = -1;
    }
    return pq;
}
