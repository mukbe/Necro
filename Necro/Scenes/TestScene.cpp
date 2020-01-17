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
	// 하트 템포
	//UIBase* Heart = _ObjectPool->CreateObject<UIBase>("UI", D3DXVECTOR2(WinSizeX / 2, 830), D3DXVECTOR2(150, 150));
	UIBase* temp = _ObjectPool->CreateObject<UIBase>("UI", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	UIBase* t = _ObjectPool->FindObject<UIBase>("UI");
	
	

}


void TestScene::PreUpdate()
{
	if (beatManager->Update(Time::Tick()))
	{
		SceneBase::PreUpdate();
	}
}
