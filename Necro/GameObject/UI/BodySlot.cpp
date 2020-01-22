#include "stdafx.h"
#include "BodySlot.h"
#include "UIBase.h"



BodySlot::BodySlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{

}


BodySlot::~BodySlot()
{
}

void BodySlot::Init()
{
	_ImageManager->AddTexture("UI_BodySlot", ResourcePath + L"UI/Body_Slot.png");
	_RenderPool->Request(this, RenderManager::Layer::UI);
}

void BodySlot::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);
}

void BodySlot::ControlUpdate()
{
}

void BodySlot::Update(float tick)
{
}

void BodySlot::Render()
{
	p2DRenderer->SetCamera(false);
	_ImageManager->Render("UI_BodySlot", rc, nullptr);
	
}
