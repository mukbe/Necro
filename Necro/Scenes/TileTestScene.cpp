#include "stdafx.h"
#include "TileTestScene.h"
#include "TileHelper.h"
#include "./GameObject/Map/TileNode.h"
#include "./GameObject/ShopKeeper.h"
#include "./GameObject/Player.h"
//일반몹
#include "./GameObject/Monster/GreenSlime.h"
#include "./GameObject/Monster/BlueSlime.h"
#include "./GameObject/Monster/Bat.h"
#include "./GameObject/Monster/Skeleton.h"
#include "./GameObject/Monster/Ghost.h"
#include "./GameObject/Monster/Monkey.h"
//보스몹
#include "./GameObject/Monster/Minotaur.h"
#include "./GameObject/Monster/RedDragon.h"
#include "./GameObject/Monster/GreenDragon.h"
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

// Item 
#include "./GameObject/Item/ItemBase.h"			
#include "./GameObject/Item/ItemShovel.h"		// 삽 or 곡괭
#include "./GameObject/Item/ItemWeapon.h"		// 무기 3종류
#include "./GameObject/Item/ItemDiamond.h"		// 다이아몬드
#include "./GameObject/Item/ItemHP.h"			// 체력하트 
#include "./GameObject/Item/ItemCoin.h"			// 동전
#include "./GameObject/Item/ItemTorch.h"
#include "./GameObject/Item/ItemWeaponDagger.h"
#include "./GameObject/Item/ItemWeaponBroadSword.h"
#include "./GameObject/Item/ItemWeaponSpear.h"
#include "./GameObject/Item/ItemShovelShovel.h"
#include "./GameObject/Item/ItemShovelPickaxe.h"



#include "./GameObject/Map/WallBase.h"
#include "./GameObject/Map/StoneWall.h"

TileTestScene::TileTestScene()
	: SceneBase()
{
}

TileTestScene::~TileTestScene()
{
}

