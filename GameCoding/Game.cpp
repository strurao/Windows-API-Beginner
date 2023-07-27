#include "pch.h"
#include "Game.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"

Game::Game()
{

}

Game::~Game()
{
	// 사실 마지막에 넣어야 의미가 있다.. 이건 예시로 넣어본다!
	GET_SINGLE(SceneManager)->Clear();
	GET_SINGLE(ResourceManager)->Clear();

	_CrtDumpMemoryLeaks();
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd; // 윈도우 번호
	_hdc = ::GetDC(hwnd); // 도화지의 번호

	::GetClientRect(hwnd, &_rect);

	// 또다른 도화지를 만든다. 임시적으로 처리가능한 비트맵을 만들어서 연결해준다.
	_hdcBack = ::CreateCompatibleDC(_hdc); // _hdc 와 호환되는 DC를 생성
	_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom); // _hdc 와 호환되는 비트맵 생성
	HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _bmpBack); // DC 와 BP를 연결
	::DeleteObject(prev); // 예전에 사용하던 것은 삭제

	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(SceneManager)->Init();
	GET_SINGLE(ResourceManager)->Init();

	GET_SINGLE(SceneManager)->ChangeScene(SceneType::GameScene);
}

void Game::Update()
{
	GET_SINGLE(TimeManager)->Update(); // 프레임 관리를 위해서 현재 시간 계산
	GET_SINGLE(InputManager)->Update(); // 매 프레임마다 현재 키보드나 마우스 상태를 모두 저장
	GET_SINGLE(SceneManager)->Update(); // 매 프레임마다 씬을 업데이트
}

void Game::Render()
{
	uint32 fps = GET_SINGLE(TimeManager)->GetFps();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		::TextOut(_hdcBack, 20, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	{
		wstring str = std::format(L"FPS({0}), DT({1} ms)", fps, static_cast<int32>(deltaTime * 1000));
		::TextOut(_hdcBack, 650, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	GET_SINGLE(SceneManager)->Render(_hdcBack);

	// Utils::DrawRect(_hdc, Pos{ 400, 300 }, 1000, 1000);
	// 잔상을 지우기가 어렵다 그래서 '더블버퍼링'이라는 개념을 활용한다

	// Double Buffering
	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY); // 비트블릿 함수 : 고속 복사
	::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS); // 도화지를 리셋해주기
}