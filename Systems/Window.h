#pragma once

struct WinDesc		// description : ���������� ���� / �뵵�� ��Ƴ��� ��
{
	wstring appName = L"";	// Application Name
	HINSTANCE instance = nullptr;	// instance : handle�� ���� ��ȣ�� ���� �����ּҸ� ��� �ִ� ��
	HWND handle = nullptr;
	float width = 0.0f;			// �ʺ�
	float height = 0.0f;		// ����
};

class Window
{
public:
	Window(const WinDesc& initDesc);
	~Window();

	ATOM MyRegisterClass(const WinDesc& desc);		// ATOM -> WORD -> unsigned short
	// Window Ŭ������ ����ϴ� ���� -> ��ϵ� Window Ŭ������ ���� ������ â ���� -> â ������ �����Ҷ����� Run(����)

	WPARAM Run();

private:
	// �޽��� ó�� �Լ� : ������ â ������ �޽����� ȣ��Ǹ� �ڵ������� ȣ��Ǵ� �Լ�
	// ������ â�� �����ִ� �Լ�
	static LRESULT CALLBACK WndProc(HWND handle,
		UINT message, WPARAM wParam, LPARAM lParam);
	// handle : ������ â�� ������ ��� �ִ� ��, ���� ������ â���� ������ ������ â�� �������� ���� ��ȣ/��
	// CALLBACK : ó���� ��(�޽���) �� �ִٸ� ���� ȣ������ �ʾƵ� �ڵ������� ȣ��ȴ�.
	// WPARAM : Word Parameter  �������� 16bit
	// LPARAM : Long Parameter	�������� 32bit
	// �޽����� �����ִ� �������� ���´�.
	// ex) ���콺�� �������ٴ� �޽�����ȣ��ɶ� LPARAM�� ���콺 ��ġ������ ���´�. (���� 16bit : x��ǥ, ���� 16bit : y��ǥ)

	WinDesc desc;

	static class Program* program;

	static bool isWindowCreated;
};