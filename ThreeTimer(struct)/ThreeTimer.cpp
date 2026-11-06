#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
#include <string>

struct Timer {

    Timer (std::chrono::milliseconds breakTime, std::string timerName,
           std::chrono::steady_clock::time_point startTime) {
        sleepTime = breakTime;
        name = timerName;
        nextDue = startTime + sleepTime;
    }

    std::chrono::steady_clock::time_point nextDue;
    std::chrono::milliseconds sleepTime;
    std::string name;
};

int main() {

    auto start = std::chrono::steady_clock::now();
    Timer fast(std::chrono::milliseconds(200), "fast", start);
    Timer medium(std::chrono::milliseconds(500), "medium", start);
    Timer slow(std::chrono::milliseconds(1000), "slow", start);

    if (fast.nextDue < medium.nextDue || fast.nextDue < slow.nextDue) {
            std::this_thread::sleep_until(fast.nextDue);

            std::chrono::duration<float, std::milli> elapsed = std::chrono::steady_clock::now() - start;
            std::cout << fast.name << " " << elapsed.count() << std::endl; 

            fast.nextDue += fast.sleepTime;
        } else if (medium.nextDue < fast.nextDue || medium.nextDue < slow.nextDue) {
            

            


            std::chrono::duration<float, std::milli> elapsed = std::chrono::steady_clock::now() - start;
            std::cout << medium.name << " " << elapsed.count() << std::endl; 

            medium.nextDue += medium.sleepTime;

        } else if (slow.nextDue < fast.nextDue || slow.nextDue < medium.nextDue) {
            std::chrono::duration<float, std::milli> elapsed = std::chrono::steady_clock::now() - start;
            std::cout << slow.name << " " << elapsed.count() << std::endl; 

            slow.nextDue += slow.sleepTime;
 
        }
}