void TileTestScene::Init()
{
	SceneBase::Init();

	ImageLoad();
	for (int i = 0; i < 10; i++)
	{
		Note* note = _ObjectPool->CreateObject<Note>("Note", D3DXVECTOR2(-20, 850), D3DXVECTOR2(8, 70));
		note->Init();
	}
	_ObjectPool->CreateObject<Heart>("Heart", { WinSizeX / 2.f , 830.f }, { 130.f,140.f });

	

	// TileManager(POINT mapSize, tileSize, 기준좌표)
	// mapSize는 {가로칸수, 세로칸수}
	// tileSize는 D3DXVECTOR2(가로크기, 세로크기)
	// 기준좌표는 D3DXVECTOR2(x좌표, y좌표) -> 여기를 LeftTop 위치로 가정하고 쭈르륵 그려짐
	//testTileManager = new TileManager({ 30,30 }, D3DXVECTOR2(52.f, 52.f), D3DXVECTOR2(13.f, 13.f));

	//타일 검출
	//testTileManager->Tile({ 2, 3 }); // 포인트 형태 매개변수 ({2,3})
	//testTileManager->Tile(2, 3); // 인트 형태 매개변수 2개 (x,y)

	//TileNode* testTile = testTileManager->Tile(0, 0); // 이런식으로 포인터에 넣을 수도 있고.
	//testTileManager->Tile(0, 0)->GetPos(); // 물론 멤버 함수도 존재함. 대부분 대충 보면 머하는 함수인지 알듯
	// 멤버 함수 모르겠으면 물어보셈.


	//testTile->GetAttribute(); //이건 오브젝트 타입 따오는거. 타입 이넘은 TileHelper.h 참조


	_TileMap->SetMapInfo({ 20, 20 }, defaultTileSize, D3DXVECTOR2(defaultTileSize.x / 2.f, defaultTileSize.y / 2.f));
	
	_TileMap->CreateMap();

	_TileMap->Tile(0, 6)->SetAlpha(0);
	_TileMap->Tile(1, 6)->SetAlpha(10);
	_TileMap->Tile(2, 6)->SetAlpha(20);
	_TileMap->Tile(3, 6)->SetAlpha(30);
	_TileMap->Tile(4, 6)->SetAlpha(40);
	_TileMap->Tile(5, 6)->SetAlpha(50);
	_TileMap->Tile(6, 6)->SetAlpha(60);
	_TileMap->Tile(7, 6)->SetAlpha(70);
	_TileMap->Tile(8, 6)->SetAlpha(80);
	_TileMap->Tile(9, 6)->SetAlpha(90);

	
	//_ObjectPool->CreateObject<Player>("Player", D3DXVECTOR2(26.f, 26.f), D3DXVECTOR2(52, 52));
	

	////몬스터
	//_ImageManager->AddFrameTexture("greenslime", ResourcePath + L"slime_green.png", 4, 2);
	//_ImageManager->AddFrameTexture("blueslime", ResourcePath + L"slime_ice.png", 4, 2);
	//_ImageManager->AddFrameTexture("bat", ResourcePath + L"bat.png", 4, 2);
	//
	//GreenSlime* greenslime = _ObjectPool->CreateObject<GreenSlime>("GreenSlime", D3DXVECTOR2(FIRSTCENTERXY, FIRSTCENTERXY), D3DXVECTOR2(52.f, 52.f));
	//BlueSlime* blueslime = _ObjectPool->CreateObject<BlueSlime>("BlueSlime", D3DXVECTOR2(FIRSTCENTERXY+TILESIZE, FIRSTCENTERXY + TILESIZE), D3DXVECTOR2(52.f, 52.f));
	//BlueSlime* blueslime2 = _ObjectPool->CreateObject<BlueSlime>("BlueSlime", D3DXVECTOR2(130.f, 78.f), D3DXVECTOR2(52.f, 52.f));
	//Bat* bat = _ObjectPool->CreateObject<Bat>("Bat", D3DXVECTOR2(FIRSTCENTERXY + TILESIZE*8, FIRSTCENTERXY + TILESIZE * 8), D3DXVECTOR2(52.f, 52.f));
	//
	_ObjectPool->CreateObject<Player>("Player", D3DXVECTOR2(78.f, 78.f), D3DXVECTOR2(52.f, 52.f));
	_ObjectPool->CreateObject<ShopKeeper>("ShopKeeper", D3DXVECTOR2(338.f, 78.f), D3DXVECTOR2(80.f, 80.f));
	MonsterLoad();

	beatManager->LoadText(ResourcePath + L"Music/stage1.txt");
	wstring path = ResourcePath + L"Music/stage1.ogg";
	SOUNDMANAGER->AddSound("stage1", String::WStringToString(path), true, false);


	for (int i = 0; i < 10; ++i)
	{
		StoneWall* testWall = _ObjectPool->CreateObject<StoneWall>("Wall", D3DXVECTOR2(0, 0), D3DXVECTOR2(52.f, 52.f));
		testWall->SetTransformInfo(0, i);
		_TileMap->Tile(0, i)->AddObject(ObjectWall, testWall);

		testWall = _ObjectPool->CreateObject<StoneWall>("Wall", D3DXVECTOR2(0, 0), D3DXVECTOR2(52.f, 52.f));
		testWall->SetTransformInfo(9, i);
		_TileMap->Tile(9, i)->AddObject(ObjectWall, testWall);

	}

	for (int i = 0; i < 7; ++i)
	{
		StoneWall* testWall = _ObjectPool->CreateObject<StoneWall>("Wall", D3DXVECTOR2(0, 0), D3DXVECTOR2(52.f, 52.f));
		testWall->SetTransformInfo(i+1, 0);
		_TileMap->Tile(i+1, 0)->AddObject(ObjectWall, testWall);

		testWall = _ObjectPool->CreateObject<StoneWall>("Wall", D3DXVECTOR2(0, 0), D3DXVECTOR2(52.f, 52.f));
		testWall->SetTransformInfo(i+1, 9);
		_TileMap->Tile(i+1, 9)->AddObject(ObjectWall, testWall);
	}

	for (int i = 0; i < 5; ++i)
	{
		WallBase* testWall = _ObjectPool->CreateObject<WallBase>("Wall", D3DXVECTOR2(0, 0), D3DXVECTOR2(52.f, 52.f));
		testWall->SetTransformInfo(5, i + 1);
		_TileMap->Tile(5, i+1)->AddObject(ObjectWall, testWall);
	}
	
	// UI 
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

	// Item

	ItemShovelShovel* IShovel = _ObjectPool->CreateObject<ItemShovelShovel>("Shovel", D3DXVECTOR2(), D3DXVECTOR2());
	IShovel->Init({ 2,6 });
	_TileMap->Tile(2, 6)->AddObject(ObjectItem, IShovel);
	IShovel->SetItemData(WShovel, 1, "Shovel");
	_GameData->SetShovelData(IShovel->GetInfo());

	ItemShovelPickaxe* IPickaxe = _ObjectPool->CreateObject<ItemShovelPickaxe>("Pickaxe", D3DXVECTOR2(), D3DXVECTOR2());
	IPickaxe->Init({ 2,5 });
	_TileMap->Tile(2, 5)->AddObject(ObjectItem, IPickaxe);
	IPickaxe->SetItemData(WPickaxe, 1, "Pickaxe");
	_GameData->SetShovelData(IPickaxe->GetInfo());


	ItemDiamond* Dia = _ObjectPool->CreateObject<ItemDiamond>("Dia", D3DXVECTOR2(), D3DXVECTOR2());
	Dia->Init({ 5,5 });
	
	//보류
	//ItemHead* Head = _ObjectPool->CreateObject<ItemHead>("ItemHead", D3DXVECTOR2(), D3DXVECTOR2());
	//Head->Init({ 5,6 });
	//Head->Init({ 5,6 });
	//_TileMap->Tile(5, 6)->AddObject(ObjectItem, Head);

	ItemCoin* Coin = _ObjectPool->CreateObject<ItemCoin>("ItemCoin", D3DXVECTOR2(), D3DXVECTOR2());
	Coin->Init({ 8,1 }); 

	ItemTorch* Torch = _ObjectPool->CreateObject<ItemTorch>("Torch", D3DXVECTOR2(), D3DXVECTOR2());
	Torch->Init({ 3,2 });
	_TileMap->Tile(3, 2)->AddObject(ObjectItem, Torch);
	Torch->SetItemData("Torch");
	_GameData->SetTorchData(Torch->GetInfo());

	ItemWeaponDagger* Dagger = _ObjectPool->CreateObject<ItemWeaponDagger>("Dagger", D3DXVECTOR2(), D3DXVECTOR2());
	Dagger->Init({ 1,3 });
	_TileMap->Tile(1, 3)->AddObject(ObjectItem, Dagger);
	Dagger->SetItemData(WDagger, { 1,1 }, 1, "Swipe_Dagger", "Dagger");
	_GameData->SetWeaponData(Dagger->GetInfo());

	ItemWeaponBroadSword* BroadSword = _ObjectPool->CreateObject<ItemWeaponBroadSword>("Broadsword", D3DXVECTOR2(), D3DXVECTOR2());
	BroadSword->Init({ 2,3 });
	_TileMap->Tile(2, 3)->AddObject(ObjectItem, BroadSword);
	BroadSword->SetItemData(WBroadsword, { 3,1 }, 1, "Swipe_Broadsword", "Broadsword");
	_GameData->SetWeaponData(BroadSword->GetInfo());

	ItemWeaponSpear* Spear = _ObjectPool->CreateObject<ItemWeaponSpear>("Spear", D3DXVECTOR2(), D3DXVECTOR2());
	Spear->Init({ 3,3 });
	_TileMap->Tile(3, 3)->AddObject(ObjectItem, Spear);
	Spear->SetItemData(WSpear, { 1,2 }, 1, "Swipe_Spear", "Spear");
	_GameData->SetWeaponData(Spear->GetInfo());

}

