#pragma once
#include "stdafx.h"
#include "GameScene.h"

#include "TileHelper.h"
#include "./GameObject/Map/TileNode.h"

/*Player*/
#include "./GameObject/Player.h"

/*Monster*/
#include "./GameObject/Monster/GreenSlime.h"
#include "./GameObject/Monster/BlueSlime.h"
#include "./GameObject/Monster/Bat.h"
#include "./GameObject/Monster/Skeleton.h"
#include "./GameObject/Monster/Ghost.h"
#include "./GameObject/Monster/Monkey.h"

#include "./GameObject/Monster/Minotaur.h"
#include "./GameObject/Monster/RedDragon.h"
#include "./GameObject/Monster/GreenDragon.h"

/* Item */
#include "./GameObject/Item/ItemBase.h"			
#include "./GameObject/Item/ItemShovel.h"		// 삽 or 곡괭
#include "./GameObject/Item/ItemWeapon.h"		// 무기 3종류
#include "./GameObject/Item/ItemDiamond.h"		// 다이아몬드
#include "./GameObject/Item/ItemBody.h"			// 방어구
#include "./GameObject/Item/ItemHead.h"			// 뚝배기
#include "./GameObject/Item/ItemHP.h"			// 체력하트 
#include "./GameObject/Item/ItemCoin.h"			// 동전
#include "./GameObject/Item/ItemTorch.h"
#include "./GameObject/Item/ItemWeaponDagger.h"
#include "./GameObject/Item/ItemWeaponBroadSword.h"
#include "./GameObject/Item/ItemWeaponSpear.h"
#include "./GameObject/Item/ItemShovelShovel.h"
#include "./GameObject/Item/ItemShovelPickaxe.h"

/*Wall*/
#include "./GameObject/Map/WallBase.h"
#include "./GameObject/Map/StoneWall.h"
#include "./GameObject/Map/GravelWall.h"
#include "./GameObject/Map/GoldWall.h"
#include "./GameObject/Map/Door.h"
#include "./GameObject/Map/DoorVertical.h"

/*NPC*/
#include "./GameObject/ShopKeeper.h"

// Ui 
#include "./GameObject/UI/Heart.h"				// 심장 
#include "./GameObject/UI/Note.h"				// 노트
#include "./GameObject/UI/Diamond.h"			// 다이아 
#include "./GameObject/UI/Coin.h"				// 코인
#include "./GameObject/UI/AttackSlot.h"			// 무기슬롯
#include "./GameObject/UI/ShovelSlot.h"			// 삽 슬롯
#include "./GameObject/UI/TorchSlot.h"			// 횃불 슬롯
#include "./GameObject/UI/ItemSlot.h"			// 체력/ 아이템 슬롯
#include "./GameObject/UI/ThrowSlot.h"			// 던지기 슬롯
#include "./GameObject/UI/HPUi.h"				// 체력UI 


GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

void GameScene::Init()
{
	SceneBase::Init();

	ImageLoad();

	_ObjectPool->CreateObject<Heart>("Heart", { WinSizeX / 2.f , 830.f }, { 130.f,140.f });

	for (int i = 0; i < 10; i++)
	{
		Note* note = _ObjectPool->CreateObject<Note>("Note", D3DXVECTOR2(-20, 850), D3DXVECTOR2(8, 70));
		note->Init();
	}
	_ObjectPool->CreateObject<Heart>("Heart", { WinSizeX / 2.f , 830.f }, { 130.f,140.f });


	beatManager->LoadText(ResourcePath + L"Music/stage1.txt");
	wstring path = ResourcePath + L"Music/stage1.ogg";
	SOUNDMANAGER->AddSound("stage1", String::WStringToString(path), true, false);

	_ObjectPool->CreateObject<AttackSlot>("UI_AttackSlot", D3DXVECTOR2(150, 75), D3DXVECTOR2(75, 75));
	_ObjectPool->CreateObject<ShovelSlot>("UI_ShovelSlot", D3DXVECTOR2(70, 75), D3DXVECTOR2(75, 75));
	_ObjectPool->CreateObject<ItemSlot>("UI_ItemSlot", D3DXVECTOR2(70, 170), D3DXVECTOR2(75, 75));
	_ObjectPool->CreateObject<ThrowSlot>("UI_ThrowSlot", D3DXVECTOR2(70, 260), D3DXVECTOR2(75, 75));
	_ObjectPool->CreateObject<Coin>("UI_Coin", D3DXVECTOR2(1200, 50), D3DXVECTOR2(50, 50));
	_ObjectPool->CreateObject<Diamond>("UI_Diamond", D3DXVECTOR2(1200, 100), D3DXVECTOR2(50, 50));
	_ObjectPool->CreateObject<TorchSlot>("UI_TorchSlot", D3DXVECTOR2(230, 75), D3DXVECTOR2(75, 75));

	for (int i = 0; i < 5; i++)
	{
		HPUi* Hp = _ObjectPool->CreateObject<HPUi>("HPUi", D3DXVECTOR2(1100 - i * 55, 50), D3DXVECTOR2(50, 50));
		Hp->Init();
	}

	_TileMap->LoadMap(L"Stage1");
	//_TileMap->ActiveAll();
}

