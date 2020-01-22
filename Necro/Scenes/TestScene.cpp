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

	ImageLoad();
	//노트
	_ObjectPool->CreateObject<Note>("Note", D3DXVECTOR2(-20, 850), D3DXVECTOR2(20, 70));
	_ObjectPool->CreateObject<Note>("Note", D3DXVECTOR2(-20, 850), D3DXVECTOR2(20, 70));
	_ObjectPool->CreateObject<Note>("Note", D3DXVECTOR2(-20, 850), D3DXVECTOR2(20, 70));
	_ObjectPool->CreateObject<Note>("Note", D3DXVECTOR2(-20, 850), D3DXVECTOR2(20, 70));
	_ObjectPool->CreateObject<Note>("Note", D3DXVECTOR2(-20, 850), D3DXVECTOR2(20, 70));
	_ObjectPool->CreateObject<Note>("Note", D3DXVECTOR2(-20, 850), D3DXVECTOR2(20, 70));
	_ObjectPool->CreateObject<Note>("Note", D3DXVECTOR2(-20, 850), D3DXVECTOR2(20, 70));
	// 플레이어 , 심장 
	_ObjectPool->CreateObject<TestPlayer>("Player", D3DXVECTOR2(200, 200), D3DXVECTOR2(100, 100));
	_ObjectPool->CreateObject<Heart>("Heart", { WinSizeX / 2.f , 830.f }, { 130.f,140.f });
	// UI 이미지 
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

	
	//사운드
	beatManager->LoadText(ResourcePath + L"Music/stage1.txt");
	wstring path = ResourcePath + L"Music/stage1.ogg";
	SOUNDMANAGER->AddSound("stage1", String::WStringToString(path), true, false);
}



void TestScene::ImageLoad()
{
	_ImageManager->AddFrameTexture("HeartTemp", ResourcePath + L"UI/TempHeart.png", 2, 1);

	_ImageManager->AddTexture("UI_ThrowSlot", ResourcePath + L"UI/UI_ThrowSlot.png");

	
	//_ImageManager->AddFrameTexture("Field_Coin", ResourcePath + L"Item/Field_Coin", 1, 2);

}
