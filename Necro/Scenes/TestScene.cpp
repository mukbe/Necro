#include "stdafx.h"
#include "TestScene.h"
#include "./GameObject/UIBase.h"

TestScene::TestScene()
	:SceneBase()
{
}


TestScene::~TestScene()
{
}

void TestScene::Init()
{
	SceneBase::Init();

	UIBase* temp = _ObjectPool->CreateObject<UIBase>("UI", D3DXVECTOR2(0, 0), D3DXVECTOR2(30, 100));
	UIBase* t = _ObjectPool->FindObject<UIBase>("UI");

	

}


void TestScene::PreUpdate()
{
	if (beatManager->Update(Time::Tick()))
	{
		SceneBase::PreUpdate();
	}
}
