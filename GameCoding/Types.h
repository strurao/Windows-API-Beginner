#pragma once
#include <cmath>
#include <Windows.h>

using int8		= __int8;
using int16		= __int16;
using int32		= __int32;
using int64		= __int64;
using uint8		= unsigned __int8;
using uint16	= unsigned __int16;
using uint32	= unsigned __int32;
using uint64	= unsigned __int64;

struct Stat
{
	int32 hp = 0;
	int32 maxHp = 0;
	float speed = 0;
};

struct Vector
{
	Vector() {}
	Vector(float x, float y) : x(x), y(y) {} 
	Vector(POINT pt) : x((float)pt.x), y((float)pt.y) {}

	Vector operator+(const Vector& other)
	{
		Vector ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		return ret;
	}

	Vector operator-(const Vector& other)
	{
		Vector ret;
		ret.x = x - other.x;
		ret.y = y - other.y;
		return ret;
	}

	Vector operator*(float value)
	{
		Vector ret;
		ret.x = x * value;
		ret.y = y * value;
		return ret;
	}

	void operator+=(const Vector& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(const Vector& other)
	{
		x -= other.x;
		y -= other.y;
	}

	void operator*=(float value)
	{
		x *= value;
		y *= value;
	}

	float LengthSquared()
	{
		return x * x + y * y;
	}

	// Magnitude 벡터의 크기
	float Length()
	{
		return ::sqrt(LengthSquared());
	}

	// Normalize 단위벡터 (정규화)
	void Normalize()
	{
		float length = Length();
		if (length < 0.00000f) return;

		x /= length;
		y /= length;
	}

	// Dot_product 내적 
	float Dot(Vector other)
	{
		return x * other.x + y * other.y;
	}

	// Cross_product 외적
	float Cross(Vector other)
	{
		// 일단 우리가 임의로 한 쪽 방향으로 정해주면 반대 방향이 음수로 나올 것.
		return x * other.y - y * other.x; // vector k
	}

	float x = 0;
	float y = 0;
};

using Pos = Vector;
/*
struct Pos
{
	float x = 0;
	float y = 0;
};
*/