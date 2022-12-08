#pragma once

struct WinDesc		// description : 구현내용의 설명서 / 용도를 담아내는 것
{
	wstring appName = L"";	// Application Name
	HINSTANCE instance = nullptr;	// instance : handle의 고유 번호를 통한 실제주소를 담고 있는 것
	HWND handle = nullptr;
	float width = 0.0f;			// 너비
	float height = 0.0f;		// 높이
};

class Window
{
public:
	Window(const WinDesc& initDesc);
	~Window();

	ATOM MyRegisterClass(const WinDesc& desc);		// ATOM -> WORD -> unsigned short
	// Window 클래스를 등록하는 과정 -> 등록된 Window 클래스를 통해 윈도우 창 생성 -> 창 생성후 종료할때까지 Run(동작)

	WPARAM Run();

private:
	// 메시지 처리 함수 : 윈도우 창 내에서 메시지가 호출되면 자동적으로 호출되는 함수
	// 윈도우 창과 묶여있는 함수
	static LRESULT CALLBACK WndProc(HWND handle,
		UINT message, WPARAM wParam, LPARAM lParam);
	// handle : 윈도우 창을 실제로 들고 있는 것, 여러 윈도우 창에서 각각의 윈도우 창을 구분짓는 고유 번호/값
	// CALLBACK : 처리할 것(메시지) 가 있다면 따로 호출하지 않아도 자동적으로 호출된다.
	// WPARAM : Word Parameter  예전에는 16bit
	// LPARAM : Long Parameter	예전에는 32bit
	// 메시지에 엮여있는 정보들이 들어온다.
	// ex) 마우스를 움직였다는 메시지가호출될때 LPARAM에 마우스 위치정보가 들어온다. (하위 16bit : x좌표, 상위 16bit : y좌표)

	WinDesc desc;

	static class Program* program;

	static bool isWindowCreated;
};