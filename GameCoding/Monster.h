#pragma once
#include "Object.h"
class Monster : public Object
{
public:
	Monster();
	virtual ~Monster() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	// Vector _start = { 300, 100 };
	// Vector _end = { 600, 250 };
	// Vector _pt1 = { 400, 150 };
	// Vector _pt2 = { 600, 450 };
	// Vector _pt3 = { 200, 450 };
	
	//���Ͱ� �ٶ󺸴� ����
	Vector _lookPos = {};
	Vector _lookDir = {};
};

