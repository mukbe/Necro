#include "stdafx.h"
#include "ItemTorch.h"
#include "./GameObject/Map/TileNode.h"
#include "./GameObject/UI/TorchSlot.h"


ItemTorch::ItemTorch(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	: ItemBase (name,pos,size)
{
	bShow = false;

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
}

void ItemTorch::Render()
{
	_ImageManager->FindTexture("Torch")->FrameRender(rc, nullptr, 1, (UINT)bShow);
}

void ItemTorch::Init(POINT tileIndex)
{
	ItemBase::Init(tileIndex);
}

void ItemTorch::EatItem()
{
}
