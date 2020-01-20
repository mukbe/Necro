#include "stdafx.h"
#include "AttackSlot.h"
#include "UIBase.h"


AttackSlot::AttackSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	_ImageManager->AddTexture("UI_AttackSlot", ResourcePath + L"UI/Attack_Slot.png");
}


AttackSlot::~AttackSlot()
{
}

void AttackSlot::Release()
{
}

void AttackSlot::ControlUpdate()
{
}

void AttackSlot::Update(float tick)
{
}

void AttackSlot::Render()
{
	_ImageManager->Render("UI_AttackSlot", FloatRect({ 150,75 }, { 75,75}, Pivot::CENTER), nullptr);
}
