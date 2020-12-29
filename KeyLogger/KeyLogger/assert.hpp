#pragma once
#include <Windows.h>
#define assert(expression)if(!(expression)){MessageBox(NULL,(LPCWSTR)("Assertion failed on line +" + __LINE__),(LPCWSTR)"Assetion failed",MB_OK);abort();}