void TileTestScene::ImageLoad()
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

	_ImageManager->AddTexture("DefaultWall", ResourcePath + L"Wall/WallBase.png");
	_ImageManager->AddTexture("StoneWall", ResourcePath + L"Wall/StoneWall.png");
	
	// Effect
	_ImageManager->AddTexture("EffectShovel", ResourcePath + L"Effect/Shovel.png");
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

void TileTestScene::MonsterLoad()
{
	//_ObjectPool->CreateObject<GreenSlime>("GreenSlime", D3DXVECTOR2(26, 52), D3DXVECTOR2(52.f, 52.f));
	_ObjectPool->CreateObject<BlueSlime>("BlueSlime", D3DXVECTOR2(26 + 52, 26 + 52*2), D3DXVECTOR2(52.f, 52.f));
	/*_ObjectPool->CreateObject<BlueSlime>("BlueSlime", D3DXVECTOR2(130.f, 26 + 52 * 2), D3DXVECTOR2(52.f, 52.f));
	_ObjectPool->CreateObject<Bat>("Bat", D3DXVECTOR2(26 + 52, 26 + 52 * 6), D3DXVECTOR2(52.f, 52.f));*/
	/*_ObjectPool->CreateObject<Skeleton>("Skeleton", D3DXVECTOR2(26 + 52, 26 + 52 * 8), D3DXVECTOR2(52.f, 52.f));
	_ObjectPool->CreateObject<Ghost>("Ghost", D3DXVECTOR2(26 + 52 * 4, 26 + 52 * 8), D3DXVECTOR2(52.f, 52.f));
	_ObjectPool->CreateObject<Monkey>("Monkey", D3DXVECTOR2(26 + 52 * 5, 26 + 52 * 5), D3DXVECTOR2(52.f, 52.f));
	_ObjectPool->CreateObject<Minotaur>("Minotaur", D3DXVECTOR2(26 + 52 * 5, 26 + 52 * 6), D3DXVECTOR2(100.f, 100.f));
	_ObjectPool->CreateObject<RedDragon>("RedDragon", D3DXVECTOR2(26 + 52 * 3, 26 + 52 * 4), D3DXVECTOR2(100.f, 100.f));
	_ObjectPool->CreateObject<GreenDragon>("GreenDragon", D3DXVECTOR2(26 + 52 * 3, 26 + 52 * 5), D3DXVECTOR2(100.f, 100.f));*/

}
