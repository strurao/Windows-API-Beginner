#include "pch.h"
#include "TimeManager.h"

void TimeManager::Init()
{
	// ::GetTickCount64(); // 현재 ms 측정. 그러나 정밀도가 조금 떨어진다

	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(& _frequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount)); // CPU 클럭
}

void TimeManager::Update()
{
	uint64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount)); // CPU 클럭
	//currentCount 변수의 주소를 LARGE_INTEGER 포인터로 캐스팅

	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount;

	_frameCount++;
	_frameTime += _deltaTime;

	if (_frameTime >= 1.f)
	{
		_fps = static_cast<uint32>(_frameCount / _frameTime);
		_frameTime = 0.f;
		_frameCount = 0;
	}
}