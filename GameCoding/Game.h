#pragma once
class Game
{
public:
	Game();
	~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

private:
	HWND _hwnd = {};
	HDC _hdc = {};

private:
	// Double Buffering
	RECT _rect;
	HDC _hdcBack = {}; // 백버퍼
	HBITMAP _bmpBack = {}; // 프런트버퍼. 백버퍼에서 그린걸 화면에 나타낸다.
};

