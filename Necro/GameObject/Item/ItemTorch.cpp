#include "stdafx.h"
#include "ItemTorch.h"
#include "./GameObject/Map/TileNode.h"
#include "./GameObject/UI/TorchSlot.h"


ItemTorch::ItemTorch(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	: ItemBase (name,pos,size)
{
	bShow = false;
	GameData::TorchInfo temp;
	temp.ImageKey = "Torch";
	SetItemData(temp);


}

ItemTorch::~ItemTorch()
{
}

void ItemTorch::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::Object);
}

void ItemTorch::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::Object);
}

void ItemTorch::Update(float tick)
{
	if (Keyboard::Get()->Down('G'))
	{
		_MessagePool->ReserveMessage(this, "EatItem");
	}
}

void ItemTorch::Render()
{
	ItemBase::Render();
	
	if (info.ImageKey == "") return;
	_ImageManager->FindTexture(info.ImageKey)->FrameRender(rc, nullptr, 0, (UINT)bShow);

	//_ImageManager->FindTexture("Torch")->FrameRender(rc, nullptr, 1, (UINT)bShow);
}


void ItemTorch::EatItem()
{
	_GameData->MinusCoin(cost);

	_GameData->SetTorchData(info);
	POINT myIndex = PosToIndex(position, TileManager::tileSize, TileManager::pivotPos);

	TileNode* tempTile = _TileMap->Tile(myIndex.x, myIndex.y);
	tempTile->DeleteObject(ObjectItem, this);

	_ObjectPool->DeletaObject(this);

	GameObject* Torch = _ObjectPool->FindObject<UIBase>("UI_TorchSlot");
	_MessagePool->ReserveMessage(Torch, "EatItem", 0.f, info.ImageKey);
	_MessagePool->ReserveMessage(Torch, "CurrentPosition", 0.f, position);
}

void ItemTorch::Init(POINT tileIndex)
{
	ItemBase::Init(tileIndex);
}