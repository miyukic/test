#include <Windows.h>
#include <iostream>
#include <locale>
#include <string>


int main(/*int argc, char* argv[]*/) {

    //SetConsoleOutputCP(CP_UTF8);
    std::wstring test = L"." + std::to_wstring(GetConsoleCP());
    std::wcout.imbue(std::locale(std::locale("."+std::to_string(GetConsoleCP()),
                    std::locale::ctype)));
            std::wcout << L"東京スカイツリー" << test << std::endl;

    //std::wcout.imbue(std::locale("Japanese"));
    //std::wstring skytree = L"東京スカイツリー";
    //std::wcout << skytree << std::endl;
}

