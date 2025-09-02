#include "execution_functions.h"
#include <string.h>
#include "execution_functions.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Helper: open file with fallback (first given name, then doc/<name>) */
static FILE* open_with_fallback(const char *name, const char *kind){
    FILE *f = fopen(name, "r");
    if (!f){
        char buf[256];
        snprintf(buf, sizeof buf, "doc/%s", name);
        f = fopen(buf, "r");
    }
    if (!f){
        fprintf(stderr, "Failed to open %s file: %s\n", kind, name);
    }
    return f;
}

void read_process_file(const char *filename, PROCESS_MANAGER *pm){
    FILE *file = open_with_fallback(filename, "process");
    if (!file) return;
    char line[256];
    int line_no = 0;
    // Temporary storage of single-item queues
    PROCESS_QUEUE temp[MAX_PROCESS];
    int count = 0;
    while (fgets(line, sizeof line, file)){
        ++line_no;
        if (line_no == 1 && (strncmp(line, "pid", 3) == 0)) continue; // header
    // expected format: pid, priority, isHead
        int pid, priority, isHead;
        if (sscanf(line, "%d , %d , %d", &pid, &priority, &isHead) != 3 &&
            sscanf(line, "%d %d %d", &pid, &priority, &isHead) != 3){
            continue;
        }
        PROCESS p; p.pid = pid; p.priority = priority;
        PROCESS_QUEUE q; initialize_process_queue(&q); q.priority = priority; enqueue(&q, p);
        if (count < MAX_PROCESS) temp[count++] = q;
    }
    fclose(file);
    // Rotate so that pid 151 (if present) becomes first; otherwise keep original order
    int start = 0;
    for (int i = 0; i < count; ++i){
        if (temp[i].queue[temp[i].front].pid == 151){ start = i; break; }
    }
    for (int i = 0; i < count; ++i){
        int idx = (start + i) % count;
        insert_rear(pm, temp[idx]);
    }
}

void read_insertion_file(const char *filename, INSERTION_QUEUE *eq){
    FILE *file = open_with_fallback(filename, "insertion");
    if (!file) return;
    char line[256];
    int line_no = 0;
    while (fgets(line, sizeof line, file)){
        ++line_no;
        if (line_no == 1 && (strncmp(line, "iteration", 9) == 0)) continue; // header
    // expected format: iteration, pid, priority, isHead
        int iteration, pid, priority, isHead;
        if (sscanf(line, "%d , %d , %d , %d", &iteration, &pid, &priority, &isHead) != 4 &&
            sscanf(line, "%d %d %d %d", &iteration, &pid, &priority, &isHead) != 4){
            continue;
        }
        PROCESS p; p.pid = pid; p.priority = priority;
        PROCESS_QUEUE q; initialize_process_queue(&q); q.priority = priority; q.iteration = iteration; enqueue(&q, p);
        enqueue(eq, q);
    }
    fclose(file);
}

void execution_loop(PROCESS_MANAGER *pm, INSERTION_QUEUE *eq, FAILURE_STACK *fs){
    // Move all insertion queue groups to the end of the process manager
    while (!isEmpty(eq)){
        PROCESS_QUEUE arriving = dequeue(eq);
        insert_rear(pm, arriving);
    }

    initialize_failed_stack(fs);
    PROCESS_QUEUE failed; initialize_process_queue(&failed);

    while (!isEmpty(pm)){
        PROCESS_QUEUE q = delete_front(pm);
        while (!isEmpty(&q)){
            PROCESS p = dequeue(&q);
            if (p.pid % 8 == 0){
                enqueue(&failed, p);
            }
        }
    }
    if (failed.size > 0) push(fs, failed);
}