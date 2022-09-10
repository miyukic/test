#include <iostream>

template<class T, class U>
auto True = [](T x){ [x](U y){ return x; }; };

int main() {
    std::cout << True(1)(2) << std::endl;
    return 0;
}
