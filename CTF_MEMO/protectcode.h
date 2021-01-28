#pragma once
//#include "pch.h"
#include <Windows.h>
_declspec(dllexport)
void protectcode(LPBYTE EP, DWORD size, HANDLE hProc);
_declspec(dllexport)
void test();