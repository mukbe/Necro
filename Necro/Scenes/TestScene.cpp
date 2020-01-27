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
#include "./GameObject/UI/HPUi.h"

#include "./GameObject/Item/ItemCoin.h"		// 동전
#include "./GameObject/Item/ItemWeapon.h"	// 무기 
#include "./GameObject/Item/ItemBody.h"		// 갑빠
#include "./GameObject/Item/ItemDiamond.h"	// 다이아몬드
#include "./GameObject/Item/ItemHead.h"		// 뚜껑
#include "./GameObject/Item/ItemShovel.h"	// 삽 / 곡괭
#include "./GameObject/Item/ItemHP.h"		// 체력아이템 / 음식 


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
	// UI 관련
	for (int i = 0; i < 10; i++)
	{
		Note* node = _ObjectPool->CreateObject<Note>("Note", D3DXVECTOR2(-20, 840), D3DXVECTOR2(8, 70));
		node->Init();
	}

	_ObjectPool->CreateObject<TestPlayer>("Player", D3DXVECTOR2(200, 200), D3DXVECTOR2(100, 100));
	_ObjectPool->CreateObject<Heart>("Heart", { WinSizeX / 2.f , 820.f }, { 110.f,120.f });
	_ObjectPool->CreateObject<HPUi>("UI_HPUi", D3DXVECTOR2(800, 50), D3DXVECTOR2(50, 50));
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

	
	//필드 아이템 관련 
	ItemCoin* Coin =  _ObjectPool->CreateObject<ItemCoin>("ItemCoin", D3DXVECTOR2(), D3DXVECTOR2());
	Coin->Init({ 8,1 }); // 아이템 뿌릴 타일 좌표

	ItemWeapon* Weapon = _ObjectPool->CreateObject<ItemWeapon>("ItemWeapon", D3DXVECTOR2(), D3DXVECTOR2());
	Weapon->Init({ 2, 5 });

	ItemBody* Body = _ObjectPool->CreateObject<ItemBody>("ItemBody", D3DXVECTOR2(), D3DXVECTOR2());
	Body->Init({ 1, 5 });

	ItemHead* Head = _ObjectPool->CreateObject<ItemHead>("ItemHead", D3DXVECTOR2(), D3DXVECTOR2());
	Head->Init({ 1,6 });

	ItemShovel* Shovel = _ObjectPool->CreateObject<ItemShovel>("ItemShovel", D3DXVECTOR2(), D3DXVECTOR2());
	Shovel->Init({ 2,6 });


	// 어떻게 해야 아이템을 나눌수가 있을 까....
	ItemDiamond* Dia = _ObjectPool->CreateObject<ItemDiamond>("Dia", D3DXVECTOR2(), D3DXVECTOR2());
	Dia->Init({ 7,1 });

	ItemDiamond* Dia2 = _ObjectPool->CreateObject<ItemDiamond>("Dia2", D3DXVECTOR2(), D3DXVECTOR2());
	Dia2->Init({ 7,2 });

	// 노래 
	beatManager->LoadText(ResourcePath + L"Music/stage1.txt");
	wstring path = ResourcePath + L"Music/stage1.ogg";
	SOUNDMANAGER->AddSound("stage1", String::WStringToString(path), true, false);
}


// 이미지 
void TestScene::ImageLoad()
{
	_ImageManager->AddFrameTexture("HeartTemp", ResourcePath + L"UI/TempHeart.png", 2, 1);
	_ImageManager->AddTexture("NoteBeat", ResourcePath + L"UI/basicbeat.png");

	_ImageManager->AddFrameTexture("HpTemp", ResourcePath + L"UI/UI_FullHp2.png", 2, 1);
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
	_ImageManager->AddFrameTexture("Dagger", ResourcePath + L"Item/Dagger.png", 1, 2);
	_ImageManager->AddFrameTexture("Broadsword", ResourcePath + L"Item/Broadsword.png", 1, 2);
	_ImageManager->AddFrameTexture("Spear", ResourcePath + L"Item/Spear.png", 1, 2);
	_ImageManager->AddFrameTexture("Leather_Armor", ResourcePath + L"Item/Leather_Armor.png", 1, 2);
	_ImageManager->AddFrameTexture("Head_Cap", ResourcePath + L"Item/Head_Cap.png", 1, 2);
	_ImageManager->AddFrameTexture("Torch", ResourcePath + L"Item/Torch.png", 1, 2);
	_ImageManager->AddFrameTexture("Pickaxe", ResourcePath + L"Item/Pickaxe.png", 1, 2);
	_ImageManager->AddFrameTexture("Shovel", ResourcePath + L"Item/Shovel.png", 1, 2);
	_ImageManager->AddFrameTexture("Apple", ResourcePath + L"Item/Apple.png", 1, 2);
	_ImageManager->AddFrameTexture("Chezz", ResourcePath + L"Item/Chezz.png", 1, 2);
	_ImageManager->AddFrameTexture("Dia", ResourcePath + L"Item/Field_Dia.png", 1, 2);
	_ImageManager->AddFrameTexture("Dia2", ResourcePath + L"Item/Field_Dia2.png", 1, 2);
	_ImageManager->AddFrameTexture("FullHeat", ResourcePath + L"Item/FullHeart.png", 1, 2);
	_ImageManager->AddFrameTexture("Heart", ResourcePath + L"Item/Heart.png", 1, 2);
}
