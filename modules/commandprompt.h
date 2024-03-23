#pragma once 

#include <stdio.h>
#include <windows.h>
#include <Shellapi.h>

int startCMD(int as_admin);
void ReportError(const char* msg);

int clearConsole();