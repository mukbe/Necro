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

	// Item
	_ImageManager->AddFrameTexture("Shovel", ResourcePath + L"Item/Shovel.png", 1, 2);
	_ImageManager->AddFrameTexture("Dagger", ResourcePath + L"Item/Dagger.png", 1, 2);
	_ImageManager->AddFrameTexture("Broadsword", ResourcePath + L"Item/Broadsword.png", 1, 2);
	_ImageManager->AddFrameTexture("Spear", ResourcePath + L"Item/Spear.png", 1, 2);
	_ImageManager->AddFrameTexture("Dia1", ResourcePath + L"Item/Field_Dia.png", 1, 2);
	_ImageManager->AddFrameTexture("Dia2", ResourcePath + L"Item/Field_Dia2.png", 1, 2);

	// 몬스터
	_ImageManager->AddFrameTexture("greenslime", ResourcePath + L"Monster/slime_green.png", 4, 4);
	_ImageManager->AddFrameTexture("blueslime", ResourcePath + L"Monster/slime_blue.png", 4, 4);
	_ImageManager->AddFrameTexture("bat", ResourcePath + L"Monster/bat.png", 4, 4);
	_ImageManager->AddFrameTexture("skeleton", ResourcePath + L"Monster/skeleton.png", 16, 4);
	_ImageManager->AddFrameTexture("ghost", ResourcePath + L"Monster/ghost.png", 2, 4);
	_ImageManager->AddFrameTexture("monkey", ResourcePath + L"Monster/monkey.png", 6, 4);
	_ImageManager->AddFrameTexture("minotaur", ResourcePath + L"Monster/minotaur.png", 9, 4);
	_ImageManager->AddFrameTexture("reddragon", ResourcePath + L"Monster/dragon_red.png", 9, 4);
	_ImageManager->AddFrameTexture("greendragon", ResourcePath + L"Monster/dragon_green.png", 4, 4);


	//Tool
	_ImageManager->AddTexture("ToolPlayer", ResourcePath + L"MapTool/ToolPlayer.png");

	_ImageManager->AddTexture("ToolBat", ResourcePath + L"MapTool/ToolBat.png");
	_ImageManager->AddTexture("ToolBlueSlime", ResourcePath + L"MapTool/ToolBlueSlime.png");
	_ImageManager->AddTexture("ToolGreenSlime", ResourcePath + L"MapTool/ToolGreenSlime.png");
	_ImageManager->AddTexture("ToolSkeleton", ResourcePath + L"MapTool/ToolSkeleton.png");

	_ImageManager->AddTexture("ToolWallBase", ResourcePath + L"MapTool/ToolWallBase.png");
	_ImageManager->AddTexture("ToolStoneWall", ResourcePath + L"MapTool/ToolStoneWall.png");
}
