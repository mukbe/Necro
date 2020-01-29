#include "stdafx.h"
#include "ItemShovel.h"


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
}

void ItemShovel::Render()
{
	//_ImageManager->FindTexture("Pickaxe")->FrameRender(rc, nullptr, 0, (UINT)bShow);
	_ImageManager->FindTexture("Shovel")->FrameRender(rc, nullptr, 0, (UINT)bShow);
}

void ItemShovel::Init(POINT tileIndex)
{
	ItemBase::Init(tileIndex);
}

void ItemShovel::EatItem()
{
}
