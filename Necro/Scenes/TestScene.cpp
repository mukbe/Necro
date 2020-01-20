#include "stdafx.h"
#include "TestScene.h"
#include "./GameObject/Note.h"
#include "./GameObject/TestPlayer.h"
#include "./GameObject/Heart.h"

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
	beatManager->LoadText(ResourcePath + L"zone.txt");

	Note* temp = _ObjectPool->CreateObject<Note>("Note", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	Note* t = _ObjectPool->FindObject<Note>("Note");
	_ObjectPool->CreateObject<TestPlayer>("Player", D3DXVECTOR2(200, 200), D3DXVECTOR2(100, 100));
	_ObjectPool->CreateObject<Heart>("Heart", { WinSizeX / 2.f , 830.f }, { 130.f,140.f });

}


void TestScene::PreUpdate()
{
	//if (beatManager->Update(Time::Tick()))
	//{
	//	SceneBase::PreUpdate();
	//}
}
