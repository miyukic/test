#include <iostream>

int main() {
    uint32_t A500, B100, C50, X;
    std::cin >> A500 >> B100 >> C50 >> X;

    uint32_t count{0};
    for (size_t i = 0; i <= A500; i++) {
        for (size_t j = 0; j <= B100; j++) {
            for (size_t k = 0; k <= C50; k++) {
                if ((i * 500 + j * 100 + k * 50) == X) {
                    count++;
                }
            }
        }
    }
    std::cout << count;
}

