#include <iostream>
using namespace std; 
#include "execution_functions.h" // Including this is enough to bring in all required headers transitively

int main() {

    // * Process Queue quick manual tests (commented out)
    // PROCESS_QUEUE pq;
    // initialize_process_queue(&pq);
    // PROCESS data;
    // initialize_process(&data, 120, 1);
    // enqueue(&pq, data);
    // cout << dequeue(&pq).pid << endl;
    // cout << isFull(&pq) << endl;
    // cout << isEmpty(&pq) << endl;


    // * Verify Process Manager creation
    PROCESS_MANAGER pm; 
    read_process_file("initial_processes.txt", &pm); 
    // cout << endl << "Process Manager Deque:" << endl; 
    // for (int i = pm.front + 1; i < pm.rear ; i++) {
    //     PROCESS_QUEUE pq = pm.deque[i];
    //     for (int j = pq.front; j <= pq.rear; j++) {
    //         cout << pq.queue[j].pid << " - ";
    //     }
    //     cout << endl;
    // }

    // * Verify Insertion Queue creation
    INSERTION_QUEUE eq; 
    read_insertion_file("arriving_processes.txt", &eq);
    // cout << endl << "Insertion Queue:" << endl; 
    // for (int i = eq.front; i <= eq.rear; i++) {
    //     PROCESS_QUEUE pq = eq.queue[i];
    //     for (int j = pq.front; j <= pq.rear; j++) {
    //         cout << pq.queue[j].pid << " - ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    // * Verify Failure Stack after execution
    FAILURE_STACK fs;
    execution_loop(&pm, &eq, &fs);
    // cout << endl << "Failure Stack:" << endl; 
    // for (int i = fs.top; i > -1; i--) {
    //     PROCESS_QUEUE pq = fs.stack[i];
    //     for (int j = pq.front; j <= pq.rear; j++) {
    //         cout << pq.queue[j].pid << " - ";
    //     }
    //     cout << endl;
    // }
    

    return 0;
}