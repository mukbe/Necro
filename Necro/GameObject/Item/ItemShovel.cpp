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
	//_ImageManager->FindTexture("Shovel")->FrameRender(rc.Update(D3DXVECTOR2(52.f,42.f),TileManager::tileSize * 0.85f,Pivot::CENTER), nullptr, 0, (UINT)bShow);
	// _ImageManager->FindTexture("EffectShovel")->Render(FloatRect(this->Transform().GetPos(), 52.f, Pivot::CENTER), NULL);
	_ImageManager->FindTexture("Shovel")->FrameRender(rc, nullptr, 0, (UINT)bShow);



	//_ImageManager->FindTexture("Shovel")->FrameRender(FloatRectr (this->Transform, 60.f, Pivot::CENTER), NULL);
}

void ItemShovel::Init(POINT tileIndex)
{
	ItemBase::Init(tileIndex);
}

void ItemShovel::EatItem()
{
	//아이템 속성 
}
