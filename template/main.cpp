#include <iostream>

template<class T, class U, class V>
auto f(T a, U b) -> V {
    return a + b;
}

template<class... Args>auto g(Args... args) {
    return f<Args>(args...);
}

int main() {
    std::cout << g<int, int, int>(1, 5) << std::endl;
    return 0;
}
