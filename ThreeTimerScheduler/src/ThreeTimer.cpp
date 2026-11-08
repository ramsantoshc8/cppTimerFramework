// threeTimerScheduler
//
// A single-threaded scheduler for three periodic timers (200ms, 500ms,
// 1000ms), all anchored to the same start time.
//
// Each round, std::min_element finds the timer with the earliest nextDue,
// the program sleeps until that time with sleep_until, then only the
// timer that fired has its nextDue advanced by its own period.
//
// This avoids busy-waiting (the thread uses no CPU while asleep) and
// avoids drift (a timer's schedule is never reset relative to "now",
// only advanced from its own fixed due time).

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

    std::vector<Timer> timerVec = {fast, medium, slow};

    
    for (int i = 0; i < 10; i++) {
        auto timer = std::min_element(timerVec.begin(), timerVec.end(), 
        [](Timer &a, Timer &b) {

            if (a.nextDue < b.nextDue) {
                return true;
            } else {
                return false;
            }
        });
        std::this_thread::sleep_until(timer->nextDue);
        timer->nextDue += timer->sleepTime;

        auto currTime = std::chrono::steady_clock::now();
        std::chrono::duration<float, std::milli> timeDiff = currTime - start;
        std::cout << timer->name << " " << timeDiff.count() << std::endl;
    }
}
