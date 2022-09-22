#include <stdio.h>

extern int H;

void A(void);

int main(void) {
    A();
    printf("Hの値は%dです。", H);
    return 0;
}
