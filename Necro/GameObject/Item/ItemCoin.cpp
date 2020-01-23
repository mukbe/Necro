#include "stdafx.h"
#include "ItemCoin.h"


ItemCoin::ItemCoin(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:ItemBase(name, pos, size)
{
	bShow = false;
	AddCallback("Merge", [&](TagMessage msg) {
		//게임데이터한테 코인증가량을 전달
	});	
}

ItemCoin::~ItemCoin()
{
}

void ItemCoin::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::Object);
}

void ItemCoin::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::Object);
}

void ItemCoin::Update(float tick)
{
}

void ItemCoin::Render()
{
	_ImageManager->FindTexture("Field_Coin")->FrameRender(rc, nullptr, 0, (UINT)bShow);
}

void ItemCoin::Init(POINT tileIndex)
{
	ItemBase::Init(tileIndex);
}

