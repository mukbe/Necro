#include "stdafx.h"
#include "ItemShovel.h"
#include "./GameObject/Map/TileNode.h"
#include "./GameObject/UI/ShovelSlot.h"


ItemShovel::ItemShovel(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:ItemBase(name,pos,size)
{
	bShow = false;
	
}

ItemShovel::~ItemShovel()
{
}

void ItemShovel::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::Object);
}

void ItemShovel::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::Object);
}


void ItemShovel::Update(float tick)
{
	if (Keyboard::Get()->Down('G'))
		EatItem();
}

void ItemShovel::Render()
{
	if (info.Imagekey == "") return;
	_ImageManager->FindTexture(info.Imagekey)->FrameRender(rc, nullptr, 0, (UINT)bShow);
}


void ItemShovel::EatItem()
{
	_GameData->SetShovelData(info);
	POINT myIndex = PosToIndex(position, TileManager::tileSize, TileManager::pivotPos);

	TileNode* tempTile = _TileMap->Tile(myIndex.x, myIndex.y);
	tempTile->DeleteObject(ObjectItem, this);

	_ObjectPool->DeletaObject(this);

	GameObject* UI = _ObjectPool->FindObject<UIBase>("UI_ShovelSlot");
	_MessagePool->ReserveMessage(UI, "EatItem", 0.f, info.Imagekey);
	_MessagePool->ReserveMessage(UI, "CurrentPos", 0.f, position);


}

void ItemShovel::Init(POINT tileIndex)
{
	ItemBase::Init(tileIndex);
}

