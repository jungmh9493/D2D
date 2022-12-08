#include "stdafx.h"
#include "Window.h"
#include "Program.h"

Program* Window::program = nullptr;
bool Window::isWindowCreated = false;

Window::Window(const WinDesc& initDesc)
{
    desc = initDesc;

    WORD wHr = MyRegisterClass(desc);   // ��ȯ�� ���� ���� : 
    assert(wHr != 0);   // wHr�� 0�̶��, Register Ŭ������ ��ȯ���� 0 -> ����� ����� ���� �ʾҴ�.

    desc.handle = CreateWindowExW
    (
        WS_EX_APPWINDOW,
        desc.appName.c_str(),   // ����� Ŭ������ �̸��� ������ �̸��� �Ѱ��־�� �Ѵ�.
        desc.appName.c_str(),   // EX : �⺻���� ���ݴ� Ȯ��� ����� ����� �� �ִ�.
        WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        nullptr,
        (HMENU)nullptr,
        desc.instance,
        nullptr
    );

    RECT rect = { 0, 0, (LONG)desc.width, (LONG)desc.height };  // RECT : �簢���� ������ ����, ǥ�����ִ� ����ü

    // GetSystemMetrics(SM_CXSCREEN or SM_CYSCREEN) : ���� ȭ�鿡���� ��ǥ�� / SM_CXSCREEN : x��ǥ, SM_CYSCREEN : y��ǥ
    UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)desc.width) / 2;
    UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)desc.height) / 2;

    AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, 0);   // �����Ǵ� ������ â ũ�� ����

    MoveWindow
    (
        desc.handle,
        centerX,
        centerY,
        rect.right - rect.left,
        rect.bottom - rect.top,
        true
    );

    ShowWindow(desc.handle, SW_SHOWNORMAL);
    // SW_SHOWNORMAL : �����츦 Ȱ��ȭ ���·� ����� �ɼ� -> ��Ŀ���� ��������. -> �Է� �޽����� �ش� ������� ���޵ȴ�.
    // �ִ�ȭ ��ų�, �ּ�ȭ �� ���, �� ���·� ������Ű�� ��ɵ� �ִ�.
    UpdateWindow(desc.handle);
    // repaint, redraw
    // ȭ���� �ٽ� �׸��� ��Ȳ -> WM_PAINT �߻� -> �޽��� ť�� ����.
    // ó�� ���� ���� �޽����� �з��� WM_PAINT�� ó���� �ȵǴ� ��Ȳ�� �߻��� ���ɼ��� �ִ�.
    // InvalidateRect : �ǵ������� WM_PAINT �޽����� �߻���Ű�� �Լ�
    // UpdateWindow : �޽��� ť�� ����ִ� WM_PAINT �޽����� �ﰢ������ ó���ϵ��� �ϴ� �Լ�
    ShowCursor(true);   // false ó���ϸ� ���콺 Ŀ���� ������ �ʰ� �ȴ�.

    isWindowCreated = true;
    //   this->desc = desc;  // desc.handle�� ���� ���� �ϱ� ������
}

Window::~Window()
{
    DestroyWindow(desc.handle);     // �ش� ���� ��ȣ(handle)�� ���� ������ â�� ����(�Ҹ�)
    UnregisterClassW(desc.appName.c_str(), desc.instance);  // ������ â �Ҹ��, ����س��� Ŭ������ ��� ����
}

ATOM Window::MyRegisterClass(const WinDesc& desc)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);       // cbSize ���� ���� ���� ����� üũ(���� üũ)

    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;   // ���� Ŭ������ ��Ÿ���� ������ �� �ִ�.
    // HREDRAW / VREDRAW -> H(horizon) / V(vertical) ���� ������ ��������� �ִٸ� �ٽ� �׷��ְڴ�.
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = desc.instance;
    wcex.hIcon = LoadIcon(nullptr, IDI_WINLOGO);    // Icon : �۾� ǥ������ ������ / IDI_WINLOGO : �⺻ �ΰ�
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);    // hbrBackGround : ����
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = desc.appName.c_str();  // C��Ÿ�� ���ڿ��� �����ڵ����·� �޾ƿ´�.
    wcex.hIconSm = wcex.hIcon;                  // IconSmall : ������ â ��ܿ� ���� �������� ��Ÿ����

    return RegisterClassExW(&wcex); // ������ ������ �������� ������ â�� ����ϰ�, �ش� ������ return �Ѵ�.
}

WPARAM Window::Run()
{
    MSG msg = { 0 };

    program = new Program();
    // �⺻ �޽��� �����Դϴ�:
    while (true)
    {
        // GetMessage : �޽��� ť�� �޽����� �������� ������ �޽����� ���ö����� ��ٸ���.
        // PeekMessage : �޽����� �������� ������ �Լ� ȣ���� �����Ѵ�.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) // WM : ������ �޽���
                break;

            INPUT->InputProc(msg.message, msg.lParam);

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else // �޽����� ���� �߻����� ������ ������Ʈ
        {
            INPUT->Update();
            TIME->Update();

            program->Update();

            program->PreRender();
            GRAPHICS->Begin();
            {
                program->Render();
                program->PostRender();
            }
            GRAPHICS->End();
        }
    }

    Graphics::Delete();

    SAFE_DELETE(program);

    TIME->Delete();
    INPUT->Delete();

    return msg.wParam;
}

LRESULT Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_CREATE)     // ������ â�� �����Ǿ��� �� �߻� (Ŭ������ ������)
    {
        gHandle = handle;
    }

    if (isWindowCreated && message == WM_SIZE)  // ������ ������ â�� ������ �� -> ������ â�� ����� ����Ǿ��� ���
    {
        gWinWidth = LOWORD(lParam);
        gWinHeight = HIWORD(lParam);
        GRAPHICS->Resize(gWinWidth, gWinHeight);
    }

    if (message == WM_CLOSE || message == WM_DESTROY)   // WM_CLOSE : ������ â x��ư Ŭ�� / WM_DESTROY : ������ â�� � ������ε� �ı��Ǿ��� ��
    {
        PostQuitMessage(0);     // �޽����� ���̻� ���� �ʰڴ�. -> WM_QUIT�� �߻���Ų��.

        return 0;
    }

    return DefWindowProc(handle, message, wParam, lParam);
}
