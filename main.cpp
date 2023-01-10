#include <iostream>
#include <vector>
#include <ranges>


int main() {
    std::vector<int> v(10);
    std::ranges::fill(std::ranges::begin(v) + 3, std::ranges::end(v), 5);
    for (const auto &n : v) {
        std::cout << n << std::endl;
    }
    return 0;
}
