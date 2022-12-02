#include <iostream>
#include <cstdio>

template<std::size_t N, double R = 0.1> struct Sum {
    static constexpr double value = R + Sum<N-1>::value;
};

template<> struct Sum<0> {
    static constexpr double value = 0.0;
};

int main() {

    std::printf("%.16f", Sum<1000>::value);

    double sum = 0.0;
    for (size_t i = 0; i < 1000; ++i) {
        sum += 0.1;
    }
    std::printf("%.16f",sum);
    return 0;
}
