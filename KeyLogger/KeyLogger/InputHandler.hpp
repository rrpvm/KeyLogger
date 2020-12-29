#pragma once
#include "Singleton.hpp"
#include <fstream>
#include <string>
#include <Windows.h>
class InputHandler : public Singleton<InputHandler> {
public:
	InputHandler() {};
	~InputHandler() {};
	static void resetInputArray(bool* array, int size);
	void printToFile(const char* directory);
	std::string GetDirectoryToFile();
	void AddToBuffer(char value);
	void GetPressedChar();
	std::string buffer;
};