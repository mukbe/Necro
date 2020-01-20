#include "stdafx.h"
#include "BoomSlot.h"
#include "UIBase.h"

BoomSlot::BoomSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	_ImageManager->AddTexture("UI_BoomSlot", ResourcePath + L"UI/Boom_Slot.png");
}

BoomSlot::~BoomSlot()
{
}

void BoomSlot::Release()
{
}

void BoomSlot::ControlUpdate()
{
}

void BoomSlot::Update(float tick)
{
}

void BoomSlot::Render()
{
	_ImageManager->Render("UI_BoomSlot", FloatRect({ 70,350}, { 75,75 }, Pivot::CENTER), nullptr);
}
