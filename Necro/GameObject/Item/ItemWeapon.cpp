#include "stdafx.h"
#include "ItemWeapon.h"
#include "./GameObject/Map/TileNode.h"
#include "./GameObject/UI/AttackSlot.h"

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

void ItemWeapon::Update(float tick)
{
	if (Keyboard::Get()->Down('G'))
		EatItem();
}

void ItemWeapon::Render()
{
	
	if (info.Imagekey == "") return;
	_ImageManager->FindTexture(info.Imagekey)->FrameRender(rc, nullptr, 0, (UINT)bShow);


	//Log_ErrorAssert(info.Imagekey == "");
}

void ItemWeapon::EatItem()
{
	_GameData->SetWeaponData(info);
	POINT myIndex = PosToIndex(position, TileManager::tileSize, TileManager::pivotPos);

	TileNode* tempTile = _TileMap->Tile(myIndex.x, myIndex.y);
	tempTile->DeleteObject(ObjectItem, this);

	_ObjectPool->DeletaObject(this);

	GameObject* ui = _ObjectPool->FindObject<UIBase>("UI_AttackSlot");
	_MessagePool->ReserveMessage(ui, "EatItem", 0.f, info.Imagekey);
	_MessagePool->ReserveMessage(ui, "CurrentPosition", 0.f, position);
}

void ItemWeapon::Init(POINT tileIndex)
{
	ItemBase::Init(tileIndex);
}
