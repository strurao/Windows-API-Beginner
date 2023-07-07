#include "pch.h"
#include "DevScene.h"
#include "Utils.h"
#include "InputManager.h"
#include "TimeManager.h"

DevScene::DevScene()
{

}

DevScene::~DevScene()
{

}

void DevScene::Init()
{

}

void DevScene::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	// �Ÿ� = �ð� * �ӵ�

	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		_playerPos.x -= _speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		_playerPos.x += _speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		_playerPos.y -= _speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		_playerPos.y += _speed * deltaTime;
	}
}

void DevScene::Render(HDC hdc)
{
	// ::Rectangle(hdc, 200, 200, 400, 400);
	Utils::DrawCircle(hdc, _playerPos, 50);
}