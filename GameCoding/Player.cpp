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
	// TODO : ��ȹ�ڰ� �����ϴ� Data sheet �� ������ ���̴�
	_stat.hp = 100;
	_stat.maxHp = 100;
	_stat.speed = 500;

	_pos.x = 400;
	_pos.y = 500;
}

void Player::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	// �Ÿ� = �ð� * �ӵ�


	// �Է�

	if (_playerTurn == false)
		return; // �� ���� �ƴϸ� ����

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
		// TODO: �̻��� �߻�
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
			mesh->Render(hdc, _pos, 0.5f, 0.5f); // ���� ���� ���� // �������� ������ �¿������ �ȴ�

	}
	else
	{
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());

		if (mesh)
			mesh->Render(hdc, _pos, -0.5f, 0.5f); // ���� ���� ���� // �������� ������ �¿������ ��ek
	}

	if (_playerTurn) // �� ���ʰ� �Դٸ�.. ��� ���� �Ӹ� ���� �׷��ֱ�
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
	
	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // ������
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
	if (_playerType == PlayerType::MissileTank) // ���� ��� PRG ���ӿ��� �������� �ٸ� �� ������ ��~
		return L"MissileTank";

	return L"CanonTank";
}