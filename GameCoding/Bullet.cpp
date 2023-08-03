#include "pch.h"
#include "Bullet.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "FortressScene.h"
#include "UIManager.h"

Bullet::Bullet() : Object(ObjectType::Projectile)
{

}

Bullet::~Bullet()
{

}

void Bullet::Init()
{
	_radius = 20.f;
}

void Bullet::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// Wind ...���� ����
	float windPercent = GET_SINGLE(UIManager)->GetWindPercent();
	_speed.x += 10 * deltaTime * windPercent;

	//Gravity ...���� ����
	/*
	���ӵ� = �ӵ� ��ȭ / �ð�
	�� ������ �ð� ���� �ӵ��� �󸶳� ���ߴ���?�� ���ӵ��̴�.
	���ӵ��� ���� ����ϰ�, ��κ��� ���ӿ��� 9.8G ��� �߷��� �����Ѵ�.
	*/
	Vector g{ 0, +1000};
	_speed += g * deltaTime;
	// _speed.y += 1000 * deltaTime;

	// �̵�
	_pos += _speed * deltaTime;
	
	// �浹
	const vector<Object*>& objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects)
	{
		if (object->GetObjectType() != ObjectType::Player)
			continue;

		if (object == _owner)
			continue;

		Vector dir = _pos - object->GetPos();
		if (dir.Length() < _radius + object->GetRadius())
		{
			FortressScene* scene = dynamic_cast<FortressScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
			if (scene)
				scene->ChangePlayerTurn();

			GET_SINGLE(ObjectManager)->Remove(this);
			return;
		}
	}
	
	// �Ҹ� ...���������� ������� �ȵǴ�
	if (_pos.y > GWinSizeY * 1.5 || _pos.y < -GWinSizeY * 1.5)
	{
		FortressScene* scene = dynamic_cast<FortressScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		if (scene)
			scene->ChangePlayerTurn();

		GET_SINGLE(ObjectManager)->Remove(this);
		return;
	}
}

void Bullet::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, static_cast<int32>(_radius));
}
