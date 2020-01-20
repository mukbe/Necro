#include "stdafx.h"
#include "TileTestScene.h"
#include "./GameObject/UIBase.h"
#include "TileHelper.h"
#include "TileNode.h"

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
	testTileManager = new TileManager(defaultMapSize, defaultTileSize, D3DXVECTOR2(0.f, 0.f));


	//Ÿ�� ����
	testTileManager->Tile({ 2, 3 }); // ����Ʈ ���� �Ű����� ({2,3})
	testTileManager->Tile(2, 3); // ��Ʈ ���� �Ű����� 2�� (x,y)

	TileNode* testTile = testTileManager->Tile(0, 0); // �̷������� �����Ϳ� ���� ���� �ְ�.
	testTileManager->Tile(0, 0)->GetPos(); // ���� ��� �Լ��� ������. ��κ� ���� ���� ���ϴ� �Լ����� �˵�
	// ��� �Լ� �𸣰����� �����.

	testTile->GetAttribute(); //�̰� ������Ʈ Ÿ�� �����°�. Ÿ�� �̳��� TileHelper.h ����

	for (int i = 0; i < 8; ++i)
	{
		//5,i �ε����� Ÿ���� ����ƽŸ������ �ٲ۴�.
		testTileManager->Tile(5, i)->SetAttribute(ObjStatic);
		//5,i �ε����� �������ε����� �ٲ۴�.
		testTileManager->Tile(5, i)->SetFrameX(1);
	}
}
