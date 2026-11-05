// #include <iostream>
// #include <thread>
// #include <chrono>

// struct Timer {
//     int sleepTime;
//     int cycles;
// };

// int main() {
//     using namespace std::literals::chrono_literals;

//     Timer a;
//     Timer b;

//     a.sleepTime = 100;
//     a.cycles = 10;

//     b.sleepTime = 1000;
//     b.cycles = 1;
    
    
//     // for (int i = 0; i < 10; i++) {
//     //     if (a.sleepTime < b.sleepTime) {
//     //         b.sleepTime -= a.sleepTime;

//     //         auto nextTime = std::chrono::steady_clock::now() + std::chrono::milliseconds(a.sleepTime);
//     //         std::this_thread::sleep_until(nextTime);    

//     //         std::cout << "timer A completed 100ms" << std::endl;
//     //     }
//     // }

//     auto nextTime = std::chrono::steady_clock::now() + std::chrono::milliseconds(a.sleepTime);
//     std::this_thread::sleep_until(nextTime);    




    

    

//     return 0;
// }