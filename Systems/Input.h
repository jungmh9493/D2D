#pragma once

#define MAX_INPUT_KEY 256

class Input
{
	DECLARE_SINGLETON(Input);

public:
	void Update();

	void InputProc(UINT message, LPARAM lParam);

	bool Down(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_DOWN; }
	bool Up(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_UP; }
	bool Press(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_PRESS; }
	bool DblClk(DWORD key) { return isDblClk; }

	Vector2 GetMousePosition() { return mousePosition; }

private:
	Vector2 mousePosition;	// ���콺�� ��ǥ����

	// 256���� ���� Ű ���¸� ����
	unsigned char keyState[MAX_INPUT_KEY] = { 0 };
	unsigned char keyOldState[MAX_INPUT_KEY] = { 0 };
	unsigned char keyMap[MAX_INPUT_KEY] = { 0 };

	bool isDblClk = false;

	// Ŭ���� �������� ���� ������
	enum
	{
		KEY_INPUT_STATUS_NONE = 0,
		KEY_INPUT_STATUS_DOWN,
		KEY_INPUT_STATUS_UP,
		KEY_INPUT_STATUS_PRESS,
	};
};