#include "stdafx.h"
#include "ThrowSlot.h"



ThrowSlot::ThrowSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	
}


ThrowSlot::~ThrowSlot()
{
}

void ThrowSlot::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
}

void ThrowSlot::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);
}

void ThrowSlot::ControlUpdate()
{
}

void ThrowSlot::Update(float tick)
{
}

void ThrowSlot::Render()
{
	p2DRenderer->SetCamera(false);
	_ImageManager->Render("UI_ThrowSlot", rc, nullptr);
}
