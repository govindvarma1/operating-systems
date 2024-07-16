#include <iostream>
#include <thread>
#include <vector>
#include <semaphore.h>
#include <unistd.h> 
using namespace std;

sem_t sem;

void task(const std::string& name) {
    sem_wait(&sem);
    
    for (int i = 0; i < 5; ++i) {
        std::cout << name << " working\n";
        sleep(1);
    }
    
    sem_post(&sem);
}

int main() {
    sem_init(&sem, 0, 3);

    thread t1(task, "Thread-1");
    thread t2(task, "Thread-2");
    thread t3(task, "Thread-3");
    thread t4(task, "Thread-4");
    thread t5(task, "Thread-5");

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    sem_destroy(&sem);

    return 0;
}
