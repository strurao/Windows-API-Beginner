#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "ResourceManager.h"
#include "LineMesh.h"
// #include "Missile.h"

Player::Player() : Object(ObjectType::Player)
{

}

Player::~Player()
{

}

void Player::Init()
{
	// TODO : 기획자가 관리하는 Data sheet 에 들어가있을 것이다
	_stat.hp = 100;
	_stat.maxHp = 100;
	_stat.speed = 500;

	_pos.x = 400;
	_pos.y = 500;
}

void Player::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	// 거리 = 시간 * 속도


	// 입력

	if (_playerTurn == false)
		return; // 내 턴이 아니면 종료

	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		_pos.x -= _stat.speed * deltaTime;
		_dir = Dir::Left;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		_pos.x += _stat.speed * deltaTime;
		_dir = Dir::Right;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		// _pos.y -= _stat.speed * deltaTime;
		// Fortress
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		// _pos.y += _stat.speed * deltaTime;
		// Fortress
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::Q))
	{
		// _barrelAngle += 10 * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::E))
	{
		// _barrelAngle -= 10 * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		// TODO: 미사일 발사
		/*
		Missile* missile = GET_SINGLE(ObjectManager)->CreateObject<Missile>();
		missile->SetPos(GetFirePos());
		missile->SetAngle(_barrelAngle);
		GET_SINGLE(ObjectManager)->Add(missile);
		*/
	}
}

void Player::Render(HDC hdc)
{
	if (_dir == Dir::Left)
	{
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());

		if (mesh)
			mesh->Render(hdc, _pos, 0.5f, 0.5f); // 비율 적용 가능 // 음수값을 넣으면 좌우반전이 된다

	}
	else
	{
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());

		if (mesh)
			mesh->Render(hdc, _pos, -0.5f, 0.5f); // 비율 적용 가능 // 음수값을 넣으면 좌우반전이 된ek
	}

	if (_playerTurn) // 내 차례가 왔다면.. 노란 공을 머리 위에 그려주기
	{
		RECT rect;
		rect.bottom = static_cast<LONG>(_pos.y - 60);
		rect.left = static_cast<LONG>(_pos.x - 10);
		rect.right = static_cast<LONG>(_pos.x + 10);
		rect.top = static_cast<LONG>(_pos.y - 80);

		HBRUSH brush = ::CreateSolidBrush(RGB(250, 236, 197));
		HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, brush);

		::Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);

		::SelectObject(hdc, oldBrush);
		::DeleteObject(brush);
	}

	// Utils::DrawCircle(hdc, _pos, 50);
	
	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // 빨간펜
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);

	// Utils::DrawLine(hdc, _pos, GetFirePos());

	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);
}

/*
Pos Player::GetFirePos()
{
	Pos firePos = _pos;
	firePos.x += _barrelLength * cos(_barrelAngle);
	firePos.y -= _barrelLength * sin(_barrelAngle);
	return firePos;
}
*/

// Fortress
wstring Player::GetMeshKey()
{
	if (_playerType == PlayerType::MissileTank) // 예를 들어 PRG 게임에서 직업별로 다른 걸 구현할 때~
		return L"MissileTank";

	return L"CanonTank";
}