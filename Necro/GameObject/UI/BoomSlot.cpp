#include "stdafx.h"
#include "BoomSlot.h"
#include "UIBase.h"

BoomSlot::BoomSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
	_ImageManager->AddTexture("UI_BoomSlot", ResourcePath + L"UI/Boom_Slot.png");
}

BoomSlot::~BoomSlot()
{
}

void BoomSlot::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);
}

void BoomSlot::ControlUpdate()
{
}

void BoomSlot::Update(float tick)
{
}

void BoomSlot::Render()
{
	p2DRenderer->SetCamera(false);
	_ImageManager->Render("UI_BoomSlot", rc, nullptr);
}
