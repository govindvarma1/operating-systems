#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int cnt = 0; // Shared variable
mutex mux;  // Mutex for synchronizing access to cnt

void add() {
    for(int i = 0; i < 1e7; i++) {
        mux.lock();   // Lock the mutex
        cnt++;        // Critical section
        mux.unlock(); // Unlock the mutex
    }
}

int main() {
    thread t1(add); // Create thread t1
    thread t2(add); // Create thread t2

    t1.join(); // Wait for t1 to finish
    t2.join(); // Wait for t2 to finish

    cout << cnt << endl; // Print the final value of cnt

    return 0;
}
