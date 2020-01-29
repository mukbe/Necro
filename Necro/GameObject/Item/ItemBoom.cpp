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
	// ��ź ���� Ŀ�ǵ� �ؾ� �� �� �����ϱ� �ϴ� �Լ� ���ܳ��� , 
}

void ItemBoom::Update(float tick)
{
}

void ItemBoom::Render()
{
	//��ź �̹��� 
}

void ItemBoom::EatItem()
{
}

void ItemBoom::Init(POINT tileIndex)
{
	ItemBase::Init(tileIndex);
}