void GameScene::ImageLoad()
{
	_ImageManager->AddFrameTexture("HeartTemp", ResourcePath + L"UI/TempHeart.png", 2, 1);

	_ImageManager->AddFrameTexture("DefaultMap", ResourcePath + L"DefaultTileMap.png", 2, 2);
	// 플레이어
	_ImageManager->AddFrameTexture("NormalPlayer", ResourcePath + L"Player/NormalPlayer.png", 4, 2);
	_ImageManager->AddFrameTexture("LeatherPlayer", ResourcePath + L"Player/LeatherPlayer.png", 4, 2);
	_ImageManager->AddTexture("PlayerShadow", ResourcePath + L"Player/PlayerShadow.png");

	// NPC
	_ImageManager->AddFrameTexture("ShopKeeper", ResourcePath + L"NPC/ShopKeeper.png", 8, 2);
	_ImageManager->AddTexture("Music", ResourcePath + L"NPC/Music.png");

	_ImageManager->AddTexture("NoteBeat", ResourcePath + L"UI/basicbeat.png");

	// Wall
	_ImageManager->AddTexture("DefaultWall", ResourcePath + L"Wall/WallBase.png");
	_ImageManager->AddTexture("StoneWall", ResourcePath + L"Wall/StoneWall.png");
	_ImageManager->AddTexture("GravelWallFine", ResourcePath + L"Wall/GravelWallFine.png");
	_ImageManager->AddTexture("GravelWallDamaged", ResourcePath + L"Wall/GravelWallDamaged.png");
	_ImageManager->AddTexture("GoldWallFine", ResourcePath + L"Wall/GoldWallFine.png");
	_ImageManager->AddTexture("GoldWallDamaged", ResourcePath + L"Wall/GoldWallDamaged.png");
	_ImageManager->AddTexture("Door", ResourcePath + L"Stuff/Door.png");
	_ImageManager->AddTexture("DoorVertical", ResourcePath + L"Stuff/DoorVertical.png");
	_ImageManager->AddTexture("Stairs", ResourcePath + L"Stuff/Stairs.png");
	_ImageManager->AddTexture("BlackWall", ResourcePath + L"Wall/BlackWall.png");
	SOUNDMANAGER->AddSound("Dig", "../_Resources/Sound/Dig.Ogg", false, false);
	SOUNDMANAGER->AddSound("DigFail", "../_Resources/Sound/DigFail.Ogg", false, false);
	SOUNDMANAGER->AddSound("DoorOpen", "../_Resources/Sound/DoorOpen.Ogg", false, false);

	// Effect
	_ImageManager->AddTexture("EffectShovel", ResourcePath + L"Effect/Shovel.png");
	wstring temp = ResourcePath + L"Effect/Shovel.png";
	string temp1;
	temp1.assign(temp.begin(), temp.end());
	EFFECTS->AddEffect("EffectShovel", "EffectShovel");
	_ImageManager->AddFrameTexture("Swipe_Dagger", ResourcePath + L"Effect/Swipe_Dagger.png", 3, 1);
	_ImageManager->AddFrameTexture("Swipe_Spear", ResourcePath + L"Effect/Swipe_Spear.png", 6, 1);
	_ImageManager->AddFrameTexture("Swipe_Broadsword", ResourcePath + L"Effect/Swipe_Broadsword.png", 3, 1);
	_ImageManager->AddFrameTexture("Playerhit", ResourcePath + L"Effect/Playerhit.png", 5, 1);

	//Item
	_ImageManager->AddFrameTexture("Shovel", ResourcePath + L"Item/Shovel.png", 1, 2);
	_ImageManager->AddFrameTexture("Dagger", ResourcePath + L"Item/Dagger.png", 1, 2);
	_ImageManager->AddFrameTexture("Broadsword", ResourcePath + L"Item/Broadsword.png", 1, 2);
	_ImageManager->AddFrameTexture("Spear", ResourcePath + L"Item/Spear.png", 1, 2);
	_ImageManager->AddFrameTexture("Dia2", ResourcePath + L"Item/Field_Dia2.png", 1, 2);
	_ImageManager->AddFrameTexture("Chezz", ResourcePath + L"Item/Chezz.png", 1, 2);
	_ImageManager->AddFrameTexture("Leather_Armor", ResourcePath + L"Item/Leather_Armor.png", 1, 2);
	_ImageManager->AddFrameTexture("Head_Cap", ResourcePath + L"Item/Head_Cap.png", 1, 2);
	_ImageManager->AddFrameTexture("Torch", ResourcePath + L"Item/Torch.png", 1, 2);
	_ImageManager->AddFrameTexture("Pickaxe", ResourcePath + L"Item/Pickaxe.png", 1, 2);
	_ImageManager->AddFrameTexture("Field_Coin", ResourcePath + L"Item/Field_Coin.png", 2, 2);
	_ImageManager->AddTexture("Shadow", ResourcePath + L"Shadow.png");

	//UI
	_ImageManager->AddTexture("UI_AttackSlot", ResourcePath + L"UI/UI_AttackSlot.png");
	_ImageManager->AddTexture("UI_Diamond", ResourcePath + L"UI/UI_Diamond.png");
	_ImageManager->AddTexture("UI_ShovelSlot", ResourcePath + L"UI/UI_ShovelSlot.png");
	_ImageManager->AddTexture("UI_TorchSlot", ResourcePath + L"UI/UI_TorchSlot.png");
	_ImageManager->AddTexture("UI_HeadSlot", ResourcePath + L"UI/UI_HeadSlot.png");
	_ImageManager->AddTexture("UI_ItemlSlot", ResourcePath + L"UI/UI_ItemSlot2.png");
	_ImageManager->AddTexture("UI_BodySlot", ResourcePath + L"UI/UI_BodySlot.png");
	_ImageManager->AddTexture("UI_BoomSlot", ResourcePath + L"UI/UI_BoomSlot.png");
	_ImageManager->AddTexture("UI_ThrowSlot", ResourcePath + L"UI/UI_ThrowSlot.png");
	_ImageManager->AddTexture("UI_Coin", ResourcePath + L"UI/UI_Coin.png");
	_ImageManager->AddTexture("E_Hp", ResourcePath + L"UI/Heart_Empty.png");
	_ImageManager->AddTexture("H_Hp", ResourcePath + L"UI/Heart_half .png");
	_ImageManager->AddTexture("F_Hp", ResourcePath + L"UI/Heart.png");  //체력 


	//몬스터
	_ImageManager->AddFrameTexture("greenslime", ResourcePath + L"Monster/slime_green.png", 4, 4);
	_ImageManager->AddFrameTexture("blueslime", ResourcePath + L"Monster/slime_blue.png", 4, 4);
	_ImageManager->AddFrameTexture("bat", ResourcePath + L"Monster/bat.png", 4, 4);
	_ImageManager->AddFrameTexture("skeleton", ResourcePath + L"Monster/skeleton.png", 16, 4);
	_ImageManager->AddFrameTexture("ghost", ResourcePath + L"Monster/ghost.png", 2, 4);
	_ImageManager->AddFrameTexture("monkey", ResourcePath + L"Monster/monkey.png", 6, 4);
	_ImageManager->AddFrameTexture("minotaur", ResourcePath + L"Monster/minotaur.png", 9, 4);
	_ImageManager->AddFrameTexture("reddragon", ResourcePath + L"Monster/dragon_red.png", 9, 4);
	_ImageManager->AddFrameTexture("greendragon", ResourcePath + L"Monster/dragon_green.png", 4, 4);

	//Font
	_ImageManager->AddFrameTexture("NumberFontUI", ResourcePath + L"Font/NumberFontUI.png", 10, 1);
	_ImageManager->AddTexture("UI_x", ResourcePath + L"Font/UI_x.png");

}
