#include "stdafx.h"
#include "HeadSlot.h"
#include "UIBase.h"


HeadSlot::HeadSlot(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:UIBase(name, pos, size)
{
	
}


HeadSlot::~HeadSlot()
{
}

void HeadSlot::Init()
{
	_RenderPool->Request(this, RenderManager::Layer::UI);
	
}

void HeadSlot::Release()
{
	_RenderPool->Remove(this, RenderManager::Layer::UI);

}

void HeadSlot::ControlUpdate()
{
}

void HeadSlot::Update(float tick)
{
}

void HeadSlot::Render()
{
	_ImageManager->Render("UI_HeadSlot", rc, nullptr);
}
