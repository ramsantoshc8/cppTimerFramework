#include <iostream>
#include <thread>
#include <queue>
#include <chrono>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;
std::queue<int> q;

bool completed = false;

void numGen () {

    using namespace std::literals::chrono_literals;

    for (int i = 1; i <= 10; i++) {

        std::this_thread::sleep_for(100ms);
        std::unique_lock<std::mutex> lock(m);
        q.push(i);
        lock.unlock();

        cv.notify_one();
    }
    completed = true;
}

void numReader () {

    while (completed == false) {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [] { 
            if (!q.empty()) {
                return true;
            } else {
                return false;
            }
        });
        int num = q.front();
        q.pop();

        std::cout << "Given number: " << num << std::endl;
    }
}

int main() {
    std::thread consumer(numReader);
    std::thread producer(numGen);
    
    producer.join();
    consumer.join();

    return 0;
}