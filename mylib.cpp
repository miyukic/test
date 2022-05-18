
module;
#include <iostream>

class Hoge {
    int m = 0;
public:
    Hoge(): m{10} { }
    int getM() const noexcept;
};

int hello() {
    std::cout << "Hello" << std::endl;
}