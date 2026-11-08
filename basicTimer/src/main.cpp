// Runs two periodic timers, a fast "sensor" (500ms) and a slow "status"
// (5000ms), from a single thread.
//
// Each Timer stores its period and the time it is next due. Every loop,
// main picks whichever timer's due time is soonest, sleeps until exactly
// that moment with sleep_until (not sleep_for), then fires it and pushes
// only that timer's due time forward by one period.
//
// Because each timer is anchored to a fixed due time rather than "sleep
// then re-sleep", lateness never accumulates across iterations.

#include <iostream>
#include <chrono>
#include <thread>

class Timer {
public:
    // time in ms to be entered ehre.
    Timer(int time, int it, std::string name) {
        sleepTime = std::chrono::milliseconds(time);
        nextDue = std::chrono::steady_clock::now() + sleepTime;
        cycles = it;
        timerName = name;
    }

    void customSleep() {
        using namespace std::literals::chrono_literals;

        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < cycles; i++) {
                
                std::this_thread::sleep_for(sleepTime); 
                auto end = std::chrono::steady_clock::now();

                std::chrono::duration<float, std::milli> time = end - start;
                std::cout << timerName << ": " << time.count() << "ms" << std::endl;
            }
    }

    std::chrono::steady_clock::time_point getNextDue() {
        return nextDue;
    }


    void increaseNextDue(std::chrono::milliseconds increaseTime) {
        nextDue += increaseTime;
    }

    std::chrono::milliseconds getSleepTime() {
        return sleepTime;
    }

private:
    std::chrono::milliseconds sleepTime;
    int cycles;
    std::string timerName;
    std::chrono::steady_clock::time_point nextDue;
    
};



int main() {
    Timer sensor(500, 10, "sensor");
    Timer status(5000, 1, "status");


    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < 30; i++) {

        

        if (sensor.getNextDue() < status.getNextDue()) {
           
            std::this_thread::sleep_until(sensor.getNextDue());

            std::chrono::duration<float, std::milli> nextDueTimeSensor = sensor.getNextDue() - start;
            std::chrono::duration<float, std::milli> nextDueTimeStatus = status.getNextDue() - start;
            std::cout << "nextDue (sensor): " << nextDueTimeSensor.count() << " -- nextDue (status): " << nextDueTimeStatus.count();
            std::cout << " ---- sensor (WIN) completed 500ms" << std::endl;

            sensor.increaseNextDue(sensor.getSleepTime());

        } else {

            std::this_thread::sleep_until(status.getNextDue());

            status.increaseNextDue(status.getSleepTime());
            std::cout << " ---- status (WIN) completed 5000ms" << std::endl;
        }

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<float, std::milli> duration = end - start;
        std::cout << "time elapsed: " << duration.count() << std::endl;
    }

    

    // sensor.customSleep();
    // status.customSleep();
    

    return 0;
}