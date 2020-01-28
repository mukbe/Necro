#include "stdafx.h"
#include "ItemCoin.h"


ItemCoin::ItemCoin(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:ItemBase(name, pos, size)
{
	bShow = false;
	hasCoin = (UINT)Math::Random(1.f, 7.f);

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

void ItemCoin::EatItem()
{
	//콤보가 있는지
	//_GameData->AddCoin(hasCoin * 콤보배율)
}

