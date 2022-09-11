#include <iostream>
#include <string>
#include <Windows.h>


int main(int argc, char* argv[]) {

    SetConsoleOutputCP(CP_UTF8);
    std::string hoge = "東京タワー";
    std::cout << hoge << std::flush;

    std::wstring aiueo = L"あいうえお";
    std::wcout << aiueo << std::endl;
}

