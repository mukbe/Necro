#include "stdafx.h"
#include "ItemCoin.h"

//코인 같은 경우에는 몬스터한테 랜덤으로 나옴 . 

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
	_ImageManager->FindTexture("Field_Coin")->FrameRender(rc, nullptr, hasCoin > 3 ? 0 : 1, (UINT)bShow);
}

void ItemCoin::Init(POINT tileIndex)
{
	ItemBase::Init(tileIndex);
}

void ItemCoin::EatItem()
{
	_GameData->AddCoin(hasCoin);
	_ObjectPool->DeletaObject(this);
}

