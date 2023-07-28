#include "pch.h"
#include "Monster.h"
#include "InputManager.h"

Monster::Monster() : Object(ObjectType::Monster)
{

}

Monster::~Monster()
{

}

void Monster::Init()
{
	_stat.hp = 100;
	_stat.maxHp = 100;
	_stat.speed = 10;
}

void Monster::Update()
{
	/* 내적

	Vector mousePos = GET_SINGLE(InputManager)->GetMousePos();

	// start -> end
	Vector v1 = _end - _start;

	// start -> mousePos
	Vector v2 = mousePos - _start;

	// 내각의 투영(projection) 에 대해 설명할 수 있는지 ??
	float maxLength = v1.Length();
	v1.Normalize();
	float dot = v1.Dot(v2);
	Pos pos = _start + v1 * dot;
	if (dot < 0 || dot > maxLength) return;
	_pos = pos;
	*/


}

void Monster::Render(HDC hdc)
{
	Vector mousePos = GET_SINGLE(InputManager)->GetMousePos();


	// Utils::DrawCircle(hdc, _pos, 50);

	// 경계선
	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);
	{
		// Utils::DrawLine(hdc, _start, _end); // 내적 예시용
		Utils::DrawLine(hdc, _pt1, _pt2); // 외적 예시용
		Utils::DrawLine(hdc, _pt2, _pt3); // 외적 예시용
		Utils::DrawLine(hdc, _pt3, _pt1); // 외적 예시용

	}
	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);

	//////
	Utils::DrawLine(hdc, _pt1, mousePos); // 외적 예시용 - 마우스 위치용

	Vector v12 = _pt2 - _pt1;
	Vector v1m = mousePos - _pt1;
	Vector v13 = _pt3 - _pt1;

	v12.Normalize();
	v1m.Normalize();
	v13.Normalize();

	float c1 = v12.Cross(v1m);
	float c2 = v1m.Cross(v13);

	if (c1 >= 0 && c2 >= 0)
	{
		// 마우스 위치가 삼각형 안에 있는 경우
	}
	else
	{
		// 마우스 위치가 삼각형에서 벗어난 경우
	}

	wstring str = std::format(L"c1({0}), c2({1})", c1, c2);
	Utils::DrawTextW(hdc, { 20, 50 }, str);
}