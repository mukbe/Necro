#include "stdafx.h"
#include "MapToolScene.h"

MapToolScene::MapToolScene()
	: SceneBase()
{	
}

MapToolScene::~MapToolScene()
{
}

void MapToolScene::Init()
{
	SceneBase::Init();

	LoadResource();
	tool = _ObjectPool->CreateObject<MapTool>("MapTool", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));

}

void MapToolScene::LoadResource()
{
	_ImageManager->AddFrameTexture("DefaultMap", ResourcePath + L"DefaultTileMap.png", 2, 2);
	_ImageManager->AddFrameTexture("greenslime", ResourcePath + L"slime_green.png", 4, 2);
	_ImageManager->AddFrameTexture("blueslime", ResourcePath + L"slime_ice.png", 4, 2);
	_ImageManager->AddFrameTexture("bat", ResourcePath + L"bat.png", 4, 2);
	_ImageManager->AddFrameTexture("PlayerHeadRight", ResourcePath + L"Player/PlayerHeadRight.png", 4, 2);
	_ImageManager->AddFrameTexture("PlayerBodyRight", ResourcePath + L"Player/PlayerBodyRight.png", 4, 10);
	_ImageManager->AddFrameTexture("PlayerHeadLeft", ResourcePath + L"Player/PlayerHeadLeft.png", 4, 2);
	_ImageManager->AddFrameTexture("PlayerBodyLeft", ResourcePath + L"Player/PlayerBodyLeft.png", 4, 10);
	_ImageManager->AddTexture("PlayerShadow", ResourcePath + L"Player/PlayerShadow.png");
}
