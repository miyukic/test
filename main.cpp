#include <cstdio>
#include <ctime>

const int val = 1;
extern const int ext_val = 0x1234; 
const char *p_val = "aiueo";
extern const time_t time_val = std::time(NULL);

extern constexpr int I = 0xEEEE;

constinit int coninit_val = 0x0000FFFF;


int main() {
    printf("%p\n", &val);
    printf("%d\n", ext_val);
    printf("%s\n", p_val);
    printf("%ld\n", time_val);
    printf("%d\n", I);
}

constexpr int f() {
    return 0;
}

