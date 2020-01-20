#include "stdafx.h"
#include "AttackSlot.h"
#include "UIBase.h"


AttackSlot::AttackSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	_ImageManager->AddTexture("UI_AttackSlot", ResourcePath + L"UI/Attack_Slot.png");
	_RenderPool->Request(this, RenderManager::Layer::UI);
}


AttackSlot::~AttackSlot()
{
}

void AttackSlot::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);
}

void AttackSlot::ControlUpdate()
{
}

void AttackSlot::Update(float tick)
{
}

void AttackSlot::Render()
{
	p2DRenderer->SetCamera(false);
	_ImageManager->Render("UI_AttackSlot", rc, nullptr);
	
}
