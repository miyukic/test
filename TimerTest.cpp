#include <iostream>
#include <cstdint>
#include <thread>
#include <chrono>
#ifdef __unix
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#endif

double getSystemTime();

uint32_t times = 0;
double systemTimeFrom = getSystemTime(); 

double getSystemTime() {
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
}

void tick() {
    times++;
    if (times >= 60) {
        double tc = getSystemTime();
        double result = systemTimeFrom - tc;
		std::cout << std::fixed << std::setprecision(8);
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
