#include "stdafx.h"
#include "ItemSlot.h"



ItemSlot::ItemSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	_ImageManager->AddTexture("UI_ItemlSlot", ResourcePath + L"UI/Item_Slot.png");
}


ItemSlot::~ItemSlot()
{
}

void ItemSlot::Release()
{
}

void ItemSlot::ControlUpdate()
{
}

void ItemSlot::Update(float tick)
{
}

void ItemSlot::Render()
{
	_ImageManager->Render("UI_ItemlSlot", FloatRect({ 70,170 }, { 75,75 }, Pivot::CENTER), nullptr);
}
