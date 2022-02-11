#include <iostream>
#include <string>
#include <windows.h>
#include <memory>

using namespace std::literals::string_literals;

int counter = 0;
constexpr int FPS = 60;

void onTimer(void);
void onDraw(void);


class Console {
    static std::string ESC = "\u001B"s;
public:
    static void clear() {
        std::cout << ESC + "1J\n"s;
    }

    static void moveCursor(const int row, const int colum) {
        std::cout << "\u001B[" << row << ";" << colum << "H\n";
    }

    static void hideCursor() {
        std::cout << "\u001B[>5h";
    }
}; 

int main(int argc, char* argv[]) {
    std::cout << argv[0] << std::endl;
    const std::unique_ptr<std::string> message = std::make_unique<std::string>("引数なしで実行します。"s);
    if (argc <= 1) {
        std::cout << *message << std::endl;
    }

    for (int i = 1; i < argc; i++) {
        std::cout << argv[i] << std::endl;
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