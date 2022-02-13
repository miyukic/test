#include <iostream>
#include <string>
#include <windows.h>
#include <memory>
#include <xstring>

#include "test.hpp"

#define dbg(...) std::cout << #__VA_ARGS__ << " = " << [&]{ return __VA_ARGS__; }() << std::endl;

using namespace std::literals::string_literals;

int counter = 0;
constexpr int FPS = 60;

void onTimer(void);
void onDraw(void);




int x[] = {
    2, 3, 4
};


int nums[][4] = {
    {1, 2, 3, 5},
    {1, 2, 3, 5},
    {1, 2, 3, 5},
    {1, 2, 3, 5}
};


//const std::string Console::ESC = "\u001B";

//int Console::field[][10] =  {
//    {2, 3},
//    {2, 3},
//    {2, 3},
//    {2, 3},
//    {2, 3}
//};

//Console::Console() {}

//void Console::clear() {
//    std::cout << ESC + "1J\n"s;
//}

//inline void Console::moveCursor(const int row, const int colum) {
//    std::cout << "\u001B[" << row << ";" << colum << "H\n";
//}

//void Console::hideCursor() {
//    std::cout << "\u001B[>5h";
//}

int main(int argc, char* argv[]) {
    std::cout << argv[0] << std::endl;
    const std::unique_ptr<std::string> message = std::make_unique<std::string>("引数なしで実行します。"s);
    if (argc <= 1) {
        //std::cout << *message << std::endl;
        dbg(*message)
    }

    for (int i = 0; i < argc; i++) {
        //std::cout << argv[i] << std::endl;
        dbg(argv[i])
    }
    
    while (true) {
        Sleep(1000 / FPS);        
        onTimer();
    }
}

void onDraw() {
    Console::clear();
    Console::moveCursor(0, 0);
}

void onTimer() {
    counter++;
    onDraw();
    std::cout << counter;
}
