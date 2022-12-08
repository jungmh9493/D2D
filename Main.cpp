#include "stdafx.h"
#include "Systems/Window.h"

HWND gHandle = nullptr;
float gWinWidth = WIN_DEFAULT_WIDTH;
float gWinHeight = WIN_DEFAULT_HEIGHT;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,     // winAPI의 기본 메인 함수, 기존의 메인함수와 형태가 다르다, winAPI의 진입점이 된다.
    _In_opt_ HINSTANCE hPrevInstance,   // 16bit 운영체제에서는 의미가 잇었지만, 지금은 아예사용하지 않는다.
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    WinDesc desc;
    desc.appName = L"WinAPI";
    desc.instance = hInstance;  // 실행하면 자동으로 instance가 들어온다.
    desc.handle = nullptr;
    desc.width = gWinWidth;
    desc.height = gWinHeight;

    Window* window = new Window(desc);
    WPARAM wParam = window->Run();
    SAFE_DELETE(window);

    return (int)wParam; // 마지막으로 받은 wParam의 메시지가 반환된다면 프로그램이 정상적인 종료가 됬다고 할 수 있다.
}