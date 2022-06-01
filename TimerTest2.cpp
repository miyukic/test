#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>


int main() {
    double total_time = 0.00;
    for (std::size_t i = 0; i < 100000; ++i ) {
        auto start = std::chrono::system_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(0)); //1ms待機
        auto end = std::chrono::system_clock::now();
        total_time += static_cast<double>(
                std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0);
    }
    std::cout << std::fixed << std::setprecision(6);
    std::cout << total_time << std::endl;
}
