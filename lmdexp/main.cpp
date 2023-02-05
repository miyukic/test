#include "sub.h"
#include <iostream>

int main() {
    auto f = [](){std::cout << "lambda" << std::endl;};
    sub(f);
}
