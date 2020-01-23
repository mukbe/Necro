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

#include "./GameObject/Item/ItemCoin.h"

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

	ImageLoad();

	for (int i = 0; i < 10; i++)
	{
		Note* node = _ObjectPool->CreateObject<Note>("Note", D3DXVECTOR2(-20, 840), D3DXVECTOR2(8, 70));
		node->Init();
	}


	_ObjectPool->CreateObject<TestPlayer>("Player", D3DXVECTOR2(200, 200), D3DXVECTOR2(100, 100));
	_ObjectPool->CreateObject<Heart>("Heart", { WinSizeX / 2.f , 820.f }, { 110.f,120.f });

	_ObjectPool->CreateObject<Coin>("UI_Coin", D3DXVECTOR2(1200, 50), D3DXVECTOR2(50, 50));
	_ObjectPool->CreateObject<Diamond>("UI_Diamond", D3DXVECTOR2(1200, 100), D3DXVECTOR2(50, 50));
	_ObjectPool->CreateObject<AttackSlot>("UI_AttackSlot", D3DXVECTOR2(150, 75), D3DXVECTOR2(75, 75));
	_ObjectPool->CreateObject<ShovelSlot>("UI_ShovelSlot", D3DXVECTOR2(70, 75), D3DXVECTOR2(75, 75));
	_ObjectPool->CreateObject<TorchSlot>("UI_TorchSlot", D3DXVECTOR2(230, 75), D3DXVECTOR2(75, 75));
	_ObjectPool->CreateObject<BodySlot>("UI_BodySlot", D3DXVECTOR2(310, 75), D3DXVECTOR2(75, 75));
	_ObjectPool->CreateObject<HeadSlot>("UI_HeadSlot", D3DXVECTOR2(390, 75), D3DXVECTOR2(75, 75));
	_ObjectPool->CreateObject<ItemSlot>("UI_ItemSlot", D3DXVECTOR2(70, 170), D3DXVECTOR2(75, 75));
	_ObjectPool->CreateObject<BoomSlot>("UI_BoomSlot", D3DXVECTOR2(70, 350), D3DXVECTOR2(75, 75));
	_ObjectPool->CreateObject<ThrowSlot>("UI_ThrowSlot", D3DXVECTOR2(70, 260), D3DXVECTOR2(75, 75));

	ItemCoin* temp =  _ObjectPool->CreateObject<ItemCoin>("ItemCoin", D3DXVECTOR2(), D3DXVECTOR2());
	temp->Init({ 3,3 });


	beatManager->LoadText(ResourcePath + L"Music/stage1.txt");
	wstring path = ResourcePath + L"Music/stage1.ogg";
	SOUNDMANAGER->AddSound("stage1", String::WStringToString(path), true, false);
}



void TestScene::ImageLoad()
{
	_ImageManager->AddFrameTexture("HeartTemp", ResourcePath + L"UI/TempHeart.png", 2, 1);
	_ImageManager->AddTexture("NoteBeat", ResourcePath + L"UI/basicbeat.png");

	_ImageManager->AddTexture("UI_ThrowSlot", ResourcePath + L"UI/UI_ThrowSlot.png");
	_ImageManager->AddTexture("UI_Coin", ResourcePath + L"UI/UI_Coin.png");
	_ImageManager->AddTexture("UI_AttackSlot", ResourcePath + L"UI/UI_AttackSlot.png");
	_ImageManager->AddTexture("UI_BodySlot", ResourcePath + L"UI/UI_BodySlot.png");
	_ImageManager->AddTexture("UI_BoomSlot", ResourcePath + L"UI/UI_BoomSlot.png");
	_ImageManager->AddTexture("UI_Diamond", ResourcePath + L"UI/UI_Diamond.png");
	_ImageManager->AddTexture("UI_HeadSlot", ResourcePath + L"UI/UI_HeadSlot.png");
	_ImageManager->AddTexture("UI_FullHp", ResourcePath + L"UI/UI_FullHp.png");
	_ImageManager->AddTexture("UI_HalfHp", ResourcePath + L"UI/UI_HalfHp.png");
	_ImageManager->AddTexture("UI_EmptyHp", ResourcePath + L"UI/UI_EmptyHp.png");
	_ImageManager->AddTexture("UI_ItemlSlot", ResourcePath + L"UI/UI_ItemSlot.png");
	_ImageManager->AddTexture("UI_ShovelSlot", ResourcePath + L"UI/UI_ShovelSlot.png");
	_ImageManager->AddTexture("UI_TorchSlot", ResourcePath + L"UI/UI_TorchSlot.png");

	_ImageManager->AddFrameTexture("Field_Coin", ResourcePath + L"Item/Field_Coin.png", 1, 2);
}
