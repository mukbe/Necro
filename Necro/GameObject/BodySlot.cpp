#include "stdafx.h"
#include "BodySlot.h"
#include "UIBase.h"



BodySlot::BodySlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	_ImageManager->AddTexture("UI_BodySlot", ResourcePath + L"UI/Body_Slot.png");
}


BodySlot::~BodySlot()
{
}

void BodySlot::Release()
{
}

void BodySlot::ControlUpdate()
{
}

void BodySlot::Update(float tick)
{
}

void BodySlot::Render()
{
	_ImageManager->Render("UI_BodySlot", FloatRect({ 310,75}, { 75,75}, Pivot::CENTER), nullptr);
}
