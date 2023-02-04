#include <iostream>
#include <Windows.h>

int main() {
//    LPCRITICAL_SECTION cs;
    int i = 0;
    int* p = &i;
    //uintptr_t ptoi = reinterpret_cast<uintptr_t>(p);
    uintptr_t ptoi = uintptr_t(p);

    std::cout << std::hex << ptoi << std::endl;

}
