#include "stdafx.h"
#include "ItemDiamond.h"



ItemDiamond::ItemDiamond(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:ItemBase(name,pos,size)
{
	bShow = false;
	AddCallback("SendDiaDate", [&](TagMessage msg)
	{
		//플레이어가 다이아가 있는 타일에 왔을 때 다이아 + 1
	});

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
}

void ItemDiamond::Render()
{
	
	_ImageManager->FindTexture("Dia")->FrameRender(rc,nullptr, (UINT)bShow);
	_ImageManager->FindTexture("Dia2")->FrameRender(rc, nullptr, (UINT)bShow);
}

void ItemDiamond::Init(POINT tileIndex)
{
	ItemBase::Init(tileIndex);
}
