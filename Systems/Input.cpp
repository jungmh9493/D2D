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

void Input::Update() // 프레임 단위로 업데이트
{
	memcpy(keyOldState, keyState, sizeof(keyOldState));
	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyMap, sizeof(keyMap));

	if (GetKeyboardState(keyState)) // 현재 프레임의 키 상태 = keyState
	{
		for (DWORD i = 0; i < MAX_INPUT_KEY; ++i)
		{
			/*
			* 가상 키는 마우스 클릭까지 포함한다.
			* 하나의 키에 대해서 아래의 상태가 나온다.
			* 0x00 : 이전에 누른적이 없고, 호출시점에도 눌려있지 않은 상태 NONE
			* 0x01 : 이전에 누른적이 있고, 호출시점에는 눌려있지 않은 상태 UP
			* 0x80 : 이전에 누른적이 없고, 호출시점에는 눌린상태		   DOWN
			* 0x81 : 이전에 누른적이 있고, 호출시점에도 눌려있는 상태	   PRESS
			*
			* 현재 우리에게는 호출시점만이 정확한 정보이다.
			* 호출 시점에 해당 키가 눌려있는 상태인지 체크 => keyState[i] & 0x80 ? 1 : 0
			*/
			keyState[i] = keyState[i] & 0x80 ? 1 : 0;

			unsigned char& oldState = keyOldState[i];
			unsigned char& state = keyState[i];

			if (oldState == 0 && state == 1)		// 이전 프레임엔 안 눌렸고, 현재 프레임에 눌렸다
				keyMap[i] = KEY_INPUT_STATUS_DOWN;	// key down
			else if (oldState == 1 && state == 0)	// 이전 프레임엔 눌렸고, 현재 프레임엔 안 눌렸다
				keyMap[i] = KEY_INPUT_STATUS_UP;	// key up
			else if (oldState == 1 && state == 1)	// 이전 프레임에 눌렸고, 현재 프래임에도 눌려있다.
				keyMap[i] = KEY_INPUT_STATUS_PRESS;	// key press
			else									// 아무것도 해당 되지 않는다.
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
