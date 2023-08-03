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

	// Wind ...가로 벡터
	float windPercent = GET_SINGLE(UIManager)->GetWindPercent();
	_speed.x += 10 * deltaTime * windPercent;

	//Gravity ...세로 벡터
	/*
	가속도 = 속도 변화 / 시간
	즉 일정한 시간 동안 속도가 얼마나 변했느냐?가 가속도이다.
	가속도는 힘에 비례하고, 대부분의 게임에는 9.8G 라는 중력이 존재한다.
	*/
	Vector g{ 0, +1000};
	_speed += g * deltaTime;
	// _speed.y += 1000 * deltaTime;

	// 이동
	_pos += _speed * deltaTime;
	
	// 충돌
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
	
	// 소멸 ...무한정으로 뻗어나가면 안되니
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
