#pragma once
#include "Object.h"
class Missile : public Object
{
public:
	Missile();
	virtual ~Missile() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetAngle(float angle) { _angle = angle; }

protected:
	float _angle = 0.f;

	float _sumTime = 0.f;
	Object* _target = nullptr;

	// Object* _target; // 괜찮을..까?
	/*
	이렇게 타겟을 포인터로 해줬을 때 오류가 생길 수 있다
	int32 로 id 를 만들거나 shared_ptr 로 해주는 방법이 있다.
	*/ 
};

