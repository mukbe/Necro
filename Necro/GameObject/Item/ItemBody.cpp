#include "stdafx.h"
#include "ItemBody.h"


ItemBody::ItemBody(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:ItemBase(name,pos,size)
{
	bShow = false;
	AddCallback("SendBodyDate", [&](TagMessage msg)
	{
		
	});
}

ItemBody::~ItemBody()
{
}

void ItemBody::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::Object);
}

void ItemBody::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::Object);
}

void ItemBody::Update(float tick)
{
	
}

void ItemBody::Render()
{
	_ImageManager->FindTexture("Leather_Armor")->FrameRender(rc, nullptr, 0, (UINT)bShow);
}

void ItemBody::Init(POINT tileIndex)
{
	ItemBase::Init(tileIndex);
	
}

void ItemBody::EatItem()
{
}
