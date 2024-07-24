#include <iostream>
#include <thread>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <mutex>

using namespace std;

queue<int> buffer;
const int MAX_BUFFER_SIZE = 10;
condition_variable cv_producer;
condition_variable cv_consumer;
mutex mtx;

void producer() {
    int value = 0;
    while(true) {
        unique_lock<mutex> lock(mtx);

        cv_producer.wait(lock, []{return buffer.size() < MAX_BUFFER_SIZE;});

        buffer.push(value);

        cout<<"Produced: "<<value<<endl;

        value++;

        cv_consumer.notify_one();

        lock.unlock();

        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void consumer() {
    while(true) {
        unique_lock<mutex> lock(mtx);

        cv_consumer.wait(lock, []{return !buffer.empty();});

        cout<<"Consumed: "<<buffer.front()<<endl;

        buffer.pop();

        cv_producer.notify_one();

        lock.unlock();

        this_thread::sleep_for(chrono::milliseconds(500));
    }

}

int main() {
    thread producerThread(producer);
    thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}