#include "stdafx.h"
#include "ShovelSlot.h"



ShovelSlot::ShovelSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	_ImageManager->AddTexture("UI_ShovelSlot", ResourcePath + L"UI/Shovel_Slot.png");
}


ShovelSlot::~ShovelSlot()
{
}

void ShovelSlot::Release()
{
}

void ShovelSlot::ControlUpdate()
{
}

void ShovelSlot::Update(float tick)
{
}

void ShovelSlot::Render()
{
	_ImageManager->Render("UI_ShovelSlot", FloatRect({ 70,75}, { 75,75}, Pivot::CENTER), nullptr);
}
