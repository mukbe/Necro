#include "stdafx.h"
#include "TestScene.h"
#include "./GameObject/UIBase.h"
#include "./GameObject/Heart.h"
#include "./GameObject/Coin.h"
#include "./GameObject/Diamond.h"
#include "./GameObject/AttackSlot.h"
#include "./GameObject/ShovelSlot.h"
#include "./GameObject/TorchSlot.h"
#include "./GameObject/BodySlot.h"	
#include "./GameObject/HeadSlot.h"
#include "./GameObject/ItemSlot.h"
#include "./GameObject/BoomSlot.h"
#include "./GameObject/ThrowSlot.h"
#include "./GameObject/TestPlayer.h"
#include "./GameObject/Note.h"


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

	_ObjectPool->CreateObject<Note>("Note", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	_ObjectPool->CreateObject<Note>("Note", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	_ObjectPool->CreateObject<Note>("Note", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	_ObjectPool->CreateObject<Note>("Note", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));



	_ObjectPool->CreateObject<TestPlayer>("Player", D3DXVECTOR2(200, 200), D3DXVECTOR2(100, 100));
	_ObjectPool->CreateObject<Heart>("Heart", { WinSizeX / 2.f , 830.f }, { 130.f,140.f });

	_ObjectPool->CreateObject<Coin>("UI_Coin", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	_ObjectPool->CreateObject<Diamond>("UI_Diamond", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	_ObjectPool->CreateObject<AttackSlot>("UI_AttackSlot", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	_ObjectPool->CreateObject<ShovelSlot>("UI_ShovelSlot", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	_ObjectPool->CreateObject<TorchSlot>("UI_TorchSlot", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	_ObjectPool->CreateObject<BodySlot>("UI_BodySlot", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	_ObjectPool->CreateObject<HeadSlot>("UI_HeadSlot", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	_ObjectPool->CreateObject<ItemSlot>("UI_ItemSlot", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	_ObjectPool->CreateObject<BoomSlot>("UI_BoomSlot", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	_ObjectPool->CreateObject<ThrowSlot>("UI_ThrowSlot", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));

	beatManager->LoadText(ResourcePath + L"zone.txt");
}


void TestScene::ControlUpdate()
{
	//if (beatManager->Update(Time::Tick()))
	//{
	//	SceneBase::ControlUpdate();
	//}
}
