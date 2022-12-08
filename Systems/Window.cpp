#include "stdafx.h"
#include "Window.h"
#include "Program.h"

Program* Window::program = nullptr;
bool Window::isWindowCreated = false;

Window::Window(const WinDesc& initDesc)
{
    desc = initDesc;

    WORD wHr = MyRegisterClass(desc);   // 반환값 존재 이유 : 
    assert(wHr != 0);   // wHr이 0이라면, Register 클래스의 반환값이 0 -> 등록이 제대로 되지 않았다.

    desc.handle = CreateWindowExW
    (
        WS_EX_APPWINDOW,
        desc.appName.c_str(),   // 등록한 클래스의 이름과 동일한 이름을 넘겨주어야 한다.
        desc.appName.c_str(),   // EX : 기본에서 조금더 확장된 기능을 사용할 수 있다.
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

    RECT rect = { 0, 0, (LONG)desc.width, (LONG)desc.height };  // RECT : 사각형의 영역을 설정, 표시해주는 구조체

    // GetSystemMetrics(SM_CXSCREEN or SM_CYSCREEN) : 실제 화면에서의 좌표값 / SM_CXSCREEN : x좌표, SM_CYSCREEN : y좌표
    UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)desc.width) / 2;
    UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)desc.height) / 2;

    AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, 0);   // 생성되는 윈도우 창 크기 설정

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
    // SW_SHOWNORMAL : 윈도우를 활성화 상태로 만드는 옵션 -> 포커스가 맞춰졌다. -> 입력 메시지가 해당 윈도우로 전달된다.
    // 최대화 됬거나, 최소화 된 경우, 원 상태로 복원시키는 기능도 있다.
    UpdateWindow(desc.handle);
    // repaint, redraw
    // 화면을 다시 그리는 상황 -> WM_PAINT 발생 -> 메시지 큐에 들어간다.
    // 처리 되지 못한 메시지가 밀려서 WM_PAINT가 처리가 안되는 상황이 발생할 가능성이 있다.
    // InvalidateRect : 의도적으로 WM_PAINT 메시지를 발생시키는 함수
    // UpdateWindow : 메시지 큐에 들어있는 WM_PAINT 메시지를 즉각적으로 처리하도록 하는 함수
    ShowCursor(true);   // false 처리하면 마우스 커서가 보이지 않게 된다.

    isWindowCreated = true;
    //   this->desc = desc;  // desc.handle에 값이 들어가야 하기 때문에
}

Window::~Window()
{
    DestroyWindow(desc.handle);     // 해당 고유 번호(handle)을 가진 윈도우 창을 제거(소멸)
    UnregisterClassW(desc.appName.c_str(), desc.instance);  // 윈도우 창 소멸시, 등록해놓은 클래스도 등록 해제
}

ATOM Window::MyRegisterClass(const WinDesc& desc)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);       // cbSize 현재 만들 것의 사이즈를 체크(버전 체크)

    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;   // 만들 클래스의 스타일을 지정할 수 있다.
    // HREDRAW / VREDRAW -> H(horizon) / V(vertical) 수평 수직의 변경사항이 있다면 다시 그려주겠다.
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = desc.instance;
    wcex.hIcon = LoadIcon(nullptr, IDI_WINLOGO);    // Icon : 작업 표시줄의 아이콘 / IDI_WINLOGO : 기본 로고
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);    // hbrBackGround : 배경색
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = desc.appName.c_str();  // C스타일 문자열을 유니코드형태로 받아온다.
    wcex.hIconSm = wcex.hIcon;                  // IconSmall : 윈도우 창 상단에 작은 아이콘을 나타낸다

    return RegisterClassExW(&wcex); // 설정한 내용을 바탕으로 위도우 창을 등록하고, 해당 내용을 return 한다.
}

WPARAM Window::Run()
{
    MSG msg = { 0 };

    program = new Program();
    // 기본 메시지 루프입니다:
    while (true)
    {
        // GetMessage : 메시지 큐에 메시지가 존재하지 않으면 메시지가 들어올때까지 기다린다.
        // PeekMessage : 메시지가 존재하지 않으면 함수 호출을 종료한다.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) // WM : 윈도우 메시지
                break;

            INPUT->InputProc(msg.message, msg.lParam);

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else // 메시지가 따로 발생하지 않으면 업데이트
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
    if (message == WM_CREATE)     // 윈도우 창이 생성되었을 때 발생 (클래스의 생성자)
    {
        gHandle = handle;
    }

    if (isWindowCreated && message == WM_SIZE)  // 완전히 원도우 창이 생성된 후 -> 윈도우 창의 사이즈가 변경되었을 경우
    {
        gWinWidth = LOWORD(lParam);
        gWinHeight = HIWORD(lParam);
        GRAPHICS->Resize(gWinWidth, gWinHeight);
    }

    if (message == WM_CLOSE || message == WM_DESTROY)   // WM_CLOSE : 윈도우 창 x버튼 클릭 / WM_DESTROY : 윈도우 창이 어떤 방식으로든 파괴되었을 때
    {
        PostQuitMessage(0);     // 메시지를 더이상 받지 않겠다. -> WM_QUIT을 발생시킨다.

        return 0;
    }

    return DefWindowProc(handle, message, wParam, lParam);
}
