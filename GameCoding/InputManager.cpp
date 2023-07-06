#include "pch.h"
#include "InputManager.h"

void InputManager::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_states.resize(KEY_TYPE_COUNT, KeyState::None); // 256
}

void InputManager::Update()
{
	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
	
	// ::GetAsyncKeyState() // ���� Ű�� �����ִ��� üũ�ϴ� ���̳�, �� �����Ӹ��� �Ϸ��� �� ������
	if (GetKeyboardState(asciiKeys) == false) // Ű���� 256���� ���¸� ������ �ϳ��� �ܾ�ͼ� �����ϰ� �ʿ信 ���� üũ�ϱ�
		return;

	for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
	{
		// Ű�� ���������� true
		if (asciiKeys[key] & 0x80)
		{
			KeyState& state = _states[key];

			// ���� �����ӿ� Ű�� ���� ���¶�� PRESS
			if (state == KeyState::Press || state == KeyState::Down)
				state = KeyState::Press;
			else
				state = KeyState::Down;
		}
		// Ű���忡�� ���� ��������
		else
		{
			KeyState& state = _states[key];

			// ���� �����ӿ� Ű�� ���� ���¶�� UP
			if (state == KeyState::Press || state == KeyState::Down)
				state = KeyState::Up;
			else
				state = KeyState::Down;
		}
	}

	//Mouse
	::GetCursorPos(&_mousePos); // Ŀ���� ��ǥ�� �˾ƿ´�
	::ScreenToClient(_hwnd, &_mousePos); // â ���� ���콺 ����Ʈ
	//?
}