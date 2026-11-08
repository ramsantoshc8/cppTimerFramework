#include <iostream>
#include <thread>
#include <atomic>

int count = 0;
std::atomic<bool> running(true);

void worker() {
    while(running) {
        if (count >= 200000) {
            running = false;
            std::cout << "stopped at worker" << std::endl;
            break;
            
        }
        count++;
    }

}

int main() {
    std::thread t2(worker);

    while (count < 200000) {
        count++;
    }
    running = false;
    t2.join();

    std::cout << "reached 200,000 " << count << std::endl;
    
    return 0;
}
