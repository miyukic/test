#include <cstdio>
#include <ctime>
#include <iostream>

const int val = 1;
extern const int ext_val = 0x1234; 
const char *p_val = "aiueo";
extern const time_t time_val = std::time(NULL);

//extern const int sub_val = 21;

extern int sub_val;

extern constexpr int I = 0xEEEE;

constinit int coninit_val = 0x0000FFFF;

int f();

int main() {
    //printf("%p\n", &val);
    //printf("%d\n", ext_val);
    //printf("%s\n", p_val);
    //printf("%ld\n", time_val);
    //printf("%d\n", I);
    sub_val = const_cast<int>(sub_val);
    std::cout << sub_val << std::endl;
    std::cout << f() << std::endl;

}

//constexpr int f() {
//    return 0;
//}

