#include "stdafx.h"
#include "BoomSlot.h"
#include "UIBase.h"

BoomSlot::BoomSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	
}

BoomSlot::~BoomSlot()
{
}

void BoomSlot::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
	_ImageManager->AddTexture("UI_BoomSlot", ResourcePath + L"UI/UI_BoomSlot.png");
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
	_ImageManager->Render("UI_BoomSlot", rc, nullptr);
}
