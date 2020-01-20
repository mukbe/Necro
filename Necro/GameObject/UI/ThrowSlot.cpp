#include "stdafx.h"
#include "ThrowSlot.h"



ThrowSlot::ThrowSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
	_ImageManager->AddTexture("UI_ThrowSlot", ResourcePath + L"UI/Throw_Slot.png");
	_ImageManager->AddTexture("UI_ThrowWaitSlot", ResourcePath + L"UI/Throw_Slot2.png");
}


ThrowSlot::~ThrowSlot()
{
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
