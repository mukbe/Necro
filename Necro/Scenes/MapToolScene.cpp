#include "stdafx.h"
#include "MapToolScene.h"

MapToolScene::MapToolScene()
	: SceneBase()
{
	_ImageManager->AddFrameTexture("DefaultMap", ResourcePath + L"DefaultTileMap.png", 2, 2);
	_ImageManager->AddFrameTexture("greenslime", ResourcePath + L"slime_green.png", 4, 2);
	_ImageManager->AddFrameTexture("blueslime", ResourcePath + L"slime_ice.png", 4, 2);
	_ImageManager->AddFrameTexture("bat", ResourcePath + L"bat.png", 4, 2);


}

MapToolScene::~MapToolScene()
{
}

void MapToolScene::Init()
{
	SceneBase::Init();

	
	tool = _ObjectPool->CreateObject<MapTool>("MapTool", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));
	
}
