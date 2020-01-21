#include "stdafx.h"
#include "TileTestScene.h"
#include "TileHelper.h"
#include "TileNode.h"
#include "./GameObject/Player.h"

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
	// TileManager(POINT mapSize, tileSize, ������ǥ)
	// mapSize�� {����ĭ��, ����ĭ��}
	// tileSize�� D3DXVECTOR2(����ũ��, ����ũ��)
	// ������ǥ�� D3DXVECTOR2(x��ǥ, y��ǥ) -> ���⸦ LeftTop ��ġ�� �����ϰ� �޸��� �׷���

	//Ÿ�� ����
	_TileMap->Tile({ 2, 3 }); // ����Ʈ ���� �Ű����� ({2,3})
	_TileMap->Tile(2, 3); // ��Ʈ ���� �Ű����� 2�� (x,y)

	TileNode* testTile = _TileMap->Tile(0, 0); // �̷������� �����Ϳ� ���� ���� �ְ�.
	_TileMap->Tile(0, 0)->GetPos(); // ���� ��� �Լ��� ������. ��κ� ���� ���� ���ϴ� �Լ����� �˵�
	// ��� �Լ� �𸣰����� �����.

	testTile->GetAttribute(); //�̰� ������Ʈ Ÿ�� �����°�. Ÿ�� �̳��� TileHelper.h ����


	for (int i = 0; i < 8; ++i)
	{
		//5,i �ε����� Ÿ���� ����ƽŸ������ �ٲ۴�.
		_TileMap->Tile(5, i)->SetAttribute(ObjStatic);
		//5,i �ε����� �������ε����� �ٲ۴�.
		_TileMap->Tile(5, i)->SetFrameX(1);
	}

	_ObjectPool->CreateObject<Player>("Player", D3DXVECTOR2(26.f, 26.f), D3DXVECTOR2(52, 52));
	
}
