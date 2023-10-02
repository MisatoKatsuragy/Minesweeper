#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <WindowsX.h>
#include <cstdio>
#include <cstdlib>
#include <ddraw.h>
#include <vector>
#include <algorithm>
#pragma comment(lib, "ddraw.lib")

#ifdef assert
#undef assert
#endif	
#define assert(x) if (!(x)) __asm { int 3 }