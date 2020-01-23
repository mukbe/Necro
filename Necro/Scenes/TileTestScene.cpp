#include "stdafx.h"
#include "TileTestScene.h"
#include "TileHelper.h"
#include "TileNode.h"
#include "./GameObject/Player.h"
#include "./GameObject/Monster/GreenSlime.h"
#include "./GameObject/Monster/BlueSlime.h"
#include "./GameObject/Monster/Bat.h"
#include "./GameObject/UI/Heart.h"
#include "./GameObject/UI/Note.h"

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

	// TileManager(POINT mapSize, tileSize, ������ǥ)
	// mapSize�� {����ĭ��, ����ĭ��}
	// tileSize�� D3DXVECTOR2(����ũ��, ����ũ��)
	// ������ǥ�� D3DXVECTOR2(x��ǥ, y��ǥ) -> ���⸦ LeftTop ��ġ�� �����ϰ� �޸��� �׷���
	//testTileManager = new TileManager({ 30,30 }, D3DXVECTOR2(52.f, 52.f), D3DXVECTOR2(13.f, 13.f));

	//Ÿ�� ����
	//testTileManager->Tile({ 2, 3 }); // ����Ʈ ���� �Ű����� ({2,3})
	//testTileManager->Tile(2, 3); // ��Ʈ ���� �Ű����� 2�� (x,y)

	//TileNode* testTile = testTileManager->Tile(0, 0); // �̷������� �����Ϳ� ���� ���� �ְ�.
	//testTileManager->Tile(0, 0)->GetPos(); // ���� ��� �Լ��� ������. ��κ� ���� ���� ���ϴ� �Լ����� �˵�
	// ��� �Լ� �𸣰����� �����.


	//testTile->GetAttribute(); //�̰� ������Ʈ Ÿ�� �����°�. Ÿ�� �̳��� TileHelper.h ����


	_TileMap->SetMapInfo({ 10, 10 }, defaultTileSize, D3DXVECTOR2(defaultTileSize.x / 2.f, defaultTileSize.y / 2.f));


	for (int i = 0; i < 8; ++i)
	{
		_TileMap->Tile(5, i)->SetAttribute(ObjStatic);
		_TileMap->Tile(5, i)->SetFrameX(1);
		//5,i �ε����� Ÿ���� ����ƽŸ������ �ٲ۴�.
		//testTileManager->Tile(5, i)->SetAttribute(ObjStatic);
		//5,i �ε����� �������ε����� �ٲ۴�.
		//testTileManager->Tile(5, i)->SetFrameX(1);
	}

	//_ObjectPool->CreateObject<Player>("Player", D3DXVECTOR2(26.f, 26.f), D3DXVECTOR2(52, 52));
	




	////����
	//_ImageManager->AddFrameTexture("greenslime", ResourcePath + L"slime_green.png", 4, 2);
	//_ImageManager->AddFrameTexture("blueslime", ResourcePath + L"slime_ice.png", 4, 2);
	//_ImageManager->AddFrameTexture("bat", ResourcePath + L"bat.png", 4, 2);
	//
	//GreenSlime* greenslime = _ObjectPool->CreateObject<GreenSlime>("GreenSlime", D3DXVECTOR2(FIRSTCENTERXY, FIRSTCENTERXY), D3DXVECTOR2(52.f, 52.f));
	//BlueSlime* blueslime = _ObjectPool->CreateObject<BlueSlime>("BlueSlime", D3DXVECTOR2(FIRSTCENTERXY+TILESIZE, FIRSTCENTERXY + TILESIZE), D3DXVECTOR2(52.f, 52.f));
	//BlueSlime* blueslime2 = _ObjectPool->CreateObject<BlueSlime>("BlueSlime", D3DXVECTOR2(130.f, 78.f), D3DXVECTOR2(52.f, 52.f));
	//Bat* bat = _ObjectPool->CreateObject<Bat>("Bat", D3DXVECTOR2(FIRSTCENTERXY + TILESIZE*8, FIRSTCENTERXY + TILESIZE * 8), D3DXVECTOR2(52.f, 52.f));
	//
	_ObjectPool->CreateObject<Player>("Player", D3DXVECTOR2(26, 26), D3DXVECTOR2(52.f, 52.f));


	beatManager->LoadText(ResourcePath + L"Music/stage1.txt");
	wstring path = ResourcePath + L"Music/stage1.ogg";
	SOUNDMANAGER->AddSound("stage1", String::WStringToString(path), true, false);
}

void TileTestScene::ImageLoad()
{
	_ImageManager->AddFrameTexture("HeartTemp", ResourcePath + L"UI/TempHeart.png", 2, 1);


	_ImageManager->AddFrameTexture("PlayerHeadRight", ResourcePath + L"Player/PlayerHeadRight.png", 4, 2);
	_ImageManager->AddFrameTexture("PlayerBodyRight", ResourcePath + L"Player/PlayerBodyRight.png", 4, 10);
	_ImageManager->AddFrameTexture("PlayerHeadLeft", ResourcePath + L"Player/PlayerHeadLeft.png", 4, 2);
	_ImageManager->AddFrameTexture("PlayerBodyLeft", ResourcePath + L"Player/PlayerBodyLeft.png", 4, 10);
	_ImageManager->AddTexture("PlayerShadow", ResourcePath + L"Player/PlayerShadow.png");
	_ImageManager->AddTexture("NoteBeat", ResourcePath + L"UI/basicbeat.png");
}
