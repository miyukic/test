#include <iostream>
#include <cstdint>

uint64_t fib(uint32_t n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fib(n - 1) + fib(n - 2);
    }       
}


template <uint64_t N>
struct Fib {
    static constexpr uint64_t val = Fib<N - 1>::val + Fib<N - 2>::val;
};

template <>
struct Fib<1> {
    static constexpr uint64_t val = 1;
};

template <>
struct Fib<0> {
    static constexpr uint64_t val = 0;
};

int main() {
    //std::cout << fib(50) << "\n";
    std::cout << Fib<100>::val << "\n";
}
