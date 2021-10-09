#include <stdio.h>

const int globalValue = 0;

int sub();

int main() {
    int b = globalValue;
}

int sub() {
    return 0;
}
