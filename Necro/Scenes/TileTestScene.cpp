#include "stdafx.h"
#include "TileTestScene.h"
#include "TileHelper.h"
#include "./GameObject/Map/TileNode.h"

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

#include "./GameObject/UI/Heart.h"
#include "./GameObject/UI/Note.h"

#include "./GameObject/Item/ItemBase.h"
#include "./GameObject/Item/ItemShovel.h"

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
		Note* note = _ObjectPool->CreateObject<Note>("Note", D3DXVECTOR2(-20, 850), D3DXVECTOR2(20, 70));
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


	_TileMap->SetMapInfo({ 10, 10 }, defaultTileSize, D3DXVECTOR2(defaultTileSize.x / 2.f, defaultTileSize.y / 2.f));
	
	_TileMap->CreateMap();

	
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
	_ObjectPool->CreateObject<Player>("Player", D3DXVECTOR2(78, 78), D3DXVECTOR2(52.f, 52.f));
	MonsterLoad();

	beatManager->LoadText(ResourcePath + L"Music/stage1.txt");
	wstring path = ResourcePath + L"Music/stage1.ogg";
	SOUNDMANAGER->AddSound("stage1", String::WStringToString(path), true, false);

	for (int i = 0; i < 10; ++i)
	{
		StoneWall* testWall = _ObjectPool->CreateObject<StoneWall>("Wall", D3DXVECTOR2(0, 0), D3DXVECTOR2(52.f, 52.f));
		testWall->SetTransformInfo(0, i);
		_TileMap->Tile(0, i)->AddObject(testWall);

		testWall = _ObjectPool->CreateObject<StoneWall>("Wall", D3DXVECTOR2(0, 0), D3DXVECTOR2(52.f, 52.f));
		testWall->SetTransformInfo(9, i);
		_TileMap->Tile(9, i)->AddObject(testWall);
	}

	for (int i = 0; i < 8; ++i)
	{
		StoneWall* testWall = _ObjectPool->CreateObject<StoneWall>("Wall", D3DXVECTOR2(0, 0), D3DXVECTOR2(52.f, 52.f));
		testWall->SetTransformInfo(i+1, 0);
		_TileMap->Tile(i+1, 0)->AddObject(testWall);

		testWall = _ObjectPool->CreateObject<StoneWall>("Wall", D3DXVECTOR2(0, 0), D3DXVECTOR2(52.f, 52.f));
		testWall->SetTransformInfo(i+1, 9);
		_TileMap->Tile(i+1, 9)->AddObject(testWall);
	}


	for (int i = 0; i < 5; ++i)
	{
		WallBase* testWall = _ObjectPool->CreateObject<WallBase>("Wall", D3DXVECTOR2(0, 0), D3DXVECTOR2(52.f, 52.f));
		testWall->SetTransformInfo(5, i + 1);
		_TileMap->Tile(5, i+1)->AddObject(testWall);
	}
	//ItemShovel* Shovel = _ObjectPool->CreateObject<ItemShovel>("ItemShovel", D3DXVECTOR2(0,0), D3DXVECTOR2(52.f,52.f));
	//Shovel->Init({ 2,6 });

	ItemShovel* Shovel = _ObjectPool->CreateObject<ItemShovel>("ItemShovel", D3DXVECTOR2(), D3DXVECTOR2());
	Shovel->Init({ 2,6 });

}

void TileTestScene::ImageLoad()
{
	_ImageManager->AddFrameTexture("HeartTemp", ResourcePath + L"UI/TempHeart.png", 2, 1);

	_ImageManager->AddFrameTexture("DefaultMap", ResourcePath + L"DefaultTileMap.png", 2, 2);

	_ImageManager->AddFrameTexture("PlayerHeadRight", ResourcePath + L"Player/PlayerHeadRight.png", 4, 2);
	_ImageManager->AddFrameTexture("PlayerBodyRight", ResourcePath + L"Player/PlayerBodyRight.png", 4, 10);
	_ImageManager->AddFrameTexture("PlayerHeadLeft", ResourcePath + L"Player/PlayerHeadLeft.png", 4, 2);
	_ImageManager->AddFrameTexture("PlayerBodyLeft", ResourcePath + L"Player/PlayerBodyLeft.png", 4, 10);
	_ImageManager->AddTexture("PlayerShadow", ResourcePath + L"Player/PlayerShadow.png");
	_ImageManager->AddTexture("NoteBeat", ResourcePath + L"UI/basicbeat.png");

	_ImageManager->AddTexture("DefaultWall", ResourcePath + L"Wall/WallBase.png");
	_ImageManager->AddTexture("StoneWall", ResourcePath + L"Wall/StoneWall.png");
	_ImageManager->AddTexture("EffectShovel", ResourcePath + L"Effect/Shovel.png");

	_ImageManager->AddFrameTexture("Shovel", ResourcePath + L"Item/Shovel.png", 1, 2);

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
}

void TileTestScene::MonsterLoad()
{
	_ObjectPool->CreateObject<GreenSlime>("GreenSlime", D3DXVECTOR2(26, 52), D3DXVECTOR2(52.f, 52.f));
	_ObjectPool->CreateObject<BlueSlime>("BlueSlime", D3DXVECTOR2(26 + 52, 26 + 52*2), D3DXVECTOR2(52.f, 52.f));
	_ObjectPool->CreateObject<BlueSlime>("BlueSlime", D3DXVECTOR2(130.f, 26 + 52 * 2), D3DXVECTOR2(52.f, 52.f));
	_ObjectPool->CreateObject<Bat>("Bat", D3DXVECTOR2(26 + 52, 26 + 52 * 6), D3DXVECTOR2(52.f, 52.f));
	_ObjectPool->CreateObject<Skeleton>("Skeleton", D3DXVECTOR2(26 + 52, 26 + 52 * 8), D3DXVECTOR2(52.f, 52.f));
	_ObjectPool->CreateObject<Ghost>("Ghost", D3DXVECTOR2(26 + 52 * 4, 26 + 52 * 8), D3DXVECTOR2(52.f, 52.f));
	_ObjectPool->CreateObject<Monkey>("Monkey", D3DXVECTOR2(26 + 52 * 5, 26 + 52 * 5), D3DXVECTOR2(52.f, 52.f));
	_ObjectPool->CreateObject<Minotaur>("Minotaur", D3DXVECTOR2(26 + 52 * 5, 26 + 52 * 6), D3DXVECTOR2(100.f, 100.f));
	_ObjectPool->CreateObject<RedDragon>("RedDragon", D3DXVECTOR2(26 + 52 * 3, 26 + 52 * 4), D3DXVECTOR2(100.f, 100.f));
	_ObjectPool->CreateObject<GreenDragon>("GreenDragon", D3DXVECTOR2(26 + 52 * 3, 26 + 52 * 5), D3DXVECTOR2(100.f, 100.f));
}
