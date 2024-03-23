#include <stdio.h>
#include <windows.h>
#include <Shellapi.h>

#include "def.h"



// Check per4missions command line: [net session]

void ReportError(const char* msg) {
    fprintf(stderr, "%s failed with error %lu\n", msg, GetLastError());
}

// 0 = True
// 1 == False

int startCMD(int as_admin) {
    SHELLEXECUTEINFO shExecInfo = {0};
    shExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    shExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    shExecInfo.lpFile = "cmd.exe"; // Command to execute

    if (as_admin == 1) {
        shExecInfo.lpVerb = "runas";  // Run as administrator
        shExecInfo.lpParameters = "/c start cmd.exe /k \"cd /d %USERPROFILE%\\Desktop && echo -*- Launched new console as Administrator -*-\""; // Parameters for the command
    } else {
        shExecInfo.lpParameters = "/c start cmd.exe /k \"cd /d %USERPROFILE%\\Desktop && echo -*- Launched new console as User -*-\""; // Parameters for the command
    }

    // Execute the command as administrator
    if (!ShellExecuteEx(&shExecInfo)) {
        ReportError("ShellExecuteEx");
        return 1;
    }

    // Wait for the command to finish
    WaitForSingleObject(shExecInfo.hProcess, INFINITE);

    // Close handle
    CloseHandle(shExecInfo.hProcess);

    return EXIT_SUCCESS;
}


int clearConsole() {
    if ( strcmp(_platform, "Windows") == 0 ) {
        system("cls");
    } else {
        system("clear");
    }
    return 0;
}