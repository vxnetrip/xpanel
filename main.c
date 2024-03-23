#include <stdio.h>
#include <windows.h>

#include "modules/commandprompt.h"
#include "modules/def.h"
#include "modules/detect.h"

int startInit(); // Forward declaration of startInit

int showMenu() {
    printf("________________________________________________________________________________________________________________________\n");
    printf("    BACKSPACE + A | -> CMD as User      BACKSPACE + W | -> EXIT\n");
    printf("    BACKSPACE + B | -> CMD as Admin                             \n");
    printf("    BACKSPACE + C | -> Scan Directory                               \n");
    printf("    BACKSPACE + D | -> Disk Info                               \n");
    printf("________________________________________________________________________________________________________________________\n");

    while (1) {
        if (GetAsyncKeyState(VK_BACK) & 0x8000) {
            if (GetAsyncKeyState('A') & 0x8000) { // BACKSPACE + A
                startCMD(0);
                startInit();
                break;
            } else if (GetAsyncKeyState('B') & 0x8000) { // BACKSPACE + B
                startCMD(1);
                startInit();
                break;
            } else if (GetAsyncKeyState('C') & 0x8000) {
                char* result = dirscan("C:/");
                printf(result);
                char buff[32];
                sprintf("%s", buff);
                startInit();
                break;
            }
            else if (GetAsyncKeyState('W') & 0x8000) { // BACKSPACE + C
                startInit();
                break;
            }
        }
    }
}

int startInit() {
    clearConsole();
    printf("________________________________________________________________________________________________________________________\n");
    printf("                                              -> X PANEL | SysOverlay\n");
    printf("                                              -> OS: %s %s\n", _platform, detect_os_v());
    printf("                                              -> USER: %s\n", detect_os_user());
    printf("                                              -> VERSION: %s\n", version);
    printf("                                              -> PRESS BACKSPACE + Q TO OPEN PANEL\n");
    printf("                                              -> CPU: n/a\n");
    printf("                                              -> GPU: n/a\n");
    printf("                                              -> DISK: n/a\n");
    printf("________________________________________________________________________________________________________________________\n");
}

int main() {
    //HWND hwnd = GetConsoleWindow();
    //SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    while (1) {
        startInit();
        while (1) {
            if (GetAsyncKeyState(VK_BACK) & 0x8000 && GetAsyncKeyState('Q') & 0x8000) { // BACKSPACE + Q
                showMenu();
                break;
            }
        }
    }

    return EXIT_SUCCESS;
}