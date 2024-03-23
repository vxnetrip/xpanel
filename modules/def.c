#include <stdio.h>

#include "def.h"

const char version[16] = "0.2.6";

#if defined(_WIN32)
    const char _platform[8] = "Windows";
#elif defined(__APPLE__)
    const char _platform[8] = "MacOS";
#else
    const char _platform[8] = "Linux";
#endif