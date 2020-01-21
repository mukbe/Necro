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
	// TileManager(POINT mapSize, tileSize, 기준좌표)
	// mapSize는 {가로칸수, 세로칸수}
	// tileSize는 D3DXVECTOR2(가로크기, 세로크기)
	// 기준좌표는 D3DXVECTOR2(x좌표, y좌표) -> 여기를 LeftTop 위치로 가정하고 쭈르륵 그려짐

	//타일 검출
	_TileMap->Tile({ 2, 3 }); // 포인트 형태 매개변수 ({2,3})
	_TileMap->Tile(2, 3); // 인트 형태 매개변수 2개 (x,y)

	TileNode* testTile = _TileMap->Tile(0, 0); // 이런식으로 포인터에 넣을 수도 있고.
	_TileMap->Tile(0, 0)->GetPos(); // 물론 멤버 함수도 존재함. 대부분 대충 보면 머하는 함수인지 알듯
	// 멤버 함수 모르겠으면 물어보셈.

	testTile->GetAttribute(); //이건 오브젝트 타입 따오는거. 타입 이넘은 TileHelper.h 참조


	for (int i = 0; i < 8; ++i)
	{
		//5,i 인덱스의 타일을 스태틱타입으로 바꾼다.
		_TileMap->Tile(5, i)->SetAttribute(ObjStatic);
		//5,i 인덱스의 프레임인덱스를 바꾼다.
		_TileMap->Tile(5, i)->SetFrameX(1);
	}

	_ObjectPool->CreateObject<Player>("Player", D3DXVECTOR2(26.f, 26.f), D3DXVECTOR2(52, 52));
	
}
