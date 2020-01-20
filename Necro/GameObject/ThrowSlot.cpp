#include "stdafx.h"
#include "ThrowSlot.h"



ThrowSlot::ThrowSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	isInPut = false;
	_ImageManager->AddTexture("UI_ThrowSlot", ResourcePath + L"UI/Throw_Slot.png");
	_ImageManager->AddTexture("UI_ThrowWaitSlot", ResourcePath + L"UI/Throw_Slot2.png");
}


ThrowSlot::~ThrowSlot()
{
}

void ThrowSlot::Release()
{
}

void ThrowSlot::ControlUpdate()
{
}

void ThrowSlot::Update(float tick)
{
}

void ThrowSlot::Render()
{
	_ImageManager->Render("UI_ThrowSlot", FloatRect({ 70,260 }, { 75,75 }, Pivot::CENTER), nullptr);
}
