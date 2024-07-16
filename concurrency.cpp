#include <iostream>
#include <thread>
#include <unistd.h> // For sleep function
using namespace std;

// Task A prints its identifier and a number from 1 to 10 with a delay of 1 second between each print
void taskA() {
    for(int i = 1; i <= 100; i++) {
        sleep(1); // Delay of 1 second
        cout << "Task A: " << i << endl;
    }
}

// Task B prints its identifier and a number from 1 to 10 with a delay of 1 second between each print
void taskB() {
    for(int i = 1; i <= 100; i++) {
        sleep(1); // Delay of 1 second
        cout << "Task B: " << i << endl;
    }
}

int main() {
    // Create and start the threads for taskA and taskB
    thread task1(taskA);
    thread task2(taskB);

    // Wait for both threads to finish
    task1.join();
    task2.join();

    return 0;
}
