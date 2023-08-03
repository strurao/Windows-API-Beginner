#pragma once
#include "Object.h"

class Bullet : public Object
{
public:
	Bullet();
	virtual ~Bullet() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

public:
	Vector GetSpeed() { return _speed; }
	void SetSpeed(Vector speed) { _speed = speed; }

	Object* GetOwner() { return _owner; }
	void SetOwner(Object* owner) { _owner = owner; }

public:
	Vector _speed = {};
	Object* _owner = nullptr;
};

