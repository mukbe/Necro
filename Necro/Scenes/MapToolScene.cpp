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
	_ImageManager->AddTexture("GravelWallFine", ResourcePath + L"Wall/GravelWallFine.png");
	_ImageManager->AddTexture("GravelWallDamaged", ResourcePath + L"Wall/GravelWallDamaged.png");
	_ImageManager->AddTexture("GoldWallFine", ResourcePath + L"Wall/GoldWallFine.png");
	_ImageManager->AddTexture("GoldWallDamaged", ResourcePath + L"Wall/GoldWallDamaged.png");
	_ImageManager->AddTexture("Door", ResourcePath + L"Stuff/Door.png");
	_ImageManager->AddTexture("DoorVertical", ResourcePath + L"Stuff/DoorVertical.png");
	_ImageManager->AddTexture("Stairs", ResourcePath + L"Stuff/Stairs.png");
	_ImageManager->AddTexture("BlackWall", ResourcePath + L"Wall/BlackWall.png");
	SOUNDMANAGER->AddSound("Dig", "../_Resources/Sound/Dig.Ogg", false, false);
	SOUNDMANAGER->AddSound("DigFail", "../_Resources/Sound/DigFail.Ogg", false, false);
	SOUNDMANAGER->AddSound("DoorOpen", "../_Resources/Sound/DoorOpen.Ogg", false, false);

	// Effect
	_ImageManager->AddTexture("EffectShovel", ResourcePath + L"Effect/Shovel.png");
	wstring temp = ResourcePath + L"Effect/Shovel.png";
	string temp1;
	temp1.assign(temp.begin(), temp.end());
	EFFECTS->AddEffect("EffectShovel", "EffectShovel");
	_ImageManager->AddFrameTexture("Swipe_Dagger", ResourcePath + L"Effect/Swipe_Dagger.png", 3, 1);
	_ImageManager->AddFrameTexture("Swipe_Spear", ResourcePath + L"Effect/Swipe_Spear.png", 6, 1);
	_ImageManager->AddFrameTexture("Swipe_Broadsword", ResourcePath + L"Effect/Swipe_Broadsword.png", 3, 1);
	_ImageManager->AddFrameTexture("Playerhit", ResourcePath + L"Effect/Playerhit.png", 5, 1);


	// Item
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
	_ImageManager->AddTexture("ToolShopKeeper", ResourcePath + L"MapTool/ToolShopKeeper.png");

	_ImageManager->AddTexture("ToolBat", ResourcePath + L"MapTool/ToolBat.png");
	_ImageManager->AddTexture("ToolBlueSlime", ResourcePath + L"MapTool/ToolBlueSlime.png");
	_ImageManager->AddTexture("ToolGreenSlime", ResourcePath + L"MapTool/ToolGreenSlime.png");
	_ImageManager->AddTexture("ToolSkeleton", ResourcePath + L"MapTool/ToolSkeleton.png");

	_ImageManager->AddTexture("ToolWallBase", ResourcePath + L"MapTool/ToolWallBase.png");
	_ImageManager->AddTexture("ToolStoneWall", ResourcePath + L"MapTool/ToolStoneWall.png");
	_ImageManager->AddTexture("ToolGravelWall", ResourcePath + L"MapTool/ToolGravelWall.png");
	_ImageManager->AddTexture("ToolGoldWall", ResourcePath + L"MapTool/ToolGoldWall.png");
	_ImageManager->AddTexture("ToolDoor", ResourcePath + L"MapTool/ToolDoor.png");
	_ImageManager->AddTexture("ToolDoorVertical", ResourcePath + L"MapTool/ToolDoorVertical.png");

	_ImageManager->AddTexture("ToolItemWeaponDagger", ResourcePath + L"MapTool/ToolItemWeaponDagger.png");
	_ImageManager->AddTexture("ToolItemWeaponBroadSword", ResourcePath + L"MapTool/ToolItemWeaponBroadSword.png");
	_ImageManager->AddTexture("ToolItemWeaponSpear", ResourcePath + L"MapTool/ToolItemWeaponSpear.png");
	_ImageManager->AddTexture("ToolItemShovelShovel", ResourcePath + L"MapTool/ToolItemShovelShovel.png");
	_ImageManager->AddTexture("ToolItemShovelPickaxe", ResourcePath + L"MapTool/ToolItemShovelPPickaxe.png");
	_ImageManager->AddTexture("ToolDiamond", ResourcePath + L"MapTool/ToolDiamond.png");

	//Font
	_ImageManager->AddFrameTexture("NumberFontUI", ResourcePath + L"Font/NumberFontUI.png", 10, 1);
	_ImageManager->AddTexture("UI_x", ResourcePath + L"Font/UI_x.png");
}
