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
    inline static const uint8_t SIZE_X = 21;
    inline static const uint8_t SIZE_Y = 16;
    inline static const std::string Console::ESC = "\u001B";
                                                     
    inline static int8_t Console::field[SIZE_Y][SIZE_X] = {           
        // 21x16
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }
    };                                               

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

class Fuga {
public:
    void hoge();
};

inline void Fuga::hoge() {
    std::cout << "Fuga#hoge" << std::endl;
}

//inline const std::string Console::ESC = "\u001B";
//
//inline int Console::field[10][10] =  {
//    {2, 3},
//    {2, 3},
//    {2, 3},
//    {2, 3},
//    {2, 3}
//};


template <typename T>
class HogeHoge {
    static T foo = 20;
};

