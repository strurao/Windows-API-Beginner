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

protected:
	// Object* _target; 
	/*
	�̷��� Ÿ���� �����ͷ� ������ �� ������ ���� �� �ִ�
	int32 �� id �� ����ų� shared_ptr �� ���ִ� ����� �ִ�.
	*/ 
};

