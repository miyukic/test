#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>

#ifdef _WIN32
#pragma comment(lib, "winmm.lib")
#include <Windows.h>
DWORD t = 0;
int main() {
    //timeBeginPeriod(1);
    decltype(std::chrono::system_clock::now()) t;
    for (int i = 0; i < 10; ++i) {
        t = std::chrono::system_clock::now();
        Sleep(1);
        printf("%lf\n", 
                static_cast<double>(
                    std::chrono::duration_cast<std::chrono::microseconds>(
                        std::chrono::system_clock::now() - t
                        ).count() / 1000.0
                    )
              );
    }
    //timeEndPeriod(1);
    return 0;
}

#elif __unix

int main() {
    double total_time = 0.00;
    for (std::size_t i = 0; i < 1000; ++i ) {
        auto start = std::chrono::system_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); //1ms待機
        auto end = std::chrono::system_clock::now();
        total_time += static_cast<double>(
                std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0);
    }
    std::cout << std::fixed << std::setprecision(6);
    std::cout << total_time << std::endl;
}
#endif
