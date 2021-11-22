#include <iostream>

extern "C" {
    void cfunc(void);
}

int main() {
    cfunc();
    return 0;
}

