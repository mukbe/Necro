#include "stdafx.h"
#include "ItemDiamond.h"
#include "./GameObject/UI/UIBase.h"
#include "./GameObject/Map/TileNode.h"

ItemDiamond::ItemDiamond(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:ItemBase(name,pos,size)
{
	bShow = false;
	hasDia = 1;
	itemKey = name;
	int temp = Math::Clamp(hasDia, 0, 3);
	itemKey += to_string(temp);
	itemTex = _ImageManager->FindTexture("ItemDiamond");
}

ItemDiamond::~ItemDiamond()
{
}

void ItemDiamond::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::Object);
}

void ItemDiamond::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::Object);
}

void ItemDiamond::Update(float tick)
{
	if (Keyboard::Get()->Down('G'))
		EatItem();
}

void ItemDiamond::Render()
{
	if (itemTex)
		itemTex->FrameRender(rc, nullptr, (UINT)bShow);

}

void ItemDiamond::Init(POINT tileIndex)
{
	ItemBase::Init(tileIndex);
}

void ItemDiamond::EatItem()
{
	_GameData->AddDia(hasDia);

	POINT myIndex = PosToIndex(position, TileManager::tileSize, TileManager::pivotPos);

	TileNode* tempTile = _TileMap->Tile(myIndex.x, myIndex.y);
	tempTile->DeleteObject(ObjectItem, this);

	GameObject* ui = _ObjectPool->FindObject<UIBase>("Diamond");
	_MessagePool->ReserveMessage(ui, "EatItem", 0.f, itemKey);
	_MessagePool->ReserveMessage(ui, "CurrentPosition", 0.f, position);

	_ObjectPool->DeletaObject(this);
	_GameData->AddDia(hasDia);

}

void ItemDiamond::Show()
{
}

void ItemDiamond::Hide()
{
}

void ItemDiamond::Active()
{
}
