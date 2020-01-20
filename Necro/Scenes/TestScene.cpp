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
	UIBase* temp = _ObjectPool->CreateObject<Heart>("UI_Heart", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	UIBase* coin = _ObjectPool->CreateObject<Coin>("UI_Coin", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	UIBase* Dia = _ObjectPool->CreateObject<Diamond>("UI_Diamond", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	UIBase* Attackslot = _ObjectPool->CreateObject<AttackSlot>("UI_AttackSlot", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	UIBase* shovelSlot = _ObjectPool->CreateObject<ShovelSlot>("UI_ShovelSlot", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	UIBase* Torchslot = _ObjectPool->CreateObject<TorchSlot>("UI_TorchSlot", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	UIBase* Bodyslot = _ObjectPool->CreateObject<BodySlot>("UI_BodySlot", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	UIBase* Headslot = _ObjectPool->CreateObject<HeadSlot>("UI_HeadSlot", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	UIBase* Itemslot = _ObjectPool->CreateObject<ItemSlot>("UI_ItemSlot", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	UIBase* Boomslot = _ObjectPool->CreateObject<BoomSlot>("UI_BoomSlot", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
	UIBase* Throwslot = _ObjectPool->CreateObject<ThrowSlot>("UI_ThrowSlot", D3DXVECTOR2(0, 850), D3DXVECTOR2(20, 70));
}


void TestScene::ControlUpdate()
{
	if (beatManager->Update(Time::Tick()))
	{
		SceneBase::ControlUpdate();
	}
}
