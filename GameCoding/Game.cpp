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
	// ��� �������� �־�� �ǹ̰� �ִ�.. �̰� ���÷� �־��!
	GET_SINGLE(SceneManager)->Clear();
	GET_SINGLE(ResourceManager)->Clear();

	_CrtDumpMemoryLeaks();
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd; // ������ ��ȣ
	_hdc = ::GetDC(hwnd); // ��ȭ���� ��ȣ

	::GetClientRect(hwnd, &_rect);

	// �Ǵٸ� ��ȭ���� �����. �ӽ������� ó�������� ��Ʈ���� ���� �������ش�.
	_hdcBack = ::CreateCompatibleDC(_hdc); // _hdc �� ȣȯ�Ǵ� DC�� ����
	_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom); // _hdc �� ȣȯ�Ǵ� ��Ʈ�� ����
	HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _bmpBack); // DC �� BP�� ����
	::DeleteObject(prev); // ������ ����ϴ� ���� ����

	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(SceneManager)->Init();
	GET_SINGLE(ResourceManager)->Init();

	GET_SINGLE(SceneManager)->ChangeScene(SceneType::GameScene);
}

void Game::Update()
{
	GET_SINGLE(TimeManager)->Update(); // ������ ������ ���ؼ� ���� �ð� ���
	GET_SINGLE(InputManager)->Update(); // �� �����Ӹ��� ���� Ű���峪 ���콺 ���¸� ��� ����
	GET_SINGLE(SceneManager)->Update(); // �� �����Ӹ��� ���� ������Ʈ
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
	// �ܻ��� ����Ⱑ ��ƴ� �׷��� '������۸�'�̶�� ������ Ȱ���Ѵ�

	// Double Buffering
	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY); // ��Ʈ�� �Լ� : ��� ����
	::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS); // ��ȭ���� �������ֱ�
}