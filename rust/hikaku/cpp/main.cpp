#include <cstdint>
#include <iostream>

struct MyStruct {
    int32_t a;
    int64_t b;
};

int main() {
    auto ms = MyStruct{32, 123};
    std::cout << "ms.a" << ms.a << "\n";
    std::cout << "ms.b" << ms.b << std::endl;
    return 0;
}
