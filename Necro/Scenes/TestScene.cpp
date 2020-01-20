#include "stdafx.h"
#include "TestScene.h"
#include "./GameObject/UI/Coin.h"
#include "./GameObject/UI/Diamond.h"
#include "./GameObject/UI/AttackSlot.h"
#include "./GameObject/UI/ShovelSlot.h"
#include "./GameObject/UI/TorchSlot.h"
#include "./GameObject/UI/BodySlot.h"	
#include "./GameObject/UI/HeadSlot.h"
#include "./GameObject/UI/ItemSlot.h"
#include "./GameObject/UI/BoomSlot.h"
#include "./GameObject/UI/ThrowSlot.h"
#include "./GameObject/TestPlayer.h"
#include "./GameObject/UI/Note.h"
#include "./GameObject/UI/Heart.h"


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
