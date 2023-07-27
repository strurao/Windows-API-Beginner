#include "pch.h"
#include "Missile.h"
#include "TimeManager.h"
#include "ObjectManager.h"

Missile::Missile() : Object(ObjectType::Projectile)
{

}

Missile::~Missile()
{

}

void Missile::Init()
{
	_stat.hp = 1;
	_stat.maxHp = 1;
	_stat.speed = 600;
}

void Missile::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 유도탄
	if (_target == nullptr)
	{
		// scalar 값으로 하나하나 구해준 방식
		_pos.x += _stat.speed * deltaTime * ::cos(_angle);
		_pos.y -= _stat.speed * deltaTime * ::sin(_angle);

		_sumTime += deltaTime;
		if (_sumTime >= 0.2f)
		{
			// 내 주변의 몬스터들 목록
			const vector<Object*>& objects = GET_SINGLE(ObjectManager)->GetObjects();
			for (Object* object : objects)
			{
				if (object->GetObjectType() == ObjectType::Monster)
				{
					_target = object; // 위험한 방식
					break;
				}
			}
		}
	}
	else 
	{
		// vector 로 방향, 값을 한번에 구해준 방식
		Vector dir = _target->GetPos() - GetPos(); // 괜찮을..까?
		dir.Normalize();

		Vector moveDir = dir * _stat.speed * deltaTime;
		_pos += moveDir;
	}

	// 충돌
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects)
	{
		if (object == this)
			continue;

		if (object->GetObjectType() != ObjectType::Monster)
			continue;

		Vector p1 = GetPos();
		Vector p2 = object->GetPos();

		Vector dir = p2 - p1;
		float dist = dir.Length();
		/*
		const float dx = p1.x - p2.x;
		const float dy = p1.y - p2.y;
		float dist = sqrt(dx * dx + dy * dy);
		*/

		if (dist < 25)
		{
			GET_SINGLE(ObjectManager)->Remove(object); // 괜찮을..까?
			GET_SINGLE(ObjectManager)->Remove(this); // 괜찮을..까?
			return;
		}

	}

	// TODO
	if (_pos.y < -200)
	{
		GET_SINGLE(ObjectManager)->Remove(this);
		return;
	}
}

void Missile::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, 25);
}