#include <ctime>

extern time_t time_val;

void f(int a) {
    time_val = a;
}
