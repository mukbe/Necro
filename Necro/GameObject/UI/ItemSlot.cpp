#include "stdafx.h"
#include "ItemSlot.h"



ItemSlot::ItemSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	
}


ItemSlot::~ItemSlot()
{
}

void ItemSlot::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
	_ImageManager->AddTexture("UI_ItemlSlot", ResourcePath + L"UI/UI_ItemSlot.png");
}

void ItemSlot::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);
}

void ItemSlot::ControlUpdate()
{
}

void ItemSlot::Update(float tick)
{
}

void ItemSlot::Render()
{
	_ImageManager->Render("UI_ItemlSlot", rc, nullptr);
}
