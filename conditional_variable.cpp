#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

condition_variable cond;
mutex mtx;
int done = 1;

void task(const string& name) {
    unique_lock<mutex> lock(mtx);
    if (done == 1) {
        done = 2;
        cout << "Waiting on conditional variable cond: " << name << endl;
        cond.wait(lock);
        cout << "Condition met: " << name << endl;
    } else {
        for (int i = 0; i < 5; ++i) {
            cout << "." << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
        cout << "Signalling condition variable cond: " << name << endl;
        cond.notify_all();
        cout << "Notification done: " << name << endl;
    }
}

int main() {
    thread t1(task, "t1");
    thread t2(task, "t2");

    t1.join();
    t2.join();

    return 0;
}
