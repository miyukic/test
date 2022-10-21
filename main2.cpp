#include <iostream>
#include <memory>
#include <stdint.h>

class Alpha {
    int16_t a : 12;
    int16_t b : 12;
};

int main() {
    std::unique_ptr<Alpha> ins = std::make_unique<Alpha>();
    Alpha al;
    std::cout << sizeof(al) << std::endl;
    return 0;
}
