#include <stdio.h>
#include <windows.h>

char* detect_os_v() {
    static char os_version[256]; // static buffer for storing the version string
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    if (!GetVersionEx(&osvi)) {
        fprintf(stderr, "Failed to get os version info\n");
        return NULL; // Indicate failure by returning NULL
    }

    // Format the version string
    snprintf(os_version, sizeof(os_version), "%lu.%lu.%lu", osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber);
    return os_version;
}

char* detect_os_user() {
    static char charusr[32]; // Static buffer for storing the username string
    TCHAR username[32];
    DWORD username_len = 32;

    if (!GetUserName(username, &username_len)) {
        fprintf(stderr, "Failed to get user login name\n");
        return NULL; // Indicate failure by returning NULL
    }

    // Convert username to wide character string
    WCHAR wide_username[32];
    if (MultiByteToWideChar(CP_UTF8, 0, username, -1, wide_username, sizeof(wide_username)) == 0) {
        fprintf(stderr, "Failed to convert username to wide character string\n");
        return NULL; // Indicate failure by returning NULL
    }

    // Convert wide character username to UTF-8
    if (WideCharToMultiByte(CP_UTF8, 0, wide_username, -1, charusr, sizeof(charusr), NULL, NULL) == 0) {
        fprintf(stderr, "Failed to convert wide character username to UTF-8\n");
        return NULL; // Indicate failure by returning NULL
    }

    return charusr;
}


char* dirscan(const char* path) {
    WIN32_FIND_DATAA findData;
    HANDLE hFind;
    static char result[4096] = ""; // Static buffer to store the result

    char searchPath[MAX_PATH];
    sprintf(searchPath, "%s\\*", path);

    hFind = FindFirstFileA(searchPath, &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Error opening directory\n");
        return NULL;
    }

    do {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            sprintf(result + strlen(result), "Directory: %s\n", findData.cFileName);
        } else {
            sprintf(result + strlen(result), "File: %s\n", findData.cFileName);
        }
    } while (FindNextFileA(hFind, &findData) != 0);

    FindClose(hFind);

    return result;
}
