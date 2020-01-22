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

	_ImageManager->AddTexture("UI_Coin", ResourcePath + L"UI/COIN.png");				
	_ImageManager->AddTexture("UI_CoinX", ResourcePath + L"Font/x.png");
	_ObjectPool->CreateObject<CoinCount>("UI_CoinX", D3DXVECTOR2(1235, 50), D3DXVECTOR2(15, 15));		// 코인 이미지 옆 x 
	_ObjectPool->CreateObject<Coin>("UI_Coin", D3DXVECTOR2(1200, 50), D3DXVECTOR2(50, 50));				// 코인 이미지
	
	_ImageManager->AddTexture("UI_Diamond", ResourcePath + L"UI/DIA.png");
	_ImageManager->AddTexture("UI_DIaX", ResourcePath + L"Font/x.png");
	_ObjectPool->CreateObject<Diamond>("UI_Diamond", D3DXVECTOR2(1200, 100), D3DXVECTOR2(50, 50));		// 다이아몬드 이미지
	_ObjectPool->CreateObject<CoinCount>("UI_DIaX", D3DXVECTOR2(1235, 100), D3DXVECTOR2(15, 15));

	_ObjectPool->CreateObject<AttackSlot>("UI_AttackSlot", D3DXVECTOR2(150, 75), D3DXVECTOR2(75, 75));	// 어택인벤 이미지 
	_ObjectPool->CreateObject<ShovelSlot>("UI_ShovelSlot", D3DXVECTOR2(70, 75), D3DXVECTOR2(75, 75));	// 삽/ 곡괭이 인벤
	_ObjectPool->CreateObject<TorchSlot>("UI_TorchSlot", D3DXVECTOR2(230, 75), D3DXVECTOR2(75, 75));	// 횃불 인벤
	_ObjectPool->CreateObject<BodySlot>("UI_BodySlot", D3DXVECTOR2(310, 75), D3DXVECTOR2(75, 75));		// 몸통
	_ObjectPool->CreateObject<HeadSlot>("UI_HeadSlot", D3DXVECTOR2(390, 75), D3DXVECTOR2(75, 75));		// 뚝배기
	_ObjectPool->CreateObject<ItemSlot>("UI_ItemSlot", D3DXVECTOR2(70, 170), D3DXVECTOR2(75, 75));		// 아이템 / 음식 
	_ObjectPool->CreateObject<BoomSlot>("UI_BoomSlot", D3DXVECTOR2(70, 350), D3DXVECTOR2(75, 75));		// 폭탄
	_ObjectPool->CreateObject<ThrowSlot>("UI_ThrowSlot", D3DXVECTOR2(70, 260), D3DXVECTOR2(75, 75));	// 단검 , 창 던지기 이미지 
	
	beatManager->LoadText(ResourcePath + L"zone.txt");
}


void TestScene::ControlUpdate()
{
	//if (beatManager->Update(Time::Tick()))
	//{
	//	SceneBase::ControlUpdate();
	//}
}
