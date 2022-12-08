#include "stdafx.h"
#include "Systems/Window.h"

HWND gHandle = nullptr;
float gWinWidth = WIN_DEFAULT_WIDTH;
float gWinHeight = WIN_DEFAULT_HEIGHT;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,     // winAPI�� �⺻ ���� �Լ�, ������ �����Լ��� ���°� �ٸ���, winAPI�� �������� �ȴ�.
    _In_opt_ HINSTANCE hPrevInstance,   // 16bit �ü�������� �ǹ̰� �վ�����, ������ �ƿ�������� �ʴ´�.
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    WinDesc desc;
    desc.appName = L"WinAPI";
    desc.instance = hInstance;  // �����ϸ� �ڵ����� instance�� ���´�.
    desc.handle = nullptr;
    desc.width = gWinWidth;
    desc.height = gWinHeight;

    Window* window = new Window(desc);
    WPARAM wParam = window->Run();
    SAFE_DELETE(window);

    return (int)wParam; // ���������� ���� wParam�� �޽����� ��ȯ�ȴٸ� ���α׷��� �������� ���ᰡ ��ٰ� �� �� �ִ�.
}