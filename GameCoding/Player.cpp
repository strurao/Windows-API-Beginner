#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "Missile.h"
#include "ResourceManager.h"
#include "LineMesh.h"

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

	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		_pos.x -= _stat.speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		_pos.x += _stat.speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		_pos.y -= _stat.speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		_pos.y += _stat.speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::Q))
	{
		_barrelAngle += 10 * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::E))
	{
		_barrelAngle -= 10 * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		// TODO: 미사일 발사
		Missile* missile = GET_SINGLE(ObjectManager)->CreateObject<Missile>();
		missile->SetPos(GetFirePos());
		missile->SetAngle(_barrelAngle);
		GET_SINGLE(ObjectManager)->Add(missile);
	}
}

void Player::Render(HDC hdc)
{
	// Utils::DrawCircle(hdc, _pos, 50);
	const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(L"Player");

	if (mesh)
		mesh->Render(hdc, _pos);

	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // 빨간펜
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);

	Utils::DrawLine(hdc, _pos, GetFirePos());

	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);
}

Pos Player::GetFirePos()
{
	Pos firePos = _pos;
	firePos.x += _barrelLength * cos(_barrelAngle);
	firePos.y -= _barrelLength * sin(_barrelAngle);
	return firePos;
}
