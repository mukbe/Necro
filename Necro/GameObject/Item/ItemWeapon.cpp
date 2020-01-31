#include "stdafx.h"
#include "ItemWeapon.h"
#include "./GameObject/Map/TileNode.h"

class TileNode;

ItemWeapon::ItemWeapon(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:ItemBase(name, pos, size)
{
	bShow = false;  // 아이템 보여지는거 
	bDrop = false;	// 아이템 주웠을 때 

}

ItemWeapon::~ItemWeapon()
{
}

void ItemWeapon::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::Object);
	
}

void ItemWeapon::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::Object);
}

void ItemWeapon::ControlUpdate()
{
}

void ItemWeapon::Update()
{
}

void ItemWeapon::Render()
{
	
	if (textureKey == "")return;
	_ImageManager->FindTexture(textureKey)->FrameRender(rc, nullptr, 0, (UINT)bShow);

	_ImageManager->FindTexture("Dagger")->FrameRender(rc, nullptr, 0, (UINT)bShow);

	//Log_ErrorAssert(info.Imagekey == "");
}

void ItemWeapon::EatItem()
{
	info.Type = myType;
	switch (myType)
	{
	case Dagger:
		_GameWorld->GetGameData()->setWeaponData(Dagger, { 0,1 }, 0, "DaggerEffect");
		break;
	case Spear:
		_GameWorld->GetGameData()->setWeaponData(Spear, { 0, 2 }, 0, "SpearEffect");
		break;
	case Broadsword:
		_GameWorld->GetGameData()->setWeaponData(Broadsword, { 3, 1 }, 0, "BroadswordEffect");
		break;
	}
	//										 타일 매니저
	D3DXVECTOR2 tempTileSize = _GameWorld->GetTileManager()->GetTileSize();
	D3DXVECTOR2 tempPivotPos = _GameWorld->GetTileManager()->GetPivotPos();
	POINT myIndex = PosToIndex(position, tempTileSize, tempPivotPos);

	TileNode* tempTile = _GameWorld->GetTileManager()->Tile(myIndex.x, myIndex.y);
	tempTile->DeleteObject(ObjectItem, this);

	_RenderPool->Remove(this, RenderManager::Layer::Object);	// 플레이어가 닿은 이미지는 먹은 걸로 설정을 하고  그 설정했던걸 지움
	_RenderPool->Request(this, RenderManager::Layer::UI);		// 아이템을 먹었을때 따로 지우지는않고 덮어 씌우는걸로 ! 
	//ui로 이동시켜주는 코드 넣어 

}

void ItemWeapon::Init(POINT tileIndex)
{
	ItemBase::Init(tileIndex);
}
