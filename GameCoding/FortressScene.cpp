#include "pch.h"
#include "FortressScene.h"
#include "UIManager.h"

FortressScene::FortressScene() 
{

}

FortressScene::~FortressScene()
{

}

void FortressScene::Init()
{
	GET_SINGLE(UIManager)->Init();
}

void FortressScene::Update()
{

}

void FortressScene::Render(HDC hdc)
{
	GET_SINGLE(UIManager)->Render(hdc);
}