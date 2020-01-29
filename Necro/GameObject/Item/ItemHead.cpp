#include "stdafx.h"
#include "ItemHead.h"


ItemHead::ItemHead(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:ItemBase(name, pos, size)
{
	bShow = false;
	
}

ItemHead::~ItemHead()
{
}

void ItemHead::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::Object);
}

void ItemHead::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::Object);
}

void ItemHead::Update(float tick)
{
}

void ItemHead::Render()
{
	_ImageManager->FindTexture("Head_Cap")->FrameRender(rc, nullptr, 0, (UINT)bShow);
}

void ItemHead::Init(POINT tileIndex)
{
	ItemBase::Init(tileIndex);
}

void ItemHead::EatItem()
{
}
