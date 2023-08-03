#include "pch.h"
#include "FortressScene.h"
#include "UIManager.h"
#include "Player.h"
#include "UIManager.h"
#include "LineMesh.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "TimeManager.h"

FortressScene::FortressScene() 
{

}

FortressScene::~FortressScene()
{

}

void FortressScene::Init()
{
	GET_SINGLE(UIManager)->Init();

	{
		// 첫 번째 플레이어
		Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
		player->SetPlayerType(PlayerType::MissileTank); // RPG 게임의 직업군이 이 예시이다
		player->SetPlayerId(0);
		player->SetPlayerTurn(true);

		GET_SINGLE(ObjectManager)->Add(player);

		player->SetPos(Vector{ 100,400 });
	}

	{
		// 두 번째 플레이어
		Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
		player->SetPlayerType(PlayerType::CanonTank); // RPG 게임의 직업군이 이 예시이다

		GET_SINGLE(ObjectManager)->Add(player);

		player->SetPos(Vector{ 700,400 });
	}
}

void FortressScene::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects)
		object->Update();

}

void FortressScene::Render(HDC hdc)
{
	GET_SINGLE(UIManager)->Render(hdc);

	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects)
		object->Render(hdc);
}