#include "stdafx.h"
#include "Input.h"

Input* Input::instance = nullptr;

Input::Input()
{
	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyOldState, sizeof(keyOldState));
	ZeroMemory(keyMap, sizeof(keyMap));
}

Input::~Input() {}

void Input::Update() // ������ ������ ������Ʈ
{
	memcpy(keyOldState, keyState, sizeof(keyOldState));
	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyMap, sizeof(keyMap));

	if (GetKeyboardState(keyState)) // ���� �������� Ű ���� = keyState
	{
		for (DWORD i = 0; i < MAX_INPUT_KEY; ++i)
		{
			/*
			* ���� Ű�� ���콺 Ŭ������ �����Ѵ�.
			* �ϳ��� Ű�� ���ؼ� �Ʒ��� ���°� ���´�.
			* 0x00 : ������ �������� ����, ȣ��������� �������� ���� ���� NONE
			* 0x01 : ������ �������� �ְ�, ȣ��������� �������� ���� ���� UP
			* 0x80 : ������ �������� ����, ȣ��������� ��������		   DOWN
			* 0x81 : ������ �������� �ְ�, ȣ��������� �����ִ� ����	   PRESS
			*
			* ���� �츮���Դ� ȣ��������� ��Ȯ�� �����̴�.
			* ȣ�� ������ �ش� Ű�� �����ִ� �������� üũ => keyState[i] & 0x80 ? 1 : 0
			*/
			keyState[i] = keyState[i] & 0x80 ? 1 : 0;

			unsigned char& oldState = keyOldState[i];
			unsigned char& state = keyState[i];

			if (oldState == 0 && state == 1)		// ���� �����ӿ� �� ���Ȱ�, ���� �����ӿ� ���ȴ�
				keyMap[i] = KEY_INPUT_STATUS_DOWN;	// key down
			else if (oldState == 1 && state == 0)	// ���� �����ӿ� ���Ȱ�, ���� �����ӿ� �� ���ȴ�
				keyMap[i] = KEY_INPUT_STATUS_UP;	// key up
			else if (oldState == 1 && state == 1)	// ���� �����ӿ� ���Ȱ�, ���� �����ӿ��� �����ִ�.
				keyMap[i] = KEY_INPUT_STATUS_PRESS;	// key press
			else									// �ƹ��͵� �ش� ���� �ʴ´�.
				keyMap[i] = KEY_INPUT_STATUS_NONE;	// key none
		}
	}
}

void Input::InputProc(UINT message, LPARAM lParam)
{
	if (message == WM_MOUSEMOVE || message == WM_LBUTTONDOWN || message == WM_LBUTTONDBLCLK)
	{
		mousePosition.x = (float)GET_X_LPARAM(lParam);
		mousePosition.y = (float)GET_Y_LPARAM(lParam);
	}

	if (message == WM_LBUTTONDBLCLK)
		isDblClk = true;
	else
		isDblClk = false;
}
