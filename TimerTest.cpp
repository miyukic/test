#include <iostream>
#include <cstdint>
#include <thread>
#include <chrono>
#include <iomanip>
#ifdef __unix
#include <fstream>
#include <string>
#include <sstream>
#elif _WIN32
#include <windows.h>
#endif

double getUptime();

uint32_t times = 0;
double systemTimeFrom = getUptime();

double getUptime() {
#ifdef __unix
	const std::string PROC_UPTIME = "/proc/uptime";
	std::ifstream ifs{PROC_UPTIME};
	if (!ifs) {
		std::cerr << "getSystemTime()でエラー" << std::endl; 
		exit(1);
	}
	std::string data;
	double r;
	getline(ifs, data);
	std::stringstream ss(data);
	std::string str;
	ss >> str;
	
	//std::cout << str << std::endl;
	return stod(str);
#elif _WIN32
    double r = GetTickCount64() / 1000.0;
    return r;
#endif
}

void tick() {
    times++;
    if (times >= 60) {
		std::cout << std::fixed << std::setprecision(8);
        double tc = getUptime();
		std::cout << "tc " << tc << std::endl;
        double result = systemTimeFrom - tc;
		std::cout << result << std::endl;
        systemTimeFrom = tc;
        times = 0;
    }
}

constexpr uint32_t WAIT_TIME = (1000 / 60) + 0.5;

int main() {
    while (true) {
        tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIME));
    }
     
    return 0;
}
