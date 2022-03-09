#include <cstdint>
#include <utility>

#include "main.hpp"

uint64_t saisyoKoubai(uint64_t a, int64_t b) {
    uint64_t (a * b) / saidaiKouyaku(a, b);
}

uint64_t saidaiKouyaku(uint64_t a, uint64_t b) {
    if (a < b) {
        std::swap(a, b);
    }
    auto q1 = a / b;
    auto r1 = a % b; 
    auto q2 = b / r1;
    auto r2 = b % r1;
    return r2;
    //auto q3 = q1 / r2;
    
}


int main() {
    return 0;
}
