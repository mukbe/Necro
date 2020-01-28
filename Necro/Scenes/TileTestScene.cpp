#include "stdafx.h"
#include "TileTestScene.h"
#include "TileHelper.h"
#include "TileNode.h"
#include "./GameObject/Player.h"
//�Ϲݸ�
#include "./GameObject/Monster/GreenSlime.h"
#include "./GameObject/Monster/BlueSlime.h"
#include "./GameObject/Monster/Bat.h"
#include "./GameObject/Monster/Skeleton.h"
#include "./GameObject/Monster/Ghost.h"
#include "./GameObject/Monster/Monkey.h"
//������
#include "./GameObject/Monster/Minotaur.h"
#include "./GameObject/Monster/RedDragon.h"
#include "./GameObject/Monster/GreenDragon.h"

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

	
	//����
	MonsterLoad();
	
	
	//�÷��̾�

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

	//����
	_ImageManager->AddFrameTexture("greenslime", ResourcePath + L"Monster/slime_green.png", 4, 2);
	_ImageManager->AddFrameTexture("blueslime", ResourcePath + L"Monster/slime_ice.png", 4, 2);
	_ImageManager->AddFrameTexture("bat", ResourcePath + L"Monster/bat.png", 4, 2);
	_ImageManager->AddFrameTexture("skeleton", ResourcePath + L"Monster/skeleton.png", 8, 2);
	_ImageManager->AddFrameTexture("ghost", ResourcePath + L"Monster/ghost.png", 2, 2);
	_ImageManager->AddFrameTexture("monkey", ResourcePath + L"Monster/monkey.png", 6, 2);
	_ImageManager->AddFrameTexture("minotaur", ResourcePath + L"Monster/minotaur.png", 9, 2);
	_ImageManager->AddFrameTexture("reddragon", ResourcePath + L"Monster/dragon_red.png", 7, 2);
	_ImageManager->AddFrameTexture("greendragon", ResourcePath + L"Monster/dragon_green.png", 2, 2);
}

void TileTestScene::MonsterLoad()
{
	_ObjectPool->CreateObject<GreenSlime>("GreenSlime", D3DXVECTOR2(26, 52), D3DXVECTOR2(52.f, 52.f));
	_ObjectPool->CreateObject<BlueSlime>("BlueSlime", D3DXVECTOR2(26 + 52, 26 + 52), D3DXVECTOR2(52.f, 52.f));
	_ObjectPool->CreateObject<BlueSlime>("BlueSlime", D3DXVECTOR2(130.f, 78.f), D3DXVECTOR2(52.f, 52.f));
	_ObjectPool->CreateObject<Bat>("Bat", D3DXVECTOR2(26 + 52 , 26 + 52 *6), D3DXVECTOR2(52.f, 52.f));
	_ObjectPool->CreateObject<Skeleton>("Skeleton", D3DXVECTOR2(26 + 52 , 26 + 52 * 8), D3DXVECTOR2(52.f, 52.f));
	_ObjectPool->CreateObject<Ghost>("Ghost", D3DXVECTOR2(26 + 52*4, 26 + 52 * 8), D3DXVECTOR2(52.f, 52.f));
	_ObjectPool->CreateObject<Monkey>("Monkey", D3DXVECTOR2(26 + 52 * 5, 26 + 52 * 5), D3DXVECTOR2(52.f, 52.f));
	_ObjectPool->CreateObject<Minotaur>("Minotaur", D3DXVECTOR2(26 + 52 * 5, 26 + 52 * 6), D3DXVECTOR2(100.f, 100.f));
	_ObjectPool->CreateObject<RedDragon>("RedDragon", D3DXVECTOR2(26 + 52 * 3, 26 + 52 * 4), D3DXVECTOR2(100.f, 100.f));
	_ObjectPool->CreateObject<GreenDragon>("GreenDragon", D3DXVECTOR2(26 + 52 * 3, 26 + 52 * 5), D3DXVECTOR2(100.f, 100.f));
}


