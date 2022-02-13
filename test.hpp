#pragma once
#include <string>
#include <iostream>

using namespace std::literals::string_literals;

//class Console {
//    static const std::string ESC;
//    static int field[][10];
//
//public:
//    Console();
//    static void clear();
//
//    static void moveCursor(const int row, const int colum);
//
//    static void hideCursor();
//}; 

class Console {
    static const std::string ESC;
    static int field[][10];

public:
//    Console();

//    static void clear();
//
//    static void moveCursor(const int row, const int colum);
//
//    static void hideCursor();

    inline void clear() {
        std::cout << ESC + "1J\n"s;
    }

    inline void moveCursor(const int row, const int colum) {
        std::cout << "\u001B[" << row << ";" << colum << "H\n";
    }

    inline void hideCursor() {
        std::cout << "\u001B[>5h";
    }

}; 

inline const std::string Console::ESC = "\u001B";

inline int Console::field[][10] =  {
    {2, 3},
    {2, 3},
    {2, 3},
    {2, 3},
    {2, 3}
};


template <typename T>
class HogeHoge {
    static T foo = 20;
};

