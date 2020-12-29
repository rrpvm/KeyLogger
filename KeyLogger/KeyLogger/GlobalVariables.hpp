#pragma once
#include <Windows.h>
#include "Singleton.hpp"
#define MAX_LOADSTRING 100
class GlobalVariables : public Singleton <GlobalVariables> {
public:
	GlobalVariables() {};
	~GlobalVariables() {};	
	WCHAR* getTitle() { return szTitle; }
	WCHAR* getSzWindowClass() { return szWindowClass; }
	HINSTANCE* getHinst() { return &hInst; }
	bool* getKeyInput() { return keyInput; }

private:
	WCHAR szTitle[MAX_LOADSTRING];
	WCHAR szWindowClass[MAX_LOADSTRING];
	HINSTANCE hInst;
	bool keyInput[256];
};