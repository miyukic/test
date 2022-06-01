#include <stdio.h>
#include <time.h>
//#include <unistd.h>
//#include <timeapi.h>
#include <windows.h>

#pragma comment(lib, "winmm.lib")
DWORD t = 0;
int main(void) {
    timeBeginPeriod(1);
    for (int i = 0; i < 10; ++i) {
        DWORD t = timeGetTime();
        Sleep(1);
        printf("%lu\n", timeGetTime() - t);
    }
    timeEndPeriod(1);
    return 0;
}

