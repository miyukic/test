#include <stdio.h>
#include <stdlib.h>

#define UINT unsigned int
typedef UINT uint32_t;

int main(void){
    int* array = (int*) malloc(sizeof(int) * 10);
    uint32_t i;
    for (i = 0; i < 10; ++i) {
        array[i] = i;
    }
    for (i = 0; i < 10; ++i) {
        printf("array=%d", array[i]);
    }
    puts("\n");
    const int* toCpy = (int*) malloc(sizeof(int) * 10);
    memcpy(toCpy, array, sizeof(int)*10);
    for (i = 0; i < 10; ++i) {
        printf("toCpy=%d", array[i]);
    }
}

