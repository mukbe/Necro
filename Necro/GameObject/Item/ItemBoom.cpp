#include "stdafx.h"
#include "ItemBoom.h"

ItemBoom::ItemBoom(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:ItemBase(name,pos,size)
{
	bShow = false;
}

ItemBoom::~ItemBoom()
{
}

void ItemBoom::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::Object);
}

void ItemBoom::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::Object);
}

void ItemBoom::ControlUpdate()
{
	// 폭탄 사용시 커맨드 해야 할 수 있으니까 일단 함수 남겨놓고 , 
}

void ItemBoom::Update(float tick)
{
}

void ItemBoom::Render()
{
	//폭탄 이미지 
}

void ItemBoom::EatItem()
{
}

void ItemBoom::Init(POINT tileIndex)
{
	ItemBase::Init(tileIndex);
}

