#include <iostream>
#include <cstdint>

uint64_t fib(uint64_t n) {
    if (n == 0 || n == 1) {
        return n;
    }
    uint64_t a = 0;
    uint64_t b = 1;
    for (uint64_t i = 1; i < n; ++i) {
        uint64_t c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    std::cout << fib(100) << "\n";
}
