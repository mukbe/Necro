#include "stdafx.h"
#include "HeadSlot.h"
#include "UIBase.h"


HeadSlot::HeadSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	_ImageManager->AddTexture("UI_HeadSlot", ResourcePath + L"UI/Head_Slot.png");
}


HeadSlot::~HeadSlot()
{
}

void HeadSlot::Release()
{
}

void HeadSlot::ControlUpdate()
{
}

void HeadSlot::Update(float tick)
{
}

void HeadSlot::Render()
{
	_ImageManager->Render("UI_HeadSlot", FloatRect({ 390,75}, { 75,75}, Pivot::CENTER), nullptr);
}
