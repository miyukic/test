#include <stdio.h>
#include <unistd.h>


int main(void) {
    for (;;) {
        setvbuf(stdout, NULL, _IONBF, 0);
        printf("message");
        //fflush(stdout);
        sleep(1);
    }
    return 0;
}

//void cfunc(void) {
//    puts("called cfunc");
//}